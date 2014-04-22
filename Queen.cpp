/******************************************************************************
  Queen.cpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07
  (See Queen.h for details)
 *****************************************************************************/

#include "Queen.h"
#include <cmath>

using namespace std;

Queen::~Queen()
{
  init();
}

bool Queen::destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn)
{
  bool action = 0; //Do we do the act

  int xDifference; // X Difference
  int yDifference; // Y Difference

  // If it's not the same team
  if(board[yTo][xTo]->getTeam() != turn)
  {
    
    xDifference = xTo - xFrom;
    yDifference = yTo - yFrom;
    
    // If it's diagonal
    if(abs(yDifference) == abs(xDifference))
    {
      // If it's right beside the Piece
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
    // If it's vertical
    else if(yTo == yFrom)
    {
      // If it's right beside the Piece
      if(abs(xTo - xFrom) == 1)
      {
        action = 1;
      }
      // If we're going backward
      else if(xTo < xFrom)
      {
        action = 1;
        for(int i = xFrom - 1; i > xTo; i--)
        {  
          // If the space isn't empty
          if(board[yFrom][i]->getTeam() != 0)
          {
            action = 0;
            break;
          }
        }
      }
      // If we're going forward
      else
      {
        action = 1;
        for(int i = xFrom + 1; i < xTo; i++)
        {  
          // If the space isn't empty
          if(board[yFrom][i]->getTeam() != 0)
          {
            action = 0;
            break;
          }
        }
      }
    }
    // If it's horizontal
    else if(xTo == xFrom)
    {  
      // If it's right beside the Piece
      if(abs(yTo - yFrom) == 1)
      {
        action = 1;
      }
      // If we're going backward
      else if(yTo < yFrom)
      {
        action = 1;
        for(int i = yFrom - 1; i > yTo; i--)
        {    
          // If the space isn't empty
          if(board[i][xFrom]->getTeam() != 0)
          {
            action = 0;
            break;
          }
        }
      }
      // If we're going forward
      else
      {
        action = 1;
        for(int i = yFrom + 1; i < yTo; i++)
        {  
          // If the space isn't empty
          if(board[i][xFrom]->getTeam() != 0)
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

char Queen::type()const
{
  return 'Q';
}
