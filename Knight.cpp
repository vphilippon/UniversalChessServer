/******************************************************************************
  Knight.cpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07
  (See Knight.h for details)
 *****************************************************************************/

#include "Knight.h"
#include <cmath>

using namespace std;

Knight::~Knight()
{
  init();
}

bool Knight::destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn)
{
  bool action = 0; //Do we do the act

  // If it's not the same team
  if(board[yTo][xTo]->getTeam() != turn)
  {
    // FRENCH : Si le produit des différences donne 2 (donc mouvement en L)
    // If the differences multiplication is 2 (L shape)
    if(abs((yTo - yFrom)*(xTo - xFrom)) == 2)
    {
      action = 1;
    }
  }

  return action;
}

char Knight::type()const
{
  return 'C'; // K is taken for King. Using french : Knight => Cavalier
}
