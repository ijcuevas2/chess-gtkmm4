//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Rook.h"
bool Rook::getIsValidPath(Coordinates coordinates) {
  int srcRow = coordinates.getSrcRow();
  int srcCol = coordinates.getSrcCol();
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  int xAbsDiff = absoluteDistance(srcRow, tgtRow);
  int yAbsDiff = absoluteDistance(srcCol, tgtCol);
  bool isValidPath = (xAbsDiff != 0 && yAbsDiff == 0) || (xAbsDiff == 0 && yAbsDiff != 0);
  return isValidPath;
}

Coordinates Rook::getNextCoordinates(Coordinates coordinates) {
  int newSrcRow = coordinates.getSrcRow();
  int newSrcCol = coordinates.getSrcCol();
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  if (newSrcCol == tgtCol) {
    newSrcRow = MathUtils::getNextCoordinate(newSrcRow, tgtRow);
  } else {
    newSrcCol = MathUtils::getNextCoordinate(newSrcCol, tgtCol);
  }

  Coordinates newCoordinates(newSrcRow, newSrcCol, tgtRow, tgtCol);
  return newCoordinates;
}

void Rook::afterPieceMoved(Coordinates coordinates) {
  setHasMoved();
}

bool Rook::getHasMoved() {
  return hasMoved;
}

void Rook::setHasMoved() {
  hasMoved = true;
}

