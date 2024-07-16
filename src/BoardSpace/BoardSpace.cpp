//
// Created by Ismael Cuevas on 7/15/24.
//

#include "../../headers/BoardSpace/BoardSpace.h"

BoardSpace::BoardSpace(ChessPiece *chessPiece, int xIndex, int yIndex) {
}

int BoardSpace::getXIndex() const {
  return xIndex;
}

int BoardSpace::getYIndex() const {
  return yIndex;
}

ChessPiece* BoardSpace::getChessPiece() {
  return chessPiece;
}

void BoardSpace::setChessPiece(ChessPiece *chessPiece) {
  this->chessPiece = chessPiece;
}

PlayerID BoardSpace::getPlayerId() {
  if (chessPiece != NULL) {
    return chessPiece->getPlayerId();
  }

  return PlayerID::NONE;
}


