//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/EmptyPiece.h"


bool EmptyPiece::canMoveToTarget(Coordinates coordinates) {
  return false;
}

void EmptyPiece::afterPieceMoved(Coordinates coordinates) {
}

bool EmptyPiece::isPieceBlockingPath(Coordinates coordinates) {
  return false;
}

Coordinates EmptyPiece::getNextCoordinates(Coordinates coordinates) {
  return Coordinates(0, 0, 0, 0);
}
