//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Pawn.h"

bool Pawn::getIsValidPath(Point2DPair point2DPair) {
  bool isCorrectDirectionValue = isCorrectDirection (point2DPair);
  if (!isCorrectDirectionValue) {
    return false;
  }

  if (isFirstMove) {
    bool canMove = canMoveFirstTurn (point2DPair);
    return canMove;
  } else {
    bool canCaptureValue = canCapture (point2DPair);
    bool canMoveSingleSpaceValue = canMoveSingleSpaceForward (point2DPair);
    return canCaptureValue || canMoveSingleSpaceValue;
  }
}

bool Pawn::canMoveFirstTurn(Point2DPair point2DPair) {
  int xAbsDistance = absoluteDistance (point2DPair.getSrcCol(), point2DPair.getTgtCol());
  int yAbsDistance = absoluteDistance (point2DPair.getSrcRow(), point2DPair.getTgtRow());

  bool canMove = xAbsDistance == 0 && yAbsDistance <= 2;
  return canMove;
}

void Pawn::afterPieceMoved(Point2DPair point2DPair) {
  if (isFirstMove) {
    setUsedFirstMove();
    setMovedTwoSpacesTurn (point2DPair);
  }
}


void Pawn::setMovedTwoSpacesTurn(Point2DPair point2DPair) {
  bool movedTwoSpacesResult = isMovingByTwoSpaces (point2DPair);
  if (movedTwoSpacesResult) {
    int turn = chessBoardMediator.getCurrentTurnSignal().emit();
    this->movedTwoSpacesTurn = turn;
  }
}

bool Pawn::isMovingByTwoSpaces(Point2DPair point2DPair) {
  int absoluteDistanceValue = absoluteDistance (point2DPair.getSrcRow(), point2DPair.getTgtRow());
  bool movedTwoSpacesResult = absoluteDistanceValue == 2;
  return movedTwoSpacesResult;
}

int Pawn::getMovedTwoSpacesTurn() {
  return this->movedTwoSpacesTurn;
}

bool Pawn::isCorrectDirection(Point2DPair point2DPair) {
  int yDistance = point2DPair.getTgtRow() - point2DPair.getSrcRow();
  if (playerId == PlayerID::PLAYER_WHITE) {
    return yDistance < 0;
  } else if (playerId == PlayerID::PLAYER_BLACK) {
    return yDistance > 0;
  }

  return false;
}

bool Pawn::canCapture(Point2DPair point2DPair) {
  bool isDiagonalMoveValue = isDiagonalMove (point2DPair);
  if (isDiagonalMoveValue) {
    bool canDiagonalCaptureValue = canDiagonalCapture (point2DPair);
    if (canDiagonalCaptureValue) {
      return true;
    }

    bool canEnPassantCaptureValue = canEnPassantCapture (point2DPair);
    if (canEnPassantCaptureValue) {
      return true;
    }
  }

  return false;
}

bool Pawn::canDiagonalCapture(Point2DPair point2DPair) {
  bool isIndexOccupiedResult = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit (point2DPair.getSrcRow(),
                                                                                       point2DPair.getSrcCol());
  return isIndexOccupiedResult;
}

bool Pawn::isDiagonalMove(Point2DPair point2DPair) {
  int xAbsDistance = absoluteDistance (point2DPair.getSrcCol(), point2DPair.getTgtCol());
  int yAbsDistance = absoluteDistance (point2DPair.getSrcRow(), point2DPair.getTgtRow());
  bool isDiagonalMoveResult = xAbsDistance == 1 && yAbsDistance == 1;
  return isDiagonalMoveResult;
}

bool Pawn::canMoveSingleSpaceForward(Point2DPair point2DPair) {
  int xAbsDistance = absoluteDistance (point2DPair.getSrcCol(), point2DPair.getTgtCol());
  int yAbsDistance = absoluteDistance (point2DPair.getSrcRow(), point2DPair.getTgtRow());

  bool isTargetOccupiedValue = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit (point2DPair.getTgtRow(),
                                                                                       point2DPair.getTgtCol());
  bool canMove = xAbsDistance == 0 && yAbsDistance < 2 && !isTargetOccupiedValue;
  return canMove;
}

bool Pawn::canEnPassantCapture(Point2DPair point2DPair) {
  bool isIndexOccupiedValue = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit (point2DPair.getSrcRow(),
                                                                                      point2DPair.getSrcCol());
  if (!isIndexOccupiedValue) {
    int enPassantTurn =
            chessBoardMediator.getMovedTwoSpacesTurnSignal().emit (point2DPair.getSrcRow(), point2DPair.getSrcCol()) + 1;
    bool canEnPassantCaptureResult = enPassantTurn == chessBoardMediator.getCurrentTurnSignal().emit();
    return canEnPassantCaptureResult;
  }

  return false;
}

void Pawn::setUsedFirstMove() {
  this->isFirstMove = false;
}

bool Pawn::isPieceBlockingPath(Point2DPair point2DPair) {
  bool positiveVerticalDirection = MathUtils::isPositiveVerticalDirection (point2DPair);
  int direction = positiveVerticalDirection ? 1 : -1;
  int nextRowCoordinate = point2DPair.getSrcRow() + direction;
  int tgtRow = point2DPair.getTgtRow();
  int tgtCol = point2DPair.getTgtCol();
  bool isNextSpaceOccupied = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit(nextRowCoordinate, tgtCol);
  if (isMovingByTwoSpaces (point2DPair)) {
    bool isTgtOccupied = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit(tgtRow, tgtCol);
    return isNextSpaceOccupied || isTgtOccupied;
  }

  return isNextSpaceOccupied;
}
