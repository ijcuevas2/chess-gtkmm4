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

void Knight::setMovementTargets(Point2D point2d) {
  std::vector<std::vector<int>> offsets = {{1, 2},
                                           {-1, 2},
                                           {1, -2},
                                           {-1, -2},
                                           {2, 1},
                                           {2, -1},
                                           {-2, 1},
                                           {-2, -1}};

  for (std::vector<int> offset : offsets) {
    int targetRow = point2d.getRow() + offset[0];
    int targetCol = point2d.getCol() + offset[1];
    Point2D targetPoint(targetRow, targetCol);
    bool canAddSpaceBool = canAddSpace(targetPoint);
    if (canAddSpaceBool) {
      captureTargets.push_back(targetPoint);
    }
  }
}
