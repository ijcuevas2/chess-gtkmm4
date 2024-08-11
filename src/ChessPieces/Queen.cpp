//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Queen.h"

bool Queen::getIsValidPath(Point2DPair point2DPair) {
  bool isHorizontalMovable = canMoveHorizontal(point2DPair);
  bool isDiagonalMovable = canMoveDiagonal(point2DPair);
  bool isValidPath = isHorizontalMovable || isDiagonalMovable;
  return isValidPath;
}

bool Queen::canMoveDiagonal(Point2DPair point2DPair) {
  const int xAbsDistance = absoluteDistance(point2DPair.getSrcRow(), point2DPair.getTgtRow());
  const int yAbsDistance = absoluteDistance(point2DPair.getSrcCol(), point2DPair.getTgtCol());
  return xAbsDistance == yAbsDistance;
}

bool Queen::canMoveHorizontal(Point2DPair point2DPair) {
  int xAbsDiff = absoluteDistance(point2DPair.getSrcRow(), point2DPair.getTgtRow());
  int yAbsDiff = absoluteDistance(point2DPair.getSrcCol(), point2DPair.getTgtCol());
  bool canMove = (xAbsDiff != 0 && yAbsDiff == 0) or (xAbsDiff == 0 && yAbsDiff != 0);
  return canMove;
}

Point2DPair Queen::getNextCoordinates(Point2DPair point2DPair) {
  if (canMoveHorizontal(point2DPair)) {
    Point2DPair newCoordinates = MathUtils::getNewHorizontalCoordinates(point2DPair);
    return newCoordinates;
  } else {
    Point2DPair newCoordinates = MathUtils::getNewDiagonalCoordinates(point2DPair);
    return newCoordinates;
  }
}
