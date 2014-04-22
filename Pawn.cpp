/******************************************************************************
  Pawn.cpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07
  (See Pawn.h for details)
 *****************************************************************************/

#include "Pawn.h"
#include <cmath>

using namespace std;

Pawn::~Pawn()
{
  init();
}

bool Pawn::destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn)
{
  bool action = 0; //Do we do the act

  // If it's not the same team
  if(board[yTo][xTo]->getTeam() != turn)
  {
    // If straight
    if(xTo == xFrom)
    {
      // If forward and empty
      if(yTo == yFrom - turn && board[yTo][xTo]->getTeam() == 0)
      {
        action = 1;
      }
      // If it's the first move, allow for 2 forward and empty space.
      else if(getMoved() == 0
              && yTo == yFrom - turn * 2
              && board[yTo + turn][xTo]->getTeam() == 0
              && board[yTo][xTo]->getTeam() == 0)
      {
        action = 1;
      }
    }
    // If it's diagonal and to capture, allow
    else if(yTo == yFrom - turn && abs(xTo - xFrom) == 1)
    {
      action = 1;
    }
  }
  return action;
}

char Pawn::type()const
{
  return 'P';
}
