/******************************************************************************
  Game.cpp
  =====================
  Original author : Vincent Philippon
  Original creation date : 2014-03-27
  (See Game.h for details)
 ******************************************************************************/

#include "Game.h"
#include <cmath>
using namespace std;


int Game::getCurrentTeam()
{
  return _turn;
}

Data::Status Game::getCurrentStatus()
{
  bool check = isCheck();
  bool canMove = isAbleToMove();
  Data::Status returnValue = Data::ok;

  // If CheckMate
  if(check && !canMove)
  {
    returnValue = Data::checkMate;
  }
  // If only check
  else if(check)
  {
    returnValue = Data::checkOnly;
  }
  // If it's a draw
  else if(!canMove || _PieceCount== 2)
  {
    returnValue = Data::draw;
  }

  return returnValue;
}

Data::Status Game::playerDo(Data& data)
{
  Data::Status status;
  if(_promotion)
  {
    data.xFrom = _prevXFrom;
    data.yFrom = _prevYFrom;
    data.xTo = _prevXTo;
    data.yTo = _prevYTo;
    status = playerDoPromotion(data);
  }
  else
  {
    data.promotionChoice = ' ';
    status = playerDoMove(data.xFrom, data.yFrom, data.xTo, data.yTo);
  }
  return status;
}

Data::Status Game::playerDoPromotion(Data& data)
{
  Data::Status status = Data::ok;
  _tempPieceKeep = _board[data.yTo][data.xTo];

  switch (data.promotionChoice)
  {
    case 'k':
      _board[data.yTo][data.xTo] = new Knight(*_tempPieceKeep);
      break;

    case 'b':
      _board[data.yTo][data.xTo] = new Bishop(*_tempPieceKeep);
      break;

    case 'r':
      _board[data.yTo][data.xTo] = new Rook(*_tempPieceKeep);
      break;

    case 'q':
      _board[data.yTo][data.xTo] = new Queen(*_tempPieceKeep);
      break;

    default:
      data.promotionChoice = ' ';
      status = Data::promotion;
  }

  if(status == Data::ok)
  {
    delete _tempPieceKeep;
    _turn *= -1;
    _promotion = false;
    _prevXFrom = -1;
    _prevYFrom = -1;
    _prevXTo = -1;
    _prevYTo = -1;
  }

  _tempPieceKeep = NULL;
  return status;
}

Data::Status Game::playerDoMove(int xFrom, int yFrom, int xTo, int yTo)
{
  Data::Status returnValue = Data::rejected;

  // Make sure coordinates are in range
  if(xFrom >= 0 && xFrom < 8
      && yFrom >= 0 && yFrom < 8
      && xTo >= 0 && xTo < 8
      && yTo >= 0 && yTo < 8)
  {
    if(_board[yFrom][xFrom]->getTeam() * _turn > 0
        && _board[yFrom][xFrom]->destination(_board, xFrom, yFrom, xTo, yTo, _turn))
    {
      // If move "en passant"
      if(_board[yFrom][xFrom]->type() == 'P'
          && _board[yFrom][xFrom]->getTeam() == 0
          && yTo == yFrom - _turn && abs(xTo - xFrom) == 1)
      {
        if(xTo == _xEnPassant && yTo == _yEnPassant)
        {
          _tempPieceKeep = _board[yTo][xTo];
          if(verifyMove(xFrom, yFrom, xTo, yTo))
          {
            _board[yTo + _turn][xTo] = new Piece();
            returnValue = Data::ok;
            concludeMove(xTo, yTo);
          }
        }
      }
      // If Castling
      else if(_board[yFrom][xFrom]->type() == 'K'
          && _board[yTo][xTo]->type() == 'R'
          && _board[yTo][xTo]->getTeam() == _turn
          && _board[yTo][xTo]->getMoved() == false
          && _board[yFrom][xFrom]->getMoved() == false)
      {
        if(castling(xFrom, yFrom, xTo, yTo))
        {
          returnValue = Data::ok;
          concludeMove(xTo, yTo);
        }
      }
      // If a more "usual" move
      else
      {
        _tempPieceKeep = _board[yTo][xTo];
        if(verifyMove(xFrom, yFrom, xTo, yTo))
        {
          returnValue = Data::ok;
          concludeMove(xTo, yTo);
        }
      }
    } // endif move validation
    if(returnValue == Data::ok)
    {
      // If pawn is at opposite last line.
      // (int cast to roundown)
      if(_board[yTo][xTo]->type() == 'P'
          && yTo == (3.5 - 3.5 * _turn))	
      {
        _prevXFrom = xFrom;
        _prevYFrom = yFrom;
        _prevXTo = xTo;
        _prevYTo = yTo;
        _promotion = true;
        returnValue = Data::promotion;
      }

      // If pawn moved 2 square ahead, making a "en passant" opportunity
      if(_board[yTo][xTo]->type() == 'P' && abs(yTo - yFrom) == 2 && xTo == xFrom)
      {
        _xEnPassant = xTo;
        _yEnPassant = yTo + _turn;
      }
      else
      {
        _xEnPassant = _yEnPassant = -1;
      }
    }
  }

  // turn switch if turn done
  if(returnValue == Data::ok)
  {
    _turn *= -1;
  }

  return returnValue;
}

Game::Game():
  _tempPieceKeep(NULL)
{
}

Game::~Game()
{
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      delete _board[i][j];
    }
  }
}

void Game::init()
{
  // White section
  _board[7][0] = new Rook(1);
  _board[7][7] = new Rook(1);
  _board[7][1] = new Knight(1);
  _board[7][6] = new Knight(1);
  _board[7][2] = new Bishop(1);
  _board[7][5] = new Bishop(1);
  _board[7][3] = new Queen(1);
  _board[7][4] = new King(1);
  for(int i = 0; i < 8; i++)
  {
    _board[6][i] = new Pawn(1);
  }

  // Black section
  _board[0][0] = new Rook(-1);
  _board[0][7] = new Rook(-1);
  _board[0][1] = new Knight(-1);
  _board[0][6] = new Knight(-1);
  _board[0][2] = new Bishop(-1);
  _board[0][5] = new Bishop(-1);
  _board[0][3] = new Queen(-1);
  _board[0][4] = new King(-1);
  for(int i = 0; i < 8; i++)
  {
    _board[1][i] = new Pawn(-1);
  }

  // Empty section
  for(int i = 2; i < 6; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      _board[i][j] = new Piece();
    }
  }

  // King position
  _whiteKingX = _blackKingX = 4;
  _whiteKingY = 7;
  _blackKingY = 0;
  _xEnPassant = -1;
  _yEnPassant = -1;
  _turn = 1;
  _PieceCount = 32;
  _promotion = false;
  _prevXFrom = -1;
  _prevYFrom = -1;
  _prevXTo = -1;
  _prevYTo = -1;
}

bool Game::isCheck(int x, int y)
{
  bool check = false;
  int kingX;
  int kingY;

  if(x >= 0 && y >= 0)
  {
    kingX = x;
    kingY = y;
  }
  else if(_turn > 0)
  {
    kingX = _whiteKingX;
    kingY = _whiteKingY;
  }
  else
  {
    kingX = _blackKingX;
    kingY = _blackKingY;
  }

  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      // If the Piece belongs to the other team
      if(_board[i][j]->getTeam() == _turn * -1)
      {
        check = _board[i][j]->destination(_board, j, i, kingX, kingY, _turn * -1);

        if(check)
        {
          return true;
        }
      }
    }
  }

  return false;
}

bool Game::isAbleToMove()
{
  bool canMove = false; //If there's a legal move left

  int i, // Index for Y coordinate of the Piece
      j, // Index for X coordinate of the Piece
      k, // Index for Y coordinate of the destination
      l; // Index for X coordinate of the destination

  for(i = 0; i < 8; i++)
  {
    for(j = 0; j < 8; j++)
    {
      if(_board[i][j]->getTeam() == _turn)
      {
        for(k = 0; k < 8; k++)
        {
          for(l = 0; l < 8; l++)
          {
            // If the destination is ok
            if(_board[i][j]->destination(_board, j, i, l, k, _turn))
            {
              // if it's a "en passant" move
              if(_board[i][j]->type() == 'P'
                  && _board[k][l]->getTeam() == 0
                  && k == i - _turn 
                  && abs(l - j) == 1)
              {
                if(l == _xEnPassant && k == _yEnPassant)
                {
                  canMove = verifyMove(j, i, l, k); 
                }
                else
                {
                  canMove = false;
                }
              }
              // If it's a normal move
              else
              {
                canMove = verifyMove(j, i, l, k); 
              }

              // If a Piece can move
              if(canMove)
              {
                undoMove(j, i, l, k);
                return canMove;
              }
            }
          }
        }
      }
    }
  }

  return canMove;
}


bool Game::verifyMove(int xPiece, int yPiece, int xDestination, int yDestination)
{
  bool move = true; // If the Piece can move

  movePiece(xPiece, yPiece, xDestination, yDestination);

  // Verify if the king is in check
  if(isCheck())
  {
    undoMove(xPiece, yPiece, xDestination, yDestination);
    move = false;
  }

  return move;
}

void Game::undoMove(int xPiece, int yPiece, int xDestination, int yDestination)
{
  // Update king position if needed
  if(_turn > 0)
  {
    if(xDestination == _whiteKingX && yDestination == _whiteKingY)
    {
      _whiteKingX = xPiece;
      _whiteKingY = yPiece;
    }
  }
  else
  {
    if(xDestination == _blackKingX && yDestination == _blackKingY)
    {
      _blackKingX = xPiece;
      _blackKingY = yPiece;
    }
  }

  // Delete, Swap and use temp
  delete _board[yPiece][xPiece];
  _board[yPiece][xPiece] = _board[yDestination][xDestination];
  _board[yDestination][xDestination] = _tempPieceKeep;
  _tempPieceKeep = NULL;
}

void Game::movePiece(int xPiece, int yPiece, int xDestination, int yDestination)
{
  // Update king position if needed
  if(xPiece == _whiteKingX && yPiece == _whiteKingY)
  {
    _whiteKingX = xDestination;
    _whiteKingY = yDestination;
  }
  else if(xPiece == _blackKingX && yPiece == _blackKingY)
  {
    _blackKingX = xDestination;
    _blackKingY = yDestination;
  }

  // Swap and keep temp until move is confirmed
  _tempPieceKeep = _board[yDestination][xDestination];
  _board[yDestination][xDestination] = _board[yPiece][xPiece];
  _board[yPiece][xPiece] = new Piece();
}

bool Game::castling(int xPiece, int yPiece, int &xDestination, int &yDestination)
{
  // Castling King side
  if(xDestination == 7)
  {
    for(int i = xPiece + 1; i < xDestination; i++)
    {
      // If king path checked by opponent
      if(isCheck(i, yPiece))
      {
        return false;
      }
    }
    // If there's a pawn in front of the tower (will check king)
    if(_board[yPiece - _turn][7]->getTeam() == -_turn
        && _board[yPiece - _turn][7]->type() == 'P')
    {
      return false;
    }
    // If legal castling
    else
    {
      // Move the rook.
      movePiece(xDestination, yDestination, xPiece + 1, yPiece);
      concludeMove(xDestination, yDestination);
      // Move the King
      xDestination -= 1;
      movePiece(xPiece, yPiece, xDestination, yDestination);
      return true;
    }
  }
  // Castling Queen side
  // TODO Check rule, Averbakh game, 1912, maybe we shouldn't check all the path. See wikipedia
  else if(xDestination == 0)
  {
    for(int i = xPiece - 1; i > xDestination; i--)
    {
      // If king path checked by opponent
      if(isCheck(i, yPiece))
      {
        return false;
      }
    }
    // If there's a pawn in front of the tower (will check king)
    if(_board[yPiece - _turn][0]->getTeam() == -_turn
        && _board[yPiece - _turn][0]->type() == 'P')
    {
      return false;
    }
    // If legal castling
    else
    {
      // Move the rook.
      movePiece(xDestination, yDestination, xPiece - 1, yPiece);
      concludeMove(xDestination, yDestination);
      // Move the King
      xDestination += 2;
      movePiece(xPiece, yPiece, xDestination, yDestination);
      return true;
    }
  }
  else
  {
    // Should Never happen...
    return false;
  }
}

void Game::concludeMove(int xDestination, int yDestination)
{
  _board[yDestination][xDestination]->setMoved(true);

  if(_tempPieceKeep != NULL)
  {
    delete _tempPieceKeep;
    _tempPieceKeep = NULL;
  }
}


