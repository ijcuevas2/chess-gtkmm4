//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Rook.h"
bool Rook::getIsValidPath(Point2DPair point2DPair) {
  int srcRow = point2DPair.getSrcRow();
  int srcCol = point2DPair.getSrcCol();
  int tgtRow = point2DPair.getTgtRow();
  int tgtCol = point2DPair.getTgtCol();
  int xAbsDiff = absoluteDistance(srcRow, tgtRow);
  int yAbsDiff = absoluteDistance(srcCol, tgtCol);
  bool isValidPath = (xAbsDiff != 0 && yAbsDiff == 0) || (xAbsDiff == 0 && yAbsDiff != 0);
  return isValidPath;
}

Point2DPair Rook::getNextCoordinates(Point2DPair point2DPair) {
  Point2DPair newCoordinates = MathUtils::getNewHorizontalCoordinates (point2DPair);
  return newCoordinates;
}

void Rook::afterPieceMoved(Point2DPair point2DPair) {
  setHasMoved();
}

bool Rook::getHasMoved() {
  return hasMoved;
}

void Rook::setHasMoved() {
  hasMoved = true;
}

