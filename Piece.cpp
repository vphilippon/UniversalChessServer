/******************************************************************************
  Piece.cpp
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07
  (See Piece.hpp for details)
 *****************************************************************************/

#include "Piece.hpp"

Piece::Piece(int team, bool moved)
{
  init(team, moved);
}

Piece::Piece(Piece &p)
{
  init(p.getTeam(), p.getMoved());
}

Piece::~Piece()
{
  init();
}

void Piece::init(int team, bool moved)
{
  setTeam(team);
  setMoved(moved);
}

void Piece::setTeam(int team)
{
  assert(team > -2 && team < 2);
  _team = team;
}

void Piece::setMoved(bool moved)
{
  _moved = moved;
}

int Piece::getTeam()const
{
  return _team;
}

bool Piece::getMoved()const
{
  return _moved;
}

const Piece& Piece::operator=(const Piece &p)
{
  init(p.getTeam(), p.getMoved());
  return *this;
}

bool Piece::destination(Piece*[8][8], int, int, int, int, int)
{
  return false;
}

char Piece::type()const
{
  return 'V'; // From french : Empty => Vide
}
