//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/King.h"

King::King(PlayerID playerId, ChessMediator & chessMediator) : ChessPiece(playerId, PieceType::KING, chessMediator) {
}

void King::afterPieceMoved(Point2DPair point2dPair) {
  setCanCastleToFalse();
  chessMediator.getUpdateKingPositionSignal().emit(playerId, point2dPair.getTgtRow(), point2dPair.getTgtCol());
}

bool King::getCanCastle() {
  return canCastle;
}

void King::setCanCastleToFalse() {
  this->canCastle = false;
}

bool King::isPieceBlockingPath(Point2DPair point2dPair) {
  bool canCheckKing = chessMediator.getCanOpponentsPiecesPutKingInCheckSignal().emit(playerId, point2dPair);
  return canCheckKing;
}

bool King::getIsValidPath(Point2DPair point2dPair) {
  int rowDist = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());
  int colDist = absoluteDistance(point2dPair.getSrcCol(), point2dPair.getTgtCol());
  bool isValidDistance = rowDist <= 1 && colDist <= 1;
  if (isValidDistance) {
    int targetRow = point2dPair.getTgtRow();
    int targetCol = point2dPair.getTgtCol();
    Point2D point2d(targetRow, targetCol);
    bool isValidPath = chessMediator.getIsKingValidPathSignal().emit(playerId, point2d);
    return isValidPath;
  }

  return false;
}

void King::setIsInCheck(bool isInCheck) {
  this->isInCheck = isInCheck;
}

bool King::getIsInCheck() {
  return this->isInCheck;
}

bool King::getIsCheckmate() {
  return isCheckmate;
}

void King::setIsCheckmate(bool value) {
  isCheckmate = value;
}
