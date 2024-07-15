//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H
#include "../../enum/PieceType.h"
#include "../../enum/Player.h"
#include "../Coordinates.h"
#include <iostream>

class ChessPiece {
public:
  void setChessPieceImagePath();

  int actualDistance(int source, int dest);
  int absoluteDistance(int source, int dest);

  virtual bool canMove(Coordinates coordinates) = 0;
  virtual void afterPieceMoved(Coordinates coordinates) = 0;
  bool isPieceBlockingPath(Coordinates coordinates);
  PlayerID getPlayerId();
  PieceType getPieceType();

protected:
  PieceType pieceType;
  PlayerID playerId;
};
#endif //CHESS_CHESSPIECE_H
