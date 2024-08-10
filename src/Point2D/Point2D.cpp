//
// Created by Ismael Cuevas on 8/9/24.
//

#include "Point2D/Point2D.h"
Point2D::Point2D(): row(0), col(0) {
}

Point2D::Point2D(int row, int col): row(row), col(col) {
}

void Point2D::setRow(int row) {
  this->row = row;
}

void Point2D::setCol(int col) {
  this->col = col;
}

int Point2D::getRow() {
  return row;
}

int Point2D::getCol() {
  return col;
}
