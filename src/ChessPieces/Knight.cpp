//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Knight.h"
bool Knight::getIsValidPath(Point2DPair coordinates) {
  int srcRow = coordinates.getSrcRow();
  int srcCol = coordinates.getSrcCol();
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  int xAbsDistance = absoluteDistance(srcRow, tgtRow);
  int yAbsDistance = absoluteDistance(srcCol, tgtCol);
  bool isValidPath = (xAbsDistance == 2 && yAbsDistance == 1) || (yAbsDistance == 2 && xAbsDistance == 1);
  return isValidPath;
}

bool Knight::isPieceBlockingPath(Point2DPair coordinates) {
  return false;
}