//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Rook.h"
bool Rook::getIsValidPath(Point2DPair coordinates) {
  int srcRow = coordinates.getSrcRow();
  int srcCol = coordinates.getSrcCol();
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  int xAbsDiff = absoluteDistance(srcRow, tgtRow);
  int yAbsDiff = absoluteDistance(srcCol, tgtCol);
  bool isValidPath = (xAbsDiff != 0 && yAbsDiff == 0) || (xAbsDiff == 0 && yAbsDiff != 0);
  return isValidPath;
}

Point2DPair Rook::getNextCoordinates(Point2DPair coordinates) {
  Point2DPair newCoordinates = MathUtils::getNewHorizontalCoordinates(coordinates);
  return newCoordinates;
}

void Rook::afterPieceMoved(Point2DPair coordinates) {
  setHasMoved();
}

bool Rook::getHasMoved() {
  return hasMoved;
}

void Rook::setHasMoved() {
  hasMoved = true;
}

