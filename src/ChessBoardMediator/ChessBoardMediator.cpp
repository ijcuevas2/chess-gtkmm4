//
// Created by Ismael Cuevas on 7/27/24.
//

#include "ChessBoardMediator/ChessBoardMediator.h"
sigc::signal<void(const Coordinates &)> ChessBoardMediator::getPawnMovementSignal() {
  return handlePawnMovement;
}

sigc::signal<void(const Coordinates &)> ChessBoardMediator::getKingMovementSignal() {
  return handleKingMovement;
}

sigc::signal<int()> ChessBoardMediator::getCurrentTurnSignal() {
  return getCurrentTurn;
}

sigc::signal<bool(int, int)> ChessBoardMediator::getIsBoardIndexOccupiedSignal() {
  return isBoardIndexOccupied;
}

sigc::signal<int(int, int)> ChessBoardMediator::getMovedTwoSpacesTurnSignal() {
  return getMovedTwoSpacesTurn;
}
