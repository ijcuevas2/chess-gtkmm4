//
// Created by Ismael Cuevas on 7/15/24.
//

#include "../../headers/BoardSpace/BoardSpace.h"

BoardSpace::BoardSpace(ChessPiece *chessPiecePtr, int xIndex, int yIndex) {
  this->chessPiecePtr = chessPiecePtr;
  this->xIndex = xIndex;
  this->yIndex = yIndex;
}

int BoardSpace::getXIndex() const {
  return xIndex;
}

int BoardSpace::getYIndex() const {
  return yIndex;
}

ChessPiece* BoardSpace::getChessPiecePtr() {
  return chessPiecePtr;
}

void BoardSpace::setChessPiecePtr(ChessPiece *chessPiecePtr) {
  this->chessPiecePtr = chessPiecePtr;
}

PlayerID BoardSpace::getPlayerId() {
  if (chessPiecePtr != NULL) {
    return chessPiecePtr->getPlayerId();
  }

  return PlayerID::NONE;
}

void BoardSpace::clearChessPiecePtr() {
}
