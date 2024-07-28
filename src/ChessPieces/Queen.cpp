//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Queen.h"

bool Queen::canMoveToTarget(Coordinates coordinates) {
  bool baseCanMove = ChessPiece::canMoveToTarget(coordinates);
  if (!baseCanMove) {
    return false;
  }

  bool isHorizontalMovable = canMoveHorizontal(coordinates);
  bool isDiagonalMovable = canMoveDiagonal(coordinates);
  bool isValidPath = isHorizontalMovable || isDiagonalMovable;
  if (isValidPath) {
    bool isPieceBlockingPathValue = isPieceBlockingPath(coordinates);
    return !isPieceBlockingPathValue;
  }

  return false;
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

void Queen::afterPieceMoved(Coordinates coordinates) {
}
