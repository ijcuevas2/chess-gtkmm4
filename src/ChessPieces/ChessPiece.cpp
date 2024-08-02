//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/ChessPiece.h"

ChessPiece::~ChessPiece() {
}

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

void ChessPiece::setPlayerId(PlayerID playerId) {
  this->playerId = playerId;
}

void ChessPiece::setPieceType(PieceType pieceType) {
  this->pieceType = pieceType;
}

void ChessPiece::copyChessPiece(ChessPiece* chessPiecePtr) {
  this->setPlayerId(chessPiecePtr->playerId);
  this->setPieceType(chessPiecePtr->pieceType);
}

bool ChessPiece::canMoveToTargetHelper(Coordinates coordinates) {
  if (coordinates.getSrcRow() < 0 || coordinates.getSrcRow() > 7) {
    return false;
  }

  if (coordinates.getSrcCol() < 0 || coordinates.getSrcCol() > 7) {
    return false;
  }

  if (coordinates.getTgtRow() < 0 || coordinates.getTgtRow() > 7) {
    return false;
  }

  if (coordinates.getTgtCol() < 0 || coordinates.getTgtCol() > 7) {
    return false;
  }

  return true;
}

bool ChessPiece::canMoveToTarget(Coordinates coordinates) {
  bool canMoveToTargetHelperVal = canMoveToTargetHelper(coordinates);
  if (canMoveToTargetHelperVal == false) {
    return false;
  }

  bool isValidPath = getIsValidPath(coordinates);
  if (isValidPath) {
    bool isClearPath = !isPieceBlockingPath(coordinates);
    bool isTurnPlayer = chessBoardMediator.getIsTurnPlayerSignal().emit(playerId);
    int tgtRow = coordinates.getTgtRow();
    int tgtCol = coordinates.getTgtCol();
    bool isNonTurnPlayerChessPiece = !chessBoardMediator.getIsTurnPlayersChessPieceSignal().emit(playerId, tgtRow, tgtCol);
    return isClearPath && isTurnPlayer && isNonTurnPlayerChessPiece;
  }

  return false;
}

ChessPiece::ChessPiece(PlayerID playerId, PieceType pieceType, ChessBoardMediator & chessBoardMediator): playerId(playerId), pieceType(pieceType), chessBoardMediator(chessBoardMediator) {
}

bool ChessPiece::getIsValidPath(Coordinates coordinates) {
  return false;
}

bool ChessPiece::isPieceBlockingPath(Coordinates coordinates) {
  return false;
}

void ChessPiece::afterPieceMoved(Coordinates coordinates) {
}
