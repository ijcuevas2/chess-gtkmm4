//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/King.h"

King::King(PlayerID playerId, ChessMediator & chessMediator) : ChessPiece(playerId, PieceType::KING, chessMediator) {
}

void King::afterPieceMoved(Point2DPair point2dPair) {
  setCanCastle(false);
  chessMediator.getUpdateKingPositionSignal().emit(playerId, point2dPair.getTgtRow(), point2dPair.getTgtCol());
  bool wasCastlingMove = wasCastlingMoveExecuted(point2dPair);
  if (wasCastlingMove) {
    Point2D point2d(point2dPair.getTgtRow(), point2dPair.getTgtCol());
    chessMediator.getMoveRookAfterCastleSignal().emit(point2d);
  }
}

bool King::getCanCastle() {
  return canCastle;
}

void King::setCanCastle(bool value) {
  this->canCastle = value;
}

bool King::isPieceBlockingPath(Point2DPair point2dPair) {
  bool canCheckKing = chessMediator.getCanOpponentsPiecesPutKingInCheckSignal().emit(playerId, point2dPair);
  return canCheckKing;
}

bool King::wasCastlingMoveExecuted(Point2DPair point2dPair) {
  int srcCol = point2dPair.getSrcCol();
  int tgtCol = point2dPair.getTgtCol();
  int distance = absoluteDistance(srcCol, tgtCol);
  if (distance == 2 || distance == 3) {
   return true;
  }

  return false;
}

bool King::isCastlingMove(Point2DPair point2dPair) {
  if (!canCastle) {
    return false;
  }

  int srcRow = point2dPair.getSrcRow();
  int srcCol = point2dPair.getSrcCol();
  int tgtRow = point2dPair.getTgtRow();
  int tgtCol = point2dPair.getTgtCol();

  int rowDist = absoluteDistance(srcRow, tgtRow);
  int colDist = actualDistance(srcCol, tgtCol);

  if (rowDist == 0) {
    if (colDist == 2) {
      bool isEmptyBishopSpace = !chessMediator.getIsBoardIndexOccupiedSignal().emit(srcRow, srcCol + 1);
      bool isEmptyKnightSpace = !chessMediator.getIsBoardIndexOccupiedSignal().emit(srcRow, srcCol + 2);
      Point2D rookPoint2d(srcRow, srcCol + 3);
      bool canRookCastle = chessMediator.getRookCanCastleSignal().emit(rookPoint2d);
      return isEmptyBishopSpace && isEmptyKnightSpace && canRookCastle;
    } else if (colDist == -2) {
      bool isEmptyQueenSpace = !chessMediator.getIsBoardIndexOccupiedSignal().emit(srcRow, srcCol - 1);
      bool isEmptyBishopSpace = !chessMediator.getIsBoardIndexOccupiedSignal().emit(srcRow, srcCol - 2);
      bool isEmptyKnightSpace = !chessMediator.getIsBoardIndexOccupiedSignal().emit(srcRow, srcCol - 3);
      Point2D rookPoint2d(srcRow, srcCol - 4);
      bool canRookCastle = chessMediator.getRookCanCastleSignal().emit(rookPoint2d);
      return isEmptyQueenSpace && isEmptyBishopSpace && isEmptyKnightSpace && canRookCastle;
    }
  }

  return false;
}

bool King::getIsValidPath(Point2DPair point2dPair) {
  int rowDist = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());
  int colDist = absoluteDistance(point2dPair.getSrcCol(), point2dPair.getTgtCol());

  bool isCastlingMoveBool = isCastlingMove(point2dPair);
  bool isValidDistance = (rowDist <= 1 && colDist <= 1 || isCastlingMoveBool);
  if (isValidDistance) {
    int targetRow = point2dPair.getTgtRow();
    int targetCol = point2dPair.getTgtCol();
    Point2D point2d(targetRow, targetCol);
    bool isValidPath = chessMediator.getIsKingValidPathSignal().emit(playerId, point2d);
    return isValidPath;
  }

  return false;
}

std::vector<Point2D> King::getMovementTargets(Point2D point2d) {
  std::vector<std::vector<int>> offsets = {{1, 1},
                                           {-1, 1},
                                           {1, -1},
                                           {-1, -1},
                                           {1, 0},
                                           {0, 1},
                                           {-1, 0},
                                           {0, -1}};

  std::vector<Point2D> movementTargets;
  for (std::vector<int> offset : offsets) {
    int targetRow = point2d.getRow() + offset[0];
    int targetCol = point2d.getCol() + offset[1];
    Point2DPair point2DPair(point2d.getRow(), point2d.getCol(), targetRow, targetCol);
    bool canMoveToTargetBool = canMoveToTarget(point2DPair);
    if (canMoveToTargetBool) {
      Point2D targetPoint(targetRow, targetCol);
      movementTargets.push_back(targetPoint);
    }
  }

  return movementTargets;
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
