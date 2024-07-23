//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Bishop.h"

bool Bishop::canMove(Coordinates coordinates) {
  bool baseCanMove = ChessPiece::canMove(coordinates);
  if (!baseCanMove) {
    return false;
  }

  const int xAbsDistance = absoluteDistance(coordinates.getSrcX(), coordinates.getTgtY());
  const int yAbsDistance = absoluteDistance(coordinates.getSrcY(), coordinates.getTgtX());
  bool isValidPath = xAbsDistance == yAbsDistance;
  if (isValidPath) {
    bool isPieceBlockingPathValue = isPieceBlockingPath(coordinates);
    return !isPieceBlockingPathValue;
  }

  return false;
}

void Bishop::afterPieceMoved(Coordinates coordinates) {
}
