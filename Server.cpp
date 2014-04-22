/******************************************************************************
  Server.cpp
  =====================
  Original author : Julian Bironneau and Vincent Philippon
  Original creation date : 2014-04-08

  TODO Description
 *****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "Protocol.h"
#include "Data.h"
#include "Game.h"

using namespace std;
using boost::asio::ip::tcp;

// Prototypes
void gameRun(shared_ptr<vector<shared_ptr<tcp::socket>>> sockets, int id);
void log(int id, string message);

int main()
{
  cout << "Server started." << endl;

  boost::asio::io_service io_service; 

  // Listening on port 1337
  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1337));

  int count = 0;
  for(;;)
  {
    shared_ptr<vector<shared_ptr<tcp::socket>>> sockets(
        new vector<shared_ptr<tcp::socket>>(2));
    for (int i = 0; i < 2; ++i)
    {
      // Connection
      shared_ptr<tcp::socket> socket(new tcp::socket(io_service));
      acceptor.accept(*socket);
      cout << "Connection of a player." << endl;
      (*sockets)[i] = socket;
    }
    boost::thread gameThread(gameRun, sockets, ++count);
  }

  return 0;
}

void gameRun(shared_ptr<vector<shared_ptr<tcp::socket>>> sockets, int id)
{
  log(id, "Game started.");
  Game game;
  game.init();

  try
  {
    // Distribution white/black
    Data data;
    data.team = 1;
    Protocol::write((*sockets)[0], data);
    data.team = -1;
    Protocol::write((*sockets)[1], data);


    int turn = 0;
    bool gameOver = false;
    while(!gameOver)
    {
      data = Data();
      data = Protocol::read((*sockets)[turn]);

      log(id, "Data received.");

      Data::Status status = game.playerDo(data);

      switch (status)
      {
        case Data::ok:
          log(id, "Move is ok.");
          status = game.getCurrentStatus();
          data.status = status;
          data.team = game.getCurrentTeam();
          for(int i = 0; i < 2; ++i)
          {
            Protocol::write((*sockets)[i], data);
          }
          turn = data.team > 0 ? 0 : 1;

          // Take care of checkMate and draw!
          gameOver = (status == Data::checkMate || status == Data::draw);
          break;

        case Data::promotion:
          log(id, "Promotion required.");
          data.status = Data::promotion;
          data.team = game.getCurrentTeam();
          turn = data.team > 0 ? 0 : 1;
          Protocol::write((*sockets)[turn], data);
          break;

        case Data::rejected:
          log(id, "Move is rejected.");
          data.status = Data::rejected;
          data.team = game.getCurrentTeam();
          turn = data.team > 0 ? 0 : 1;
          Protocol::write((*sockets)[turn], data);
          break;

        default:
          log(id, "Oops...That wasn't expexted...");
      }
    }
  }
  catch(...)
  {
    log(id, "Connection closed by peer. Close remaining connection.");
  }

  log(id, "Game ended.");

  for (int i = 0; i < 2; ++i)
  {
    (*sockets)[i]->close();
  }
}

void log(int id, string message)
{
  cout << id << " : " << message << endl;
}


