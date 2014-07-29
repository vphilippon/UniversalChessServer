/******************************************************************************
  King.hpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07

  King chess piece.
  (Inherits Piece. See Piece.hpp for undocummented elements)

  Modification log:
  Vincent Philippon, 2014-03-25 : Tweak for UniversalChessServer.
  Vincent Philippon, 2014-04-21 : Translate to english.
 *****************************************************************************/

#ifndef KING_HPP_
#define KING_HPP_
#include "Piece.hpp"

class King :
  public Piece
{
public:
  // Methods
  King(int team = 0, bool moved = false): Piece(team, moved) {}
  King(Piece &p): Piece(p) {}
  ~King();
  bool destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn);
  char type()const;
};

#endif
