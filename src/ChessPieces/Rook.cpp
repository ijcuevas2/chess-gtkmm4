//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Rook.h"

bool Rook::getIsValidPath(Point2DPair point2dPair) {
  int srcRow = point2dPair.getSrcRow();
  int srcCol = point2dPair.getSrcCol();
  int tgtRow = point2dPair.getTgtRow();
  int tgtCol = point2dPair.getTgtCol();
  int xAbsDiff = absoluteDistance(srcRow, tgtRow);
  int yAbsDiff = absoluteDistance(srcCol, tgtCol);
  bool isValidPath = (xAbsDiff != 0 && yAbsDiff == 0) || (xAbsDiff == 0 && yAbsDiff != 0);
  return isValidPath;
}

Point2DPair Rook::getNextCoordinates(Point2DPair point2dPair) {
  Point2DPair newCoordinates = MathUtils::getNewHorizontalCoordinates(point2dPair);
  return newCoordinates;
}

void Rook::afterPieceMoved(Point2DPair point2dPair) {
  setCanCastle(false);
}


bool Rook::getCanCastle() {
  return canCastle;
}

void Rook::setCanCastle(bool value) {
  canCastle = value;
}

std::vector<Point2D> Rook::getMovementTargets(Point2D point2d) {
  std::vector<Point2D> movementTargets = ChessPiece::getCardinalSpaces(point2d);
  return movementTargets;
}
