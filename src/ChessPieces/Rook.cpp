//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Rook.h"
//bool Rook::canMoveToTarget(Coordinates coordinates) {
//  bool baseCanMove = ChessPiece::canMoveToTarget(coordinates);
//  if (!baseCanMove) {
//    return false;
//  }
//
//  int xAbsDiff = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
//  int yAbsDiff = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
//
//  bool isValidPath = (xAbsDiff != 0 && yAbsDiff == 0) || (xAbsDiff == 0 && yAbsDiff != 0);
//  if (isValidPath) {
//    bool isPieceBlockingPathValue = isPieceBlockingPath(coordinates);
//    return !isPieceBlockingPathValue;
//  }
//
//  return false;
//}

bool Rook::getHasMoved() {
  return hasMoved;
}

void Rook::setHasMoved() {
  hasMoved = true;
}

void Rook::afterPieceMoved(Coordinates coordinates) {
  setHasMoved();
}

bool Rook::isPieceBlockingPath(Coordinates coordinates) {
  return false;
}

Coordinates Rook::getNextCoordinates(Coordinates coordinates) {
  return Coordinates(0, 0, 0, 0);
}
