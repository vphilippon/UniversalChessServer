/******************************************************************************
  Bishop.h
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07

  Bishop chess piece.
  (Inherits Piece. See Piece.h for undocummented elements)

  Modification log:
  Vincent Philippon, 2014-03-25 : Tweak for UniversalChessServer.
  Vincent Philippon, 2014-04-21 : Translate to english.
 *****************************************************************************/

#ifndef BISHOP_H_
#define BISHOP_H_
#include "Piece.h"

class Bishop :
  public Piece
{
public:
  // Methods
  Bishop(int team = 0, bool moved = false): Piece(team, moved) {}
  Bishop(Piece &p): Piece(p) {}
  ~Bishop();
  bool destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn);
  char type()const;
};

#endif
