//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Pawn.h"

bool Pawn::getIsValidPath(Point2DPair point2dPair) {
  bool isCorrectDirectionValue = isCorrectDirection(point2dPair);
  if (!isCorrectDirectionValue) {
    return false;
  }

  if (isFirstMove) {
    bool canMove = canMoveFirstTurn(point2dPair);
    return canMove;
  } else {
    bool canCaptureValue = canCapture(point2dPair);
    bool canMoveSingleSpaceValue = canMoveSingleSpaceForward(point2dPair);
    return canCaptureValue || canMoveSingleSpaceValue;
  }
}

bool Pawn::canMoveFirstTurn(Point2DPair point2dPair) {
  int xAbsDistance = absoluteDistance(point2dPair.getSrcCol(), point2dPair.getTgtCol());
  int yAbsDistance = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());

  bool canMove = xAbsDistance == 0 && yAbsDistance <= 2;
  return canMove;
}

void Pawn::afterPieceMoved(Point2DPair point2dPair) {
  if (isFirstMove) {
    setUsedFirstMove();
    setEnpassantSquare(point2dPair);
  }
}

void Pawn::clearEnPassantCaptureSquare(Point2DPair point2dPair) {
  bool isEnPassantCaptureBool = isEnPassantCapture(point2dPair);
  if (isEnPassantCaptureBool) {
    chessMediator.getClearEnPassantCaptureSpaceSignal().emit(point2dPair);
  }
}

void Pawn::setEnpassantSquare(Point2DPair point2dPair) {
  bool movedTwoSpacesResult = isMovingByTwoSpaces(point2dPair);
  if (movedTwoSpacesResult) {
    Point2D point2D(point2dPair.getTgtRow(), point2dPair.getTgtCol());
    chessMediator.getSetEnPassantSquareSignal().emit(point2D);
  }
}

bool Pawn::isMovingByTwoSpaces(Point2DPair point2dPair) {
  int absoluteDistanceValue = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());
  bool movedTwoSpacesResult = absoluteDistanceValue == 2;
  return movedTwoSpacesResult;
}

bool Pawn::isCorrectDirection(Point2DPair point2dPair) {
  int yDistance = point2dPair.getTgtRow() - point2dPair.getSrcRow();
  if (playerId == PlayerID::PLAYER_WHITE) {
    return yDistance < 0;
  } else if (playerId == PlayerID::PLAYER_BLACK) {
    return yDistance > 0;
  }

  return false;
}

bool Pawn::canCapture(Point2DPair point2dPair) {
  bool isDiagonalMoveValue = isDiagonalMove(point2dPair);
  if (isDiagonalMoveValue) {
    bool canDiagonalCaptureValue = canDiagonalCapture(point2dPair);
    if (canDiagonalCaptureValue) {
      return true;
    }

    bool canEnPassantCaptureValue = isEnPassantCapture(point2dPair);
    if (canEnPassantCaptureValue) {
      return true;
    }
  }

  return false;
}

bool Pawn::canDiagonalCapture(Point2DPair point2dPair) {
  bool isIndexOccupiedResult = chessMediator.getIsBoardIndexOccupiedSignal().emit(point2dPair.getTgtRow(), point2dPair.getTgtCol());
  return isIndexOccupiedResult;
}

bool Pawn::isDiagonalMove(Point2DPair point2dPair) {
  int xAbsDistance = absoluteDistance(point2dPair.getSrcCol(), point2dPair.getTgtCol());
  int yAbsDistance = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());
  bool isDiagonalMoveResult = xAbsDistance == 1 && yAbsDistance == 1;
  return isDiagonalMoveResult;
}

bool Pawn::canMoveSingleSpaceForward(Point2DPair point2dPair) {
  int xAbsDistance = absoluteDistance(point2dPair.getSrcCol(), point2dPair.getTgtCol());
  int yAbsDistance = absoluteDistance(point2dPair.getSrcRow(), point2dPair.getTgtRow());

  bool isTargetOccupiedValue = chessMediator.getIsBoardIndexOccupiedSignal().emit(point2dPair.getTgtRow(),
                                                                                  point2dPair.getTgtCol());
  bool canMove = xAbsDistance == 0 && yAbsDistance < 2 && !isTargetOccupiedValue;
  return canMove;
}

int Pawn::getCapturingPieceEnpassantRow() {
  if (playerId == PlayerID::PLAYER_WHITE) {
    return static_cast<int>(PawnEnpassantRow::WHITE_PAWN_CAPTURING_ROW);
  }

  return static_cast<int>(PawnEnpassantRow::BLACK_PAWN_CAPTURING_ROW);
}

bool Pawn::isEnPassantCapture(Point2DPair point2dPair) {
  Point2D point2D = chessMediator.getEnPassantCoordinatesSignal().emit(point2dPair);
  bool hasEnPassantCaptureTarget = chessMediator.getIsEnPassantSquareSignal().emit(point2D);
  int enPassantRow = getCapturingPieceEnpassantRow();
  bool hasEnPassantRow = point2dPair.getSrcRow() == enPassantRow;
  bool canEnPassantCaptureBool = hasEnPassantRow && hasEnPassantCaptureTarget;
  return canEnPassantCaptureBool;
}

void Pawn::setUsedFirstMove() {
  this->isFirstMove = false;
}

bool Pawn::isPieceBlockingPath(Point2DPair point2dPair) {
  bool positiveVerticalDirection = MathUtils::isPositiveVerticalDirection(point2dPair);
  int direction = positiveVerticalDirection ? 1 : -1;
  int nextRowCoordinate = point2dPair.getSrcRow() + direction;
  int tgtRow = point2dPair.getTgtRow();
  int tgtCol = point2dPair.getTgtCol();
  bool isNextSpaceOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(nextRowCoordinate, tgtCol);
  if (isMovingByTwoSpaces(point2dPair)) {
    bool isTgtOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(tgtRow, tgtCol);
    return isNextSpaceOccupied || isTgtOccupied;
  }

  int nextColCaptureCoordinate = point2dPair.getSrcCol() + direction;
  bool isCaptureRow = tgtRow == nextRowCoordinate;
  bool isCaptureCol = tgtCol == nextColCaptureCoordinate;
  bool isDiagonalCapture = isCaptureRow && isCaptureCol;
  return isNextSpaceOccupied && !isDiagonalCapture;
}

void Pawn::setMovementTargets(Point2D point2d) {
}
