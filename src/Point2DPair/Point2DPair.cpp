//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/Point2DPair/Point2DPair.h"
Point2DPair::Point2DPair(): _srcRow(0), _srcCol(0), _tgtRow(0), _tgtCol(0) {
}

Point2DPair::Point2DPair(int srcRow, int srcCol, int tgtRow, int tgtCol): _srcRow (srcRow), _srcCol(srcCol), _tgtRow(tgtRow), _tgtCol(tgtCol) {
}

int Point2DPair::getSrcRow() const {
  return _srcRow;
}

int Point2DPair::getSrcCol() const {
  return _srcCol;
}

int Point2DPair::getTgtRow() const {
  return _tgtRow;
}

int Point2DPair::getTgtCol() const {
  return _tgtCol;
}
