//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/King.h"
bool King::canMoveToTarget(Point2DPair coordinates) {
}

std::vector<Point2DPair> King::getAdjacentCoordinates(Point2DPair coordinates) {
}

void King::afterPieceMoved(Point2DPair coordinates) {
  this->setHasMoved();
  this->chessBoardMediator.getUpdateKingPositionSignal().emit(playerId, coordinates.getTgtRow(), coordinates.getTgtCol());
}

bool King::getHasMoved() {
  return hasMoved;
}

void King::setHasMoved() {
  this->hasMoved = true;
}

bool King::isPieceBlockingPath(Point2DPair coordinates) {
  return false;
}

bool King::getIsValidPath(Point2DPair coordinates) {
  return false;
}

bool King::getIsInCheck() {
  return this->isInCheck;
}