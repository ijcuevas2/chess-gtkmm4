//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Knight.h"

bool Knight::getIsValidPath(Point2DPair point2dPair) {
  int srcRow = point2dPair.getSrcRow();
  int srcCol = point2dPair.getSrcCol();
  int tgtRow = point2dPair.getTgtRow();
  int tgtCol = point2dPair.getTgtCol();
  int xAbsDistance = absoluteDistance(srcRow, tgtRow);
  int yAbsDistance = absoluteDistance(srcCol, tgtCol);
  bool isValidPath = (xAbsDistance == 2 && yAbsDistance == 1) || (yAbsDistance == 2 && xAbsDistance == 1);
  return isValidPath;
}

bool Knight::isPieceBlockingPath(Point2DPair point2dPair) {
  return false;
}