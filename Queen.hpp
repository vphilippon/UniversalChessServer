/******************************************************************************
  Queen.hpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07

  Queen chess piece.
  (Inherits Piece. See Piece.hpp for undocummented elements)

  Modification log:
  Vincent Philippon, 2014-03-25 : Tweak for UniversalChessServer.
  Vincent Philippon, 2014-04-21 : Translate to english.
 *****************************************************************************/

#ifndef QUEEN_HPP_
#define QUEEN_HPP_
#include "Piece.hpp"

class Queen :
  public Piece
{
public:
  // Methods
  Queen(int team = 0, bool moved = false): Piece(team, moved) {}
  Queen(Piece &p): Piece(p) {}
  ~Queen();
  bool destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn);
  char type()const;
};

#endif
