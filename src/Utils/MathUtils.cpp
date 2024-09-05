//
// Created by Ismael Cuevas on 7/31/24.
//

#include "../../headers/Utils/MathUtils.h"

bool MathUtils::isPositive(int num) {
  return num < 0;
}

bool MathUtils::isPositiveVerticalDirection(Point2DPair point2dPair) {
  int srcRow = point2dPair.getSrcRow();
  int tgtRow = point2dPair.getTgtRow();
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

bool MathUtils::isSourceEqualToTarget(Point2DPair point2dPair) {
  bool hasEqualCols = point2dPair.getSrcCol() == point2dPair.getTgtCol();
  bool hasEqualRows = point2dPair.getSrcRow() == point2dPair.getTgtRow();
  return hasEqualCols && hasEqualRows;
}

Point2DPair MathUtils::getNewDiagonalCoordinates(Point2DPair point2dPair) {
  int newSrcRow = point2dPair.getSrcRow();
  int newSrcCol = point2dPair.getSrcCol();
  int tgtRow = point2dPair.getTgtRow();
  int tgtCol = point2dPair.getTgtCol();
  newSrcRow = MathUtils::getNextCoordinate(newSrcRow, tgtRow);
  newSrcCol = MathUtils::getNextCoordinate(newSrcCol, tgtCol);
  Point2DPair newCoordinates(newSrcRow, newSrcCol, tgtRow, tgtCol);
  return newCoordinates;
}

Point2DPair MathUtils::getNewHorizontalCoordinates(Point2DPair point2dPair) {
  int newSrcRow = point2dPair.getSrcRow();
  int newSrcCol = point2dPair.getSrcCol();
  int tgtRow = point2dPair.getTgtRow();
  int tgtCol = point2dPair.getTgtCol();
  if (newSrcCol == tgtCol) {
    newSrcRow = MathUtils::getNextCoordinate(newSrcRow, tgtRow);
  } else {
    newSrcCol = MathUtils::getNextCoordinate(newSrcCol, tgtCol);
  }

  Point2DPair newCoordinates(newSrcRow, newSrcCol, tgtRow, tgtCol);
  return newCoordinates;
}

int MathUtils::charToDigit(char c) {
  if (std::isdigit(c)) {
    return c - '0';
  }
  throw std::invalid_argument("Character is not a digit");
}

bool MathUtils::isValidPoint2D(Point2D point2d) {
  int row = point2d.getRow();
  int col = point2d.getCol();
  if (row < 0 || row > 7 || col < 0 || col > 7) {
    return false;
  }

  return true;
}

std::vector<Point2D> MathUtils::getAdjacentKingPoints(Point2D srcPoint2D) {
  std::vector<Point2D> relativePoints = {
          Point2D(0, 1),
          Point2D(1, 1),
          Point2D(1, 0),
          Point2D(1, -1),
          Point2D(0, -1),
          Point2D(-1, -1),
          Point2D(-1, 0),
          Point2D(-1, 1)
  };

  std::vector<Point2D> targetPoints;

  for (int i = 0; i < relativePoints.size(); ++i) {
    Point2D relativePoint2D = relativePoints[i];
    int srcRow = srcPoint2D.getRow();
    int srcCol = srcPoint2D.getCol();
    int newRow = srcRow + relativePoint2D.getRow();
    int newCol = srcCol + relativePoint2D.getCol();
    Point2D targetPoint2D(newRow, newCol);
    if (isValidPoint2D(targetPoint2D)) {
      targetPoints.push_back(targetPoint2D);
    }
  }

  return targetPoints;
}
