//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Knight.h"

bool Knight::canMoveToTarget(Coordinates coordinates) {
  bool baseCanMove = ChessPiece::canMoveToTarget(coordinates);
  if (!baseCanMove) {
    return false;
  }

  int xAbsDistance = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
  int yAbsDistance = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());

  bool isValidPath = (xAbsDistance == 2 && yAbsDistance == 1) || (yAbsDistance == 2 && xAbsDistance == 1);
  return isValidPath;
}

void Knight::afterPieceMoved(Coordinates coordinates) {
}

bool Knight::isPieceBlockingPath(Coordinates coordinates) {
  return false;
}

Coordinates Knight::getNextCoordinates(Coordinates coordinates) {
  return Coordinates(0, 0, 0, 0);
}
