//
// Created by Ismael Cuevas on 7/15/24.
//

#include "../headers/BoardSpace.h"
int BoardSpace::getXIndex() const {
  return xIndex;
}

int BoardSpace::getYIndex() const {
  return yIndex;
}

ChessPiece* BoardSpace::getChessPiece() {
  return chessPiece;
}

PlayerID BoardSpace::getPlayerId() {
  if (chessPiece != NULL) {
    return chessPiece->getPlayerId();
  }

  return PlayerID::NONE;
}