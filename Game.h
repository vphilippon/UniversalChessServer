/******************************************************************************
  Game.h
  =====================
  Original author : Julian Bironneau and Vincent Philippon
  Original creation date : 2014-03-27

  This class takes care of the chess game.
  It register the moves, keep information on the state of the game and ensure
  everything goes according to the chess game rules.
 *****************************************************************************/

#ifndef GAME_H_
#define GAME_H_
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Data.h"


class Game
{
  private:
    // Property
    Piece* _board[8][8];
    int _whiteKingX;
    int _whiteKingY;
    int _blackKingX;
    int _blackKingY;
    int _xEnPassant; // X of the "en passant" potential victim
    int _yEnPassant; // Y of the "en passant" potential victim
    int _turn;
    int _PieceCount;
    Piece* _tempPieceKeep; // Intended in need of undo
    bool _promotion;
    int _prevXFrom;
    int _prevYFrom;
    int _prevXTo;
    int _prevYTo;

  public:
    // Methods
    Game(); 
    ~Game();

    void init();
    int getCurrentTeam(); // Get the current team playing
    Data::Status getCurrentStatus(); // Get the current status for the current team
    Data::Status playerDo(Data& data); // Try and do an action 

  private:
    Data::Status playerDoPromotion(Data& data); // Try and do the promotion
    Data::Status playerDoMove(int xFrom, int yFrom, int xTo, int yTo); // Try and do the move
    bool isCheck(int x = -1, int y = -1); // Tells if the current playing king is in check
    bool isAbleToMove(); // Tell if there's legal move left
    bool verifyMove(int xPiece, int yPiece, int xDestination, int yDestination); // Make sure it doesn't cause self-check
    void undoMove(int xPiece, int yPiece, int xDestination, int yDestination); // Undo the last move
    void movePiece(int xPiece, int yPiece, int xDestination, int yDestination); // Move the Piece
    bool castling(int xPiece, int yPiece, int &xDestination, int &yDestination); // Castling move
    void concludeMove(int xDestination, int yDestination); // Conclude the move
};

#endif

