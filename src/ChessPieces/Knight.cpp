//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Knight.h"
bool Knight::getIsValidPath(Coordinates coordinates) {
  int srcRow = coordinates.getSrcRow();
  int srcCol = coordinates.getSrcCol();
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  int xAbsDistance = absoluteDistance(srcRow, srcCol);
  int yAbsDistance = absoluteDistance(tgtRow, tgtCol);
  bool isValidPath = (xAbsDistance == 2 && yAbsDistance == 1) || (yAbsDistance == 2 && xAbsDistance == 1);
  return isValidPath;
}