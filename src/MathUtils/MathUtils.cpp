//
// Created by Ismael Cuevas on 7/31/24.
//

#include "MathUtils/MathUtils.h"

int MathUtils::isPositive(int num) {
  return num < 0;
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
