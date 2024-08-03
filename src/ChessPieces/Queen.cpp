//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Queen.h"

bool Queen::getIsValidPath(Coordinates coordinates) {
  bool isHorizontalMovable = canMoveHorizontal(coordinates);
  bool isDiagonalMovable = canMoveDiagonal(coordinates);
  bool isValidPath = isHorizontalMovable || isDiagonalMovable;
  return isValidPath;
}

bool Queen::canMoveDiagonal(Coordinates coordinates) {
  const int xAbsDistance = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
  const int yAbsDistance = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
  return xAbsDistance == yAbsDistance;
}

bool Queen::canMoveHorizontal(Coordinates coordinates) {
  int xAbsDiff = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
  int yAbsDiff = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
  bool canMove = (xAbsDiff != 0 && yAbsDiff == 0) or (xAbsDiff == 0 && yAbsDiff != 0);
  return canMove;
}

Coordinates Queen::getNextCoordinates(Coordinates coordinates) {
  if (canMoveHorizontal(coordinates)) {
    Coordinates newCoordinates = MathUtils::getNewHorizontalCoordinates(coordinates);
    return newCoordinates;
  } else {
    Coordinates newCoordinates = MathUtils::getNewDiagonalCoordinates(coordinates);
    return newCoordinates;
  }
}
