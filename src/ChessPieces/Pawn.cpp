//
// Created by Ismael Cuevas on 7/14/24.
//

#include "../../headers/ChessPieces/Pawn.h"

bool Pawn::canMoveToTarget(Coordinates coordinates) {
  bool baseCanMove = ChessPiece::canMoveToTargetHelper(coordinates);
  if (!baseCanMove) {
    return false;
  }

  bool isCorrectDirectionValue = isCorrectDirection(coordinates);
  if (!isCorrectDirectionValue) {
    return false;
  }

  if (isFirstMove) {
    bool canMove = canMoveFirstTurn(coordinates);
    return canMove;
  } else {
    bool canCaptureValue = canCapture(coordinates);
    bool canMoveSingleSpaceValue = canMoveSingleSpaceForward(coordinates);
    return canCaptureValue || canMoveSingleSpaceValue;
  }
}

bool Pawn::canMoveFirstTurn(Coordinates coordinates) {
  int xAbsDistance = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
  int yAbsDistance = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());

  bool canMove = xAbsDistance == 0 && yAbsDistance <= 2;
  return canMove;
}

void Pawn::afterPieceMoved(Coordinates coordinates) {
  if (isFirstMove) {
    setUsedFirstMove();
    setMovedTwoSpacesTurn(coordinates);
  }
}

void Pawn::setMovedTwoSpacesTurn(Coordinates coordinates) {
  int absoluteDistanceValue = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
  bool movedTwoSpacesResult = absoluteDistanceValue == 2;
  if (movedTwoSpacesResult) {
    int turn = chessBoardMediator.getCurrentTurnSignal().emit();
    this->movedTwoSpacesTurn = turn;
  }
}

int Pawn::getMovedTwoSpacesTurn() {
  return this->movedTwoSpacesTurn;
}

bool Pawn::isCorrectDirection(Coordinates coordinates) {
  int yDistance = coordinates.getTgtRow() - coordinates.getSrcRow();
  if (playerId == PlayerID::PLAYER_WHITE) {
    return yDistance < 0;
  } else if (playerId == PlayerID::PLAYER_BLACK) {
    return yDistance > 0;
  }

  return false;
}

bool Pawn::canCapture(Coordinates coordinates) {
  bool isDiagonalMoveValue = isDiagonalMove(coordinates);
  if (isDiagonalMoveValue) {
    bool canDiagonalCaptureValue = canDiagonalCapture(coordinates);
    if (canDiagonalCaptureValue) {
      return true;
    }

    bool canEnPassantCaptureValue = canEnPassantCapture(coordinates);
    if (canEnPassantCaptureValue) {
      return true;
    }
  }

  return false;
}

bool Pawn::canDiagonalCapture(Coordinates coordinates) {
  bool isIndexOccupiedResult = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit(coordinates.getSrcRow(), coordinates.getSrcCol());
  return isIndexOccupiedResult;
}

bool Pawn::isDiagonalMove(Coordinates coordinates) {
  int xAbsDistance = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
  int yAbsDistance = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());
  bool isDiagonalMoveResult = xAbsDistance == 1 && yAbsDistance == 1;
  return isDiagonalMoveResult;
}

bool Pawn::canMoveSingleSpaceForward(Coordinates coordinates) {
  int xAbsDistance = absoluteDistance(coordinates.getSrcCol(), coordinates.getTgtCol());
  int yAbsDistance = absoluteDistance(coordinates.getSrcRow(), coordinates.getTgtRow());

  bool isTargetOccupiedValue = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit(coordinates.getTgtRow(), coordinates.getTgtCol());
  bool canMove = xAbsDistance == 0 && yAbsDistance < 2 && !isTargetOccupiedValue;
  return canMove;
}

bool Pawn::canEnPassantCapture(Coordinates coordinates) {
  bool isIndexOccupiedValue = chessBoardMediator.getIsBoardIndexOccupiedSignal().emit(coordinates.getSrcRow(), coordinates.getSrcCol());
  if (!isIndexOccupiedValue) {
    int enPassantTurn = chessBoardMediator.getMovedTwoSpacesTurnSignal().emit(coordinates.getSrcRow(), coordinates.getSrcCol()) + 1;
    bool canEnPassantCaptureResult = enPassantTurn == chessBoardMediator.getCurrentTurnSignal().emit();
    return canEnPassantCaptureResult;
  }

  return false;
}

void Pawn::setUsedFirstMove() {
  this->isFirstMove = false;
}

bool Pawn::isPieceBlockingPath(Coordinates coordinates) {
  return false;
}

Coordinates Pawn::getNextCoordinates(Coordinates coordinates) {
  return Coordinates(0, 0, 0, 0);
}
