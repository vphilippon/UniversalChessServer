/******************************************************************************
  Bishop.cpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07
  (See Bishop.hpp for details)
 *****************************************************************************/

#include "Bishop.hpp"
#include <cmath>

using namespace std;

Bishop::~Bishop()
{
  init();
}

bool Bishop::destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn)
{
  bool action = 0;  // Do we do the act

  int  xDifference;  // X Difference
  int  yDifference;  // Y Difference

  // If it's not the same team
  if(board[yTo][xTo]->getTeam() != turn)
  {
    xDifference = xTo - xFrom;
    yDifference = yTo - yFrom;
    
    // If it's diagonal
    if(abs(yDifference) == abs(xDifference))
    {
      // If it's right beside it
      if(abs(xDifference) == 1)
      {
        action = 1;
      }
      // If X+, Y+
      else if(xDifference > 0 && yDifference > 0)
      {
        action = 1;
        for(int i = 1; i < abs(xDifference); i++)
        {
          // If the space isn't empty
          if(board[yFrom + i][xFrom + i]->getTeam() != 0)
          {
            action = 0;
            break;
          }
        }
      }
      // If X+, Y-
      else if(xDifference > 0 && yDifference < 0)
      {
        action = 1;
        for(int i = 1; i < abs(xDifference); i++)
        {  
          // If the space isn't empty
          if(board[yFrom - i][xFrom + i]->getTeam() != 0)
          {
            action = 0;
            break;
          }
        }  
      }
      // If X-, Y+
      else if(xDifference < 0 && yDifference > 0)
      {
        action = 1;
        for(int i = 1; i < abs(xDifference); i++)
        {  
          // If the space isn't empty
          if(board[yFrom + i][xFrom - i]->getTeam() != 0)
          {
            action = 0;
            break;
          }
        }  
      }
      // If X-, Y-
      else
      {
        action = 1;
        for(int i = 1; i < abs(xDifference); i++)
        {  
          // If the space isn't empty
          if(board[yFrom - i][xFrom - i]->getTeam() != 0)
          {
            action = 0;
            break;
          }
        }  
      }
    }
  }
  return action;
}

char Bishop::type()const
{
  return 'B';
}
