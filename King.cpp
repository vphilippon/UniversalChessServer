/******************************************************************************
  King.cpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07
  (See King.h for details)
 *****************************************************************************/

#include "King.h"
#include <cmath>

using namespace std;

King::~King()
{
  init();
}

bool King::destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn)
{
  bool action = 0; //Do we do the act

  int xDifference; // X Difference
  int yDifference; // Y Difference

  // If it's not the same team
  if(board[yTo][xTo]->getTeam() != turn)
  {
    
    xDifference = xTo - xFrom;
    yDifference = yTo - yFrom;
    
    // If the move is only of 1
    if((abs(xDifference) + abs(yDifference)) == 1)
    {
      action = 1;
    }
  }
  // Castling
  else if(getMoved() == false 
          && board[yTo][xTo]->getMoved() == false
          && board[yTo][xTo]->getTeam() == turn
          && board[yTo][xTo]->type() == 'T')
  {
    // King side
    if(xTo == 7)
    {
      action = 1;
      for(int i = xFrom + 1; i < xTo; i++)
      {
        //Si non vide
        if(board[yFrom][i]->getTeam() != 0)
        {
          action = 0;
          break;
        }
      }
    }
    // Queen side
    else if(xTo == 0)
    {
      action = 1;
      for(int i = xFrom - 1; i > xTo; i--)
      {
        // If space not empty
        if(board[yFrom][xFrom - i]->getTeam() != 0)
        {
          action = 0;
          break;
        }
      }
    }
  }

  return action;
}

char King::type()const
{
  return 'K';
}
