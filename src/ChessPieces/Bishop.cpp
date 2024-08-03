//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Bishop.h"

bool Bishop::getIsValidPath(Coordinates coordinates) {
  int srcRow = coordinates.getSrcRow();
  int srcCol = coordinates.getSrcCol();
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  const int xAbsDistance = absoluteDistance(srcRow, tgtRow);
  const int yAbsDistance = absoluteDistance(srcCol, tgtCol);
  bool isValidPathValue = xAbsDistance == yAbsDistance;
  return isValidPathValue;
}

Coordinates Bishop::getNextCoordinates(Coordinates coordinates) {
  int newSrcRow = coordinates.getSrcRow();
  int newSrcCol = coordinates.getSrcCol();
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  newSrcRow = MathUtils::getNextCoordinate(newSrcRow, tgtRow);
  newSrcCol = MathUtils::getNextCoordinate(newSrcCol, tgtCol);
  Coordinates newCoordinates(newSrcRow, newSrcCol, tgtRow, tgtCol);
  return newCoordinates;
}

