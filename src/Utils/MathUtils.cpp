//
// Created by Ismael Cuevas on 7/31/24.
//

#include "../../headers/Utils/MathUtils.h"

bool MathUtils::isPositive(int num) {
  return num < 0;
}

bool MathUtils::isPositiveVerticalDirection(Point2DPair point2DPair) {
  int srcRow = point2DPair.getSrcRow();
  int tgtRow = point2DPair.getTgtRow();
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

bool MathUtils::isSourceEqualToTarget(Point2DPair point2DPair) {
  bool hasEqualCols = point2DPair.getSrcCol() == point2DPair.getTgtCol();
  bool hasEqualRows = point2DPair.getSrcRow() == point2DPair.getTgtRow();
  return hasEqualCols && hasEqualRows;
}

Point2DPair MathUtils::getNewDiagonalCoordinates(Point2DPair point2DPair) {
  int newSrcRow = point2DPair.getSrcRow();
  int newSrcCol = point2DPair.getSrcCol();
  int tgtRow = point2DPair.getTgtRow();
  int tgtCol = point2DPair.getTgtCol();
  newSrcRow = MathUtils::getNextCoordinate(newSrcRow, tgtRow);
  newSrcCol = MathUtils::getNextCoordinate(newSrcCol, tgtCol);
  Point2DPair newCoordinates(newSrcRow, newSrcCol, tgtRow, tgtCol);
  return newCoordinates;
}

Point2DPair MathUtils::getNewHorizontalCoordinates(Point2DPair point2DPair) {
  int newSrcRow = point2DPair.getSrcRow();
  int newSrcCol = point2DPair.getSrcCol();
  int tgtRow = point2DPair.getTgtRow();
  int tgtCol = point2DPair.getTgtCol();
  if (newSrcCol == tgtCol) {
    newSrcRow = MathUtils::getNextCoordinate(newSrcRow, tgtRow);
  } else {
    newSrcCol = MathUtils::getNextCoordinate(newSrcCol, tgtCol);
  }

  Point2DPair newCoordinates(newSrcRow, newSrcCol, tgtRow, tgtCol);
  return newCoordinates;
}
