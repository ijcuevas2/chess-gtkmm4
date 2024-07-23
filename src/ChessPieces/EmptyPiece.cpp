//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/EmptyPiece.h"


bool EmptyPiece::canMove(Coordinates coordinates) {
  return false;
}

void EmptyPiece::afterPieceMoved(Coordinates coordinates) {
}