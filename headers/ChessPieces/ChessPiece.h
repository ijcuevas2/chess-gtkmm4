//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H
#include "../../enum/PieceType.h"
#include "../../enum/Player.h"
#include "../Point2DPair/Point2DPair.h"
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
  bool hasValidCoordinates(Point2DPair coordinates);
  virtual bool getIsValidPath(Point2DPair coordinates) = 0;
  virtual Point2DPair getNextCoordinates(Point2DPair coordinates);
  virtual bool canMoveToTarget(Point2DPair coordinates);
  virtual void afterPieceMoved(Point2DPair coordinates);
  virtual bool isPieceBlockingPath(Point2DPair coordinates);
  void copyChessPiece(ChessPiece* chessPiecePtr);
  PlayerID getPlayerId();
  PieceType getPieceType();
  void setPlayerId(PlayerID playerId);
  void setPieceType(PieceType pieceType);
protected:
  PieceType pieceType;
  PlayerID playerId;
  ChessBoardMediator & chessBoardMediator;
};
#endif //CHESS_CHESSPIECE_H
