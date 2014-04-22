/******************************************************************************
  Rook.cpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07
  (See Rook.h for details)
 *****************************************************************************/

#include "Rook.h"
#include <cmath>

using namespace std;

Rook::~Rook()
{
  init();
}

bool Rook::destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn)
{
  bool action = 0; //Do we do the act

  // If it's not the same team
  if(board[yTo][xTo]->getTeam() != turn)
  { 
    // If it's vertical
    if(yTo == yFrom)
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

char Rook::type()const
{
  return 'R';
}
