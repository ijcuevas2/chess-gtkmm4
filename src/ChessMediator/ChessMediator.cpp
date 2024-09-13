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

sigc::signal<Point2D(Point2DPair)> ChessMediator::getEnPassantCoordinatesSignal() {
  return getEnPassantCoordinates;
}

sigc::signal<void(Point2DPair)> ChessMediator::getClearEnPassantCaptureSpaceSignal() {
  return clearEnPassantCaptureSpace;
}

sigc::signal<void()> ChessMediator::getClearEnPassantSquareSignal() {
  return clearEnPassantSquare;
}

sigc::signal<void(std::string)> ChessMediator::getSaveStateToFileSignal() {
  return saveStateToFile;
}

sigc::signal<Point2D()> ChessMediator::getEnPassantSquareSignal() {
  return getEnPassantSquare;
}

sigc::signal<Point2D(std::string)> ChessMediator::getPointFromAlgebraicNotationSignal() {
  return getPointFromAlgebraicNotation;
}

sigc::signal<Point2DPair(std::string, std::string)> ChessMediator::getSetPrevMoveFromStringSignal() {
  return setPrevMoveFromString;
}

sigc::signal<void(Point2DPair)> ChessMediator::getSetPrevMoveSignal() {
  return getSetPrevMove;
}

sigc::signal<bool(PlayerID)> ChessMediator::getIsKingInCheckSignal() {
  return isKingInCheck;
}

sigc::signal<bool(PlayerID, Point2D)> ChessMediator::getIsKingValidPathSignal() {
  return isKingValidPath;
}

sigc::signal<PlayerID()> ChessMediator::getTurnPlayerIdSignal() {
  return turnPlayerId;
}

sigc::signal<PlayerID()> ChessMediator::getOpponentTurnPlayerIdSignal() {
  return opponentPlayerId;
}

sigc::signal<void()> ChessMediator::getOpenCheckmateDialogSignal() {
  return openCheckmateDialog;
}

sigc::signal<void()> ChessMediator::getNewGameSignal() {
  return newGame;
}
