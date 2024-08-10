//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/King.h"
bool King::canMoveToTarget(Point2DPair point2DPair) {
}

std::vector<Point2DPair> King::getAdjacentCoordinates(Point2DPair point2DPair) {
}

void King::afterPieceMoved(Point2DPair point2DPair) {
  this->setHasMoved();
  this->chessBoardMediator.getUpdateKingPositionSignal().emit(playerId, point2DPair.getTgtRow(), point2DPair.getTgtCol());
}

bool King::getHasMoved() {
  return hasMoved;
}

void King::setHasMoved() {
  this->hasMoved = true;
}

bool King::isPieceBlockingPath(Point2DPair point2DPair) {
  return false;
}

bool King::getIsValidPath(Point2DPair point2DPair) {
  return false;
}

bool King::getIsInCheck() {
  return this->isInCheck;
}