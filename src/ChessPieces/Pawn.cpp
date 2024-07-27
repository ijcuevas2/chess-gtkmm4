//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Pawn.h"

bool Pawn::canMoveToTarget(Coordinates coordinates) {
  return true;
}

void Pawn::afterPieceMoved(Coordinates coordinates) {
}

void Pawn::setMovedTwoSpacesTurn(Coordinates coordinates) {
  int absoluteDistanceValue = absoluteDistance(coordinates.getSrcY(), coordinates.getTgtY());
  bool movedTwoSpacesResult = absoluteDistanceValue == 2;
  if (movedTwoSpacesResult) {
    //this->movedTwoSpacesTurn = ChessMovementUtils::getCurrentTurn();
  }
}

int Pawn::getMovedTwoSpacesTurn() {
  return this->movedTwoSpacesTurn;
}

bool Pawn::isCorrectDirection(Coordinates coordinates) {
  int yDistance = coordinates.getTgtY() - coordinates.getSrcY();
  if (playerId == PlayerID::PLAYER_LIGHT) {
    return yDistance < 0;
  } else if (playerId == PlayerID::PLAYER_DARK) {
    return yDistance > 0;
  }

  return false;
}