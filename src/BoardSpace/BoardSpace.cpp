//
// Created by Ismael Cuevas on 7/15/24.
//

#include "../../headers/BoardSpace/BoardSpace.h"

BoardSpace::BoardSpace(ChessPiece *chessPiecePtr, int row, int col) {
  this->chessPiecePtr = chessPiecePtr;
  this->row = row;
  this->col = col;
}

int BoardSpace::getRow() const {
  return row;
}

int BoardSpace::getCol() const {
  return col;
}

ChessPiece* BoardSpace::getChessPiecePtr() {
  return chessPiecePtr;
}

void BoardSpace::setChessPiecePtr(ChessPiece *chessPiecePtr) {
  this->chessPiecePtr = chessPiecePtr;
}

PlayerID BoardSpace::getPlayerId() {
  if (chessPiecePtr != NULL) {
    return chessPiecePtr->getPlayerId();
  }

  return PlayerID::NONE;
}

void BoardSpace::clearChessPiecePtr() {
  if (chessPiecePtr != nullptr) {
    delete chessPiecePtr;
    chessPiecePtr = nullptr;
  }
}
