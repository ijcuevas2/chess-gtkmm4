//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Rook.h"
bool Rook::canMoveToTarget(Coordinates coordinates) {
  bool baseCanMove = ChessPiece::canMoveToTarget(coordinates);
  if (!baseCanMove) {
    return false;
  }

  int xAbsDiff = absoluteDistance(coordinates.getSrcX(), coordinates.getTgtX());
  int yAbsDiff = absoluteDistance(coordinates.getSrcY(), coordinates.getTgtY());

  bool isValidPath = (xAbsDiff != 0 && yAbsDiff == 0) || (xAbsDiff == 0 && yAbsDiff != 0);
  if (isValidPath) {
    bool isPieceBlockingPathValue = isPieceBlockingPath(coordinates);
    return !isPieceBlockingPathValue;
  }

  return false;
}

void Rook::afterPieceMoved(Coordinates coordinates) {
}
