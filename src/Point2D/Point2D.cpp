//
// Created by Ismael Cuevas on 8/9/24.
//

#include "Point2D/Point2D.h"

Point2D::Point2D() : row(0), col(0) {
}

Point2D::Point2D(int row, int col) : row(row), col(col) {
}

void Point2D::setRow(int row) {
  this->row = row;
}

void Point2D::setCol(int col) {
  this->col = col;
}

int Point2D::getRow() const {
  return row;
}

int Point2D::getCol() const {
  return col;
}

bool Point2D::operator==(const Point2D & other) const {
  return this->row == other.row && this->col == other.col;
}

size_t Point2D::HashFunction::operator()(const Point2D& p) const {
  return std::hash<int>()(p.getRow()) ^ (std::hash<int>()(p.getCol()) << 1);
}
