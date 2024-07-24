//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Bishop.h"

bool Bishop::canMoveToTarget(Coordinates coordinates) {
  bool baseCanMove = ChessPiece::canMoveToTarget(coordinates);
  if (!baseCanMove) {
    return false;
  }

  const int xAbsDistance = absoluteDistance(coordinates.getSrcX(), coordinates.getTgtX());
  const int yAbsDistance = absoluteDistance(coordinates.getSrcY(), coordinates.getTgtY());
  bool isValidPath = xAbsDistance == yAbsDistance;
  if (isValidPath) {
    bool isPieceBlockingPathValue = isPieceBlockingPath(coordinates);
    return !isPieceBlockingPathValue;
  }

  return false;
}

void Bishop::afterPieceMoved(Coordinates coordinates) {
}
