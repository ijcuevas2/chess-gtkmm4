//
// Created by Ismael Cuevas on 9/1/24.
//

#include "ChessMediator/ChessMediator.h"

sigc::signal<void(std::string)> ChessMediator::getAfterFileLoadedSignal() {
  return afterFileLoaded;
}

sigc::signal<void()> ChessMediator::getOpenFileDialogSignal() {
  return openFileDialog;
}

sigc::signal<void()> ChessMediator::getOpenSaveDialogSignal() {
  return openSaveDialog;
}

sigc::signal<void()> ChessMediator::getUpdateUiSignal() {
  return updateUi;
}

sigc::signal<void()> ChessMediator::getOnUndoButtonClicked() {
  return onUndoButtonPressed;
}

sigc::signal<void(bool)> ChessMediator::getUpdateUndoButtonUiSignal() {
  return updateUndoButtonUi;
}

sigc::signal<void()> ChessMediator::getUpdateLabelSignal() {
  return updateLabel;
}

sigc::signal<int()> ChessMediator::getCurrentTurnSignal() {
  return getCurrentTurn;
}

sigc::signal<bool(int, int)> ChessMediator::getIsBoardIndexOccupiedSignal() {
  return isBoardIndexOccupied;
}

sigc::signal<bool(PlayerID)> ChessMediator::getIsTurnPlayerSignal() {
  return isTurnPlayer;
}

sigc::signal<bool(PlayerID, int, int)> ChessMediator::getIsTurnPlayersChessPieceSignal() {
  return isTurnPlayersChessPiece;
}

sigc::signal<void(PlayerID, int, int)> ChessMediator::getUpdateKingPositionSignal() {
  return updateKingPosition;
}

sigc::signal<bool(Point2D)> ChessMediator::getIsKingOccupyingSpaceSignal() {
  return isKingOccupyingSpace;
}

sigc::signal<bool(PlayerID, Point2DPair)> ChessMediator::getCanOpponentsPiecesPutKingInCheckSignal() {
  return canOpponentsPiecesPutKingInCheck;
}

sigc::signal<void(Point2D)> ChessMediator::getSetEnPassantSquareSignal() {
  return setEnPassantSquare;
}

sigc::signal<bool(Point2D)> ChessMediator::getIsEnPassantSquareSignal() {
  return isEnPassantSquare;
}

sigc::signal<void()> ChessMediator::getClearSelectedBoardSpaceUISignal() {
  return clearSelectedBoardSpaceUI;
}
