//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/King.h"
bool King::canMoveToTarget(Coordinates coordinates) {
}

std::vector<Coordinates> King::getAdjacentCoordinates(Coordinates coordinates) {
}

void King::afterPieceMoved(Coordinates coordinates) {
  this->setHasMoved();
  this->chessBoardMediator.getUpdateKingPositionSignal().emit(playerId, coordinates.getTgtRow(), coordinates.getTgtCol());
}

bool King::getHasMoved() {
  return hasMoved;
}

void King::setHasMoved() {
  this->hasMoved = true;
}

bool King::isPieceBlockingPath(Coordinates coordinates) {
  return false;
}

bool King::getIsValidPath(Coordinates coordinates) {
  return false;
}

bool King::getIsInCheck() {
  return this->isInCheck;
}