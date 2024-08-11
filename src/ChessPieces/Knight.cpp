//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Knight.h"

bool Knight::getIsValidPath(Point2DPair point2DPair) {
  int srcRow = point2DPair.getSrcRow();
  int srcCol = point2DPair.getSrcCol();
  int tgtRow = point2DPair.getTgtRow();
  int tgtCol = point2DPair.getTgtCol();
  int xAbsDistance = absoluteDistance(srcRow, tgtRow);
  int yAbsDistance = absoluteDistance(srcCol, tgtCol);
  bool isValidPath = (xAbsDistance == 2 && yAbsDistance == 1) || (yAbsDistance == 2 && xAbsDistance == 1);
  return isValidPath;
}

bool Knight::isPieceBlockingPath(Point2DPair point2DPair) {
  return false;
}