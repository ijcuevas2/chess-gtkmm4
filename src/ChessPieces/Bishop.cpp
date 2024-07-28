//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Bishop.h"

bool Bishop::canMoveToTarget(Coordinates coordinates) {
  bool baseCanMove = ChessPiece::canMoveToTarget(coordinates);
  if (!baseCanMove) {
    return false;
  }

  const int xAbsDistance = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
  const int yAbsDistance = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
  bool isValidPath = xAbsDistance == yAbsDistance;
  if (isValidPath) {
    bool isPieceBlockingPathValue = isPieceBlockingPath(coordinates);
    return !isPieceBlockingPathValue;
  }

  return false;
}

void Bishop::afterPieceMoved(Coordinates coordinates) {
}
