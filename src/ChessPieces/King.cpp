//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/King.h"

bool King::canMoveToTarget(Coordinates coordinates) {
  return false;
}

void King::afterPieceMoved(Coordinates coordinates) {
  this->setHasMoved();
}

bool King::getHasMoved() {
  return hasMoved;
}

void King::setHasMoved() {
  this->hasMoved = true;
}