//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/Coordinates/Coordinates.h"
Coordinates::Coordinates(): _srcRow(0), _srcCol(0), _tgtRow(0), _tgtCol(0) {
}

Coordinates::Coordinates(int srcRow, int srcCol, int tgtRow, int tgtCol): _srcRow (srcRow), _srcCol(srcCol), _tgtRow(tgtRow), _tgtCol(tgtCol) {
}

int Coordinates::getSrcRow() const {
  return _srcRow;
}

int Coordinates::getSrcCol() const {
  return _srcCol;
}

int Coordinates::getTgtRow() const {
  return _tgtRow;
}

int Coordinates::getTgtCol() const {
  return _tgtCol;
}

SinglePieceCoordinates::SinglePieceCoordinates(): row(0), col(0) {
}

SinglePieceCoordinates::SinglePieceCoordinates(int row, int col): row(row), col(col) {
}

void SinglePieceCoordinates::setRow(int row) {
  this->row = row;
}

void SinglePieceCoordinates::setCol(int col) {
  this->col = col;
}

int SinglePieceCoordinates::getRow() {
  return row;
}

int SinglePieceCoordinates::getCol() {
  return col;
}