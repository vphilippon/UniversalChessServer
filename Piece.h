/******************************************************************************
  Piece.h
  =====================
  Original author : Alexandre Beaulieu and Vincent Philippon
  Original creation date : 2010-05-07

  Chess piece. Base for all chess pieces. Also represent and empty spot.

  Modification log:
  Vincent Philippon, 2014-03-25 : Tweak for UniversalChessServer.
  Vincent Philippon, 2014-04-21 : Translate to english.
 *****************************************************************************/

#ifndef PIECE_H_
#define PIECE_H_
#include <assert.h>


class Piece
{
protected:
  // Property
  int _team; // Team of the Piece. 1 = White | -1 = Black
  bool _moved; // Indicates if the Piece was moved.

public:
  // Methods
  Piece(int team = 0, bool moved = false);
  Piece(Piece &p);
  virtual ~Piece();
  void init(int team = 0, bool moved = false);

  // Getter
  int getTeam()const;
  bool getMoved()const;

  // Setter
  void setTeam(int team);
  void setMoved(bool moved);

  // Overload of operator= Copy the property _team and _moved
  const Piece& operator=(const Piece &p);

  // Virtual methods
  // Validates the move according to the Piece allowed behaviour
  virtual bool destination(Piece* board[8][8], int xFrom, int yFrom, int xTo, int yTo, int turn);
  // Return a char representing the type of the Piece
  virtual char type()const;
};

#endif
