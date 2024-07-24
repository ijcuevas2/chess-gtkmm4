//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Knight.h"

bool Knight::canMoveToTarget(Coordinates coordinates) {
  bool baseCanMove = ChessPiece::canMoveToTarget(coordinates);
  if (!baseCanMove) {
    return false;
  }

  int xAbsDistance = absoluteDistance(coordinates.getSrcX(), coordinates.getTgtX());
  int yAbsDistance = absoluteDistance(coordinates.getSrcY(), coordinates.getTgtY());

  bool isValidPath = (xAbsDistance == 2 && yAbsDistance == 1) || (yAbsDistance == 2 && xAbsDistance == 1);
  return isValidPath;
}

void Knight::afterPieceMoved(Coordinates coordinates) {
}
