//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Queen.h"

bool Queen::getIsValidPath(Point2DPair coordinates) {
  bool isHorizontalMovable = canMoveHorizontal(coordinates);
  bool isDiagonalMovable = canMoveDiagonal(coordinates);
  bool isValidPath = isHorizontalMovable || isDiagonalMovable;
  return isValidPath;
}

bool Queen::canMoveDiagonal(Point2DPair coordinates) {
  const int xAbsDistance = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
  const int yAbsDistance = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
  return xAbsDistance == yAbsDistance;
}

bool Queen::canMoveHorizontal(Point2DPair coordinates) {
  int xAbsDiff = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
  int yAbsDiff = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
  bool canMove = (xAbsDiff != 0 && yAbsDiff == 0) or (xAbsDiff == 0 && yAbsDiff != 0);
  return canMove;
}

Point2DPair Queen::getNextCoordinates(Point2DPair coordinates) {
  if (canMoveHorizontal(coordinates)) {
    Point2DPair newCoordinates = MathUtils::getNewHorizontalCoordinates(coordinates);
    return newCoordinates;
  } else {
    Point2DPair newCoordinates = MathUtils::getNewDiagonalCoordinates(coordinates);
    return newCoordinates;
  }
}
