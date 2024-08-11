//
// Created by Ismael Cuevas on 7/27/24.
//

#include "ChessBoardMediator/ChessBoardMediator.h"

sigc::signal<int()> ChessBoardMediator::getCurrentTurnSignal() {
  return getCurrentTurn;
}

sigc::signal<bool(int, int)> ChessBoardMediator::getIsBoardIndexOccupiedSignal() {
  return isBoardIndexOccupied;
}

sigc::signal<int(int, int)> ChessBoardMediator::getMovedTwoSpacesTurnSignal() {
  return getMovedTwoSpacesTurn;
}

sigc::signal<bool(PlayerID)> ChessBoardMediator::getIsTurnPlayerSignal() {
  return isTurnPlayer;
}

sigc::signal<bool(PlayerID, int, int)> ChessBoardMediator::getIsTurnPlayersChessPieceSignal() {
  return isTurnPlayersChessPiece;
}

sigc::signal<void(PlayerID, int, int)> ChessBoardMediator::getUpdateKingPositionSignal() {
  return updateKingPosition;
}

sigc::signal<bool(Point2D)> ChessBoardMediator::getIsKingOccupyingSpaceSignal() {
  return isKingOccupyingSpace;
}

sigc::signal<bool(PlayerID, Point2DPair)> ChessBoardMediator::getCanOpponentsPiecesPutKingInCheckSignal() {
  return canOpponentsPiecesPutKingInCheck;
}
