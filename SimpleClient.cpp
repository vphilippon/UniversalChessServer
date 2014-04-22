#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Protocol.h"
#include "Data.h"

using namespace std;
using boost::asio::ip::tcp;

// Prototypes
void doMove(shared_ptr<tcp::socket> socket);
void showMove(Data data);
void doPromotion(shared_ptr<tcp::socket> socket);

int main()
{
  cout << "Client started." << endl;

  boost::asio::io_service io_service;
  tcp::resolver resolver(io_service);

  string serverAddress;
  cout << "Enter the chess server address : " << endl;
  cin >> serverAddress;

  tcp::resolver::query query(serverAddress, "1337");
  tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

  // Connexion au server
  shared_ptr<tcp::socket> socket(new tcp::socket(io_service));
  socket->connect(*endpoint_iterator);

  cout << "Waiting for the second player..." << endl;

  Data data;
  data = Protocol::read(socket);
  int team = data.team;

  // Am I white or black?
  if(team > 0) // White
  {
    cout << "You play as white." << endl;
    
    // White first turn
    doMove(socket);
  }
  else // Black
  {
    cout << "You play as black." << endl;
  }


  bool gameOver = false;
  while (!gameOver)
  {
    // Block and wait for server answer
    data = Protocol::read(socket);

    // If it's our turn to act
    if(data.team == team)
    {
      switch (data.status)
      {
        case Data::ok:
          showMove(data);
          cout << "It's your turn to play." << endl;
          doMove(socket);
          break;

        case Data::rejected:
          cout << "REJECTED : Your move was illegal. Play again." << endl;
          doMove(socket);
          break;

        case Data::promotion:
          doPromotion(socket);
          break;

        case Data::checkOnly:
          showMove(data);
          cout << "ATTENTION! You are in CHECK!" << endl
            << "It's your turn to play." << endl;
          doMove(socket);
          break;

        case Data::checkMate:
          showMove(data);
          cout << "Defeat! You are CHECKMATE!" << endl;
          gameOver = true;
          break;

        case Data::draw:
          showMove(data);
          cout << "Draw! Your opponent move caused a STALEMATE!" << endl;
          gameOver = true;
          break;

        default:
          cout << "Oops! That wasn't expected..." << endl;
      }
    }
    else // If it's the opponent's turn to act
    {
      switch (data.status)
      {
        case Data::ok:
          cout << "It's the opponent's turn to play." << endl;
          break;

        case Data::checkOnly:
          cout << "The opponent is in CHECK!" << endl
            << "It's the opponent's turn to play." << endl;
          break;

        case Data::checkMate:
          cout << "Victory! The opponent is CHECKMATE!" << endl;
          gameOver = true;
          break;

        case Data::draw:
          cout << "Draw! Your move caused a STALEMATE!" << endl;
          gameOver = true;
          break;

        default:
          cout << "Oops! That wasn't expected..." << endl;
      }
    }
  }

  cout << "Client stopping." << endl;
  socket->close();
  return 0;
}

void doMove(shared_ptr<tcp::socket> socket)
{
  Data data;
  cout << "Enter the move :" << endl
    << "(Format : X_Piece Y_Piece X_Destination Y_Destination)" << endl;
  cin >> data.xFrom >> data.yFrom >> data.xTo >> data.yTo;
  Protocol::write(socket, data);
}

void showMove(Data data)
{
  cout << "Movement : " << data.xFrom << "," << data.yFrom << " -> " 
    << data.xTo << "," << data.yTo << endl;
  if(data.promotionChoice != ' ')
  {
    cout << "The pawn in " << data.xFrom << "," << data.yFrom
      << "moved in " << data.xTo << "," << data.yTo 
      << " was promoted to " << data.promotionChoice << "." << endl;
  }
}

void doPromotion(shared_ptr<tcp::socket> socket)
{
  Data data;
  cout << "Enter the promotion choice :" << endl
    << "(Choice : Knight(k), bishop(b), rook(r), queen(q))" << endl;
  cin >> data.promotionChoice;
  Protocol::write(socket, data);
}

