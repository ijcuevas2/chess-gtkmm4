//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/King.h"

//bool King::canMoveToTarget(Point2DPair point2dPair) {
//}

std::vector<Point2D> King::getAdjacentPoints(Point2D srcPoint2D) {
  std::vector<Point2D> relativePoints = {
          Point2D(0, 1),
          Point2D(1, 1),
          Point2D(1, 0),
          Point2D(1, -1),
          Point2D(0, -1),
          Point2D(-1, -1),
          Point2D(-1, 0),
          Point2D(-1, 1)
  };

  std::vector<Point2D> targetPoints;

  for (int i = 0; i < relativePoints.size(); ++i) {
    Point2D relativePoint2D = relativePoints[i];
    int srcRow = srcPoint2D.getRow();
    int srcCol = srcPoint2D.getCol();
    int newRow = srcRow + relativePoint2D.getRow();
    int newCol = srcCol + relativePoint2D.getCol();
    Point2D targetPoint2D(newRow, newCol);
    if (isValidPoint2D(targetPoint2D)) {
      targetPoints.push_back(targetPoint2D);
    }
  }

  return targetPoints;
}

void King::afterPieceMoved(Point2DPair point2dPair) {
  this->setHasMoved();
  this->chessMediator.getUpdateKingPositionSignal().emit(playerId, point2dPair.getTgtRow(),
                                                         point2dPair.getTgtCol());
}

bool King::getHasMoved() {
  return hasMoved;
}

void King::setHasMoved() {
  this->hasMoved = true;
}

bool King::isPieceBlockingPath(Point2DPair point2dPair) {
  bool canCheckKing = chessMediator.getCanOpponentsPiecesPutKingInCheckSignal().emit(playerId, point2dPair);
  return canCheckKing;
}

bool King::getIsValidPath(Point2DPair point2dPair) {
  int rowDist = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());
  int colDist = absoluteDistance(point2dPair.getSrcCol(), point2dPair.getTgtCol());
  if (rowDist <= 1 && colDist <= 1) {
    return true;
  }

  return false;
}

void King::setIsInCheck(bool isInCheck) {
  this->isInCheck = isInCheck;
}

bool King::getIsInCheck() {
  return this->isInCheck;
}