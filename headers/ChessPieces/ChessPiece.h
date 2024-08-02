//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H
#include "../../enum/PieceType.h"
#include "../../enum/Player.h"
#include "../Coordinates/Coordinates.h"
#include "ChessBoardMediator/ChessBoardMediator.h"
#include "../../headers/MathUtils/MathUtils.h"
#include <iostream>

class ChessPiece {
public:
  void setChessPieceImagePath();
  ChessPiece(PlayerID playerId, PieceType pieceType, ChessBoardMediator & chessBoardMediator);
  virtual ~ChessPiece();
  int actualDistance(int source, int dest);
  int absoluteDistance(int source, int dest);
  virtual bool canMoveToTarget(Coordinates coordinates);
  bool canMoveToTargetHelper(Coordinates coordinates);
  virtual void afterPieceMoved(Coordinates coordinates) = 0;
  virtual bool isPieceBlockingPath(Coordinates coordinates) = 0;
  virtual Coordinates getNextCoordinates(Coordinates coordinates) = 0;
  PlayerID getPlayerId();
  PieceType getPieceType();
  void setPlayerId(PlayerID playerId);
  void setPieceType(PieceType pieceType);
  void copyChessPiece(ChessPiece* chessPiece);
protected:
  PieceType pieceType;
  PlayerID playerId;
  ChessBoardMediator & chessBoardMediator;
};
#endif //CHESS_CHESSPIECE_H
