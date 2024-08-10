//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/ChessPiece.h"
ChessPiece::ChessPiece(PlayerID playerId, PieceType pieceType, ChessBoardMediator & chessBoardMediator): playerId(playerId), pieceType(pieceType), chessBoardMediator(chessBoardMediator) {
}

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

bool ChessPiece::hasValidCoordinates(Point2DPair coordinates) {
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

bool ChessPiece::canMoveToTarget(Point2DPair coordinates) {
  bool hasValidCoordinatesVal = hasValidCoordinates(coordinates);
  if (hasValidCoordinatesVal == false) {
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

bool ChessPiece::isPieceBlockingPath(Point2DPair coordinates) {
  coordinates = getNextCoordinates(coordinates);
  bool isSourceEqualToTarget = MathUtils::isSourceEqualToTarget(coordinates);
  while (!isSourceEqualToTarget) {
    bool isOccupied = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit(coordinates.getSrcRow(), coordinates.getSrcCol());
    if (isOccupied) {
      return true;
    }

    coordinates = getNextCoordinates(coordinates);
    isSourceEqualToTarget = MathUtils::isSourceEqualToTarget(coordinates);
  }

  return false;
}

Point2DPair ChessPiece::getNextCoordinates(Point2DPair coordinates) {
  int tgtRow = coordinates.getTgtRow();
  int tgtCol = coordinates.getTgtCol();
  return Point2DPair(tgtRow, tgtCol, tgtRow, tgtCol);
}

void ChessPiece::afterPieceMoved(Point2DPair coordinates) {
}

bool ChessPiece::getIsValidPath(Point2DPair coordinates) {
  return false;
}