//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/ChessPiece.h"

ChessPiece::ChessPiece(PlayerID playerId, PieceType pieceType, ChessMediator & chessMediator) : playerId(
        playerId), pieceType(pieceType), chessMediator(chessMediator) {
}

ChessPiece::~ChessPiece() {
}

int ChessPiece::actualDistance(int source, int dest) {
  return dest - source;
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

void ChessPiece::copyChessPiece(ChessPiece *chessPiecePtr) {
  this->setPlayerId(chessPiecePtr->playerId);
  this->setPieceType(chessPiecePtr->pieceType);
}

bool ChessPiece::isValidPoint2D(Point2D point2d) {
  if (point2d.getRow() < 0 || point2d.getRow() > 7) {
    return false;
  }

  if (point2d.getCol() < 0 || point2d.getCol() > 7) {
    return false;
  }

  return true;
}

bool ChessPiece::isValidPoint2DPair(Point2DPair point2dPair) {
  if (point2dPair.getSrcRow() < 0 || point2dPair.getSrcRow() > 7) {
    return false;
  }

  if (point2dPair.getSrcCol() < 0 || point2dPair.getSrcCol() > 7) {
    return false;
  }

  if (point2dPair.getTgtRow() < 0 || point2dPair.getTgtRow() > 7) {
    return false;
  }

  if (point2dPair.getTgtCol() < 0 || point2dPair.getTgtCol() > 7) {
    return false;
  }

  return true;
}

bool ChessPiece::canMoveToTarget(Point2DPair point2dPair) {
  bool hasValidCoordinatesVal = isValidPoint2DPair(point2dPair);
  if (hasValidCoordinatesVal == false) {
    return false;
  }

  bool isValidPath = getIsValidPath(point2dPair);
  if (isValidPath) {
    bool isClearPath = !isPieceBlockingPath(point2dPair);
    bool isTurnPlayer = chessMediator.getIsTurnPlayerSignal().emit(playerId);
    int tgtRow = point2dPair.getTgtRow();
    int tgtCol = point2dPair.getTgtCol();
    bool isNonTurnPlayerChessPiece = !chessMediator.getIsTurnPlayersChessPieceSignal().emit(playerId, tgtRow, tgtCol);
    return isClearPath && isTurnPlayer && isNonTurnPlayerChessPiece;
  }

  return false;
}

bool ChessPiece::isPieceBlockingPath(Point2DPair point2dPair) {
  point2dPair = getNextCoordinates(point2dPair);
  bool isSourceEqualToTarget = MathUtils::isSourceEqualToTarget(point2dPair);
  while (!isSourceEqualToTarget) {
    bool isOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(point2dPair.getSrcRow(),
                                                                         point2dPair.getSrcCol());
    if (isOccupied) {
      return true;
    }

    point2dPair = getNextCoordinates(point2dPair);
    isSourceEqualToTarget = MathUtils::isSourceEqualToTarget(point2dPair);
  }

  return false;
}

Point2DPair ChessPiece::getNextCoordinates(Point2DPair point2dPair) {
  int tgtRow = point2dPair.getTgtRow();
  int tgtCol = point2dPair.getTgtCol();
  return Point2DPair(tgtRow, tgtCol, tgtRow, tgtCol);
}

void ChessPiece::afterPieceMoved(Point2DPair point2dPair) {
}

bool ChessPiece::getIsValidPath(Point2DPair point2dPair) {
  return false;
}