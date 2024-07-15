//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/ChessPiece.h"

int ChessPiece::actualDistance(int source, int dest) {
  return source - dest;
}

int ChessPiece::absoluteDistance(int source, int dest) {
  return std::abs(actualDistance(source, dest));
}

PieceType ChessPiece::getPieceType() {
  return this->pieceType;
}

PlayerID ChessPiece::getPlayerId() {
  return playerId;
}

bool ChessPiece::canMove(Coordinates coordinates) {
  if (coordinates.getSrcX() < 0 || coordinates.getSrcX() > 7) {
    return false;
  }

  if (coordinates.getSrcY() < 0 || coordinates.getSrcY() > 7) {
    return false;
  }

  if (coordinates.getTgtX() < 0 || coordinates.getTgtX() > 7) {
    return false;
  }

  if (coordinates.getTgtY() < 0 || coordinates.getTgtY() > 7) {
    return false;
  }

  return true;
}

