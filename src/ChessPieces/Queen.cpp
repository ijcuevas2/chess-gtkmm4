//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Queen.h"

bool Queen::getIsValidPath(Point2DPair point2dPair) {
  bool isHorizontalMovable = canMoveHorizontal(point2dPair);
  bool isDiagonalMovable = canMoveDiagonal(point2dPair);
  bool isValidPath = isHorizontalMovable || isDiagonalMovable;
  return isValidPath;
}

bool Queen::canMoveDiagonal(Point2DPair point2dPair) {
  const int xAbsDistance = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());
  const int yAbsDistance = absoluteDistance(point2dPair.getSrcCol(), point2dPair.getTgtCol());
  return xAbsDistance == yAbsDistance;
}

bool Queen::canMoveHorizontal(Point2DPair point2dPair) {
  int xAbsDiff = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());
  int yAbsDiff = absoluteDistance(point2dPair.getSrcCol(), point2dPair.getTgtCol());
  bool canMove = (xAbsDiff != 0 && yAbsDiff == 0) or (xAbsDiff == 0 && yAbsDiff != 0);
  return canMove;
}

Point2DPair Queen::getNextCoordinates(Point2DPair point2dPair) {
  if (canMoveHorizontal(point2dPair)) {
    Point2DPair newCoordinates = MathUtils::getNewHorizontalCoordinates(point2dPair);
    return newCoordinates;
  } else {
    Point2DPair newCoordinates = MathUtils::getNewDiagonalCoordinates(point2dPair);
    return newCoordinates;
  }
}
