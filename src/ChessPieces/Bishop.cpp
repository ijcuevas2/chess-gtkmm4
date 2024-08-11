//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Bishop.h"

bool Bishop::getIsValidPath(Point2DPair point2DPair) {
  int srcRow = point2DPair.getSrcRow();
  int srcCol = point2DPair.getSrcCol();
  int tgtRow = point2DPair.getTgtRow();
  int tgtCol = point2DPair.getTgtCol();
  const int xAbsDistance = absoluteDistance(srcRow, tgtRow);
  const int yAbsDistance = absoluteDistance(srcCol, tgtCol);
  bool isValidPathValue = xAbsDistance == yAbsDistance;
  return isValidPathValue;
}

Point2DPair Bishop::getNextCoordinates(Point2DPair point2DPair) {
  Point2DPair newCoordinates = MathUtils::getNewDiagonalCoordinates(point2DPair);
  return newCoordinates;
}

