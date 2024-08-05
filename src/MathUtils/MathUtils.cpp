//
// Created by Ismael Cuevas on 7/31/24.
//

#include "MathUtils/MathUtils.h"

bool MathUtils::isPositive(int num) {
  return num < 0;
}

bool MathUtils::isPositiveVerticalDirection(Coordinates coordinates) {
  int srcRow = coordinates.getSrcRow();
  int tgtRow = coordinates.getTgtRow();
  const int direction = tgtRow - srcRow;
  return direction > 0;
}

int MathUtils::getNextCoordinate(int source, int dest) {
  int distance = dest - source;
  if (isPositive(distance)) {
    source -= 1;
  } else if (source != dest) {
    source += 1;
  }

  return source;
}

bool MathUtils::isSourceEqualToTarget(Coordinates coordinates) {
  bool hasEqualCols = coordinates.getSrcCol() == coordinates.getTgtCol();
  bool hasEqualRows = coordinates.getSrcRow() == coordinates.getTgtRow();
  return hasEqualCols && hasEqualRows;
}

Coordinates MathUtils::getNewDiagonalCoordinates(Coordinates coordinates) {
  int newSrcRow = coordinates.getSrcRow();
  int newSrcCol = coordinates.getSrcCol();
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  newSrcRow = MathUtils::getNextCoordinate(newSrcRow, tgtRow);
  newSrcCol = MathUtils::getNextCoordinate(newSrcCol, tgtCol);
  Coordinates newCoordinates(newSrcRow, newSrcCol, tgtRow, tgtCol);
  return newCoordinates;
}

Coordinates MathUtils::getNewHorizontalCoordinates(Coordinates coordinates) {
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
