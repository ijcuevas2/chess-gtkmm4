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

void ChessPiece::copyChessPiece(ChessPiece *chessPiecePtr) {
  this->setPlayerId(chessPiecePtr->playerId);
  this->setPieceType(chessPiecePtr->pieceType);
}

bool ChessPiece::isValidPoint2D(Point2D point2D) {
  if (point2D.getRow() < 0 || point2D.getRow() > 7) {
    return false;
  }

  if (point2D.getCol() < 0 || point2D.getCol() > 7) {
    return false;
  }

  return true;
}

bool ChessPiece::isValidPoint2DPair(Point2DPair point2DPair) {
  if (point2DPair.getSrcRow() < 0 || point2DPair.getSrcRow() > 7) {
    return false;
  }

  if (point2DPair.getSrcCol() < 0 || point2DPair.getSrcCol() > 7) {
    return false;
  }

  if (point2DPair.getTgtRow() < 0 || point2DPair.getTgtRow() > 7) {
    return false;
  }

  if (point2DPair.getTgtCol() < 0 || point2DPair.getTgtCol() > 7) {
    return false;
  }

  return true;
}

bool ChessPiece::canMoveToTarget(Point2DPair point2DPair) {
  bool hasValidCoordinatesVal = isValidPoint2DPair(point2DPair);
  if (hasValidCoordinatesVal == false) {
    return false;
  }

  bool isValidPath = getIsValidPath(point2DPair);
  if (isValidPath) {
    bool isClearPath = !isPieceBlockingPath(point2DPair);
    bool isTurnPlayer = chessMediator.getIsTurnPlayerSignal().emit(playerId);
    int tgtRow = point2DPair.getTgtRow();
    int tgtCol = point2DPair.getTgtCol();
    bool isNonTurnPlayerChessPiece = !chessMediator.getIsTurnPlayersChessPieceSignal().emit(playerId, tgtRow,
                                                                                            tgtCol);
    return isClearPath && isTurnPlayer && isNonTurnPlayerChessPiece;
  }

  return false;
}

bool ChessPiece::isPieceBlockingPath(Point2DPair point2DPair) {
  point2DPair = getNextCoordinates(point2DPair);
  bool isSourceEqualToTarget = MathUtils::isSourceEqualToTarget(point2DPair);
  while (!isSourceEqualToTarget) {
    bool isOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(point2DPair.getSrcRow(),
                                                                         point2DPair.getSrcCol());
    if (isOccupied) {
      return true;
    }

    point2DPair = getNextCoordinates(point2DPair);
    isSourceEqualToTarget = MathUtils::isSourceEqualToTarget(point2DPair);
  }

  return false;
}

Point2DPair ChessPiece::getNextCoordinates(Point2DPair point2DPair) {
  int tgtRow = point2DPair.getTgtRow();
  int tgtCol = point2DPair.getTgtCol();
  return Point2DPair(tgtRow, tgtCol, tgtRow, tgtCol);
}

void ChessPiece::afterPieceMoved(Point2DPair point2DPair) {
}

bool ChessPiece::getIsValidPath(Point2DPair point2DPair) {
  return false;
}