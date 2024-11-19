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

bool ChessPiece::getIsValidPath(Point2DPair point2dPair) {
  return false;
}

bool ChessPiece::canAddSpace(Point2D point2d) {
  bool isValidTargetPoint = isValidPoint2D(point2d);
  if (isValidTargetPoint) {
    bool isBoardSpaceOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(point2d.getRow(), point2d.getCol());
    if (isBoardSpaceOccupied) {
      int targetRow = point2d.getRow();
      int targetCol = point2d.getCol();
      bool isTurnPlayerChessPiece = chessMediator.getIsTurnPlayersChessPieceSignal().emit(this->playerId, targetRow, targetCol);
      if (!isTurnPlayerChessPiece) {
        return true;
      }
    }
  }

  return false;
}

std::vector<Point2D> ChessPiece::getDiagonalSpacesHelper(Point2D point2d, bool isEastDirection) {
  std::vector<Point2D> result(0);
  int direction = isEastDirection ? 1 : -1;
  int targetRow = point2d.getRow();
  int targetCol = point2d.getCol();

  bool canAddEndSpaceBool = false;
  bool isOccupied = false;

  do {
    targetCol += direction;
    targetRow += direction;

    Point2D targetPoint(targetRow, targetCol);
    canAddEndSpaceBool = canAddSpace(targetPoint);

    if (canAddEndSpaceBool) {
      result.push_back(targetPoint);
    }

    isOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(targetPoint.getRow(), targetPoint.getCol());
  } while (!canAddEndSpaceBool && !isOccupied);

  targetRow = point2d.getRow();
  targetCol = point2d.getCol();
  isOccupied = false;

  do {
    targetCol -= direction;
    targetRow += direction;

    Point2D targetPoint(targetRow, targetCol);
    canAddEndSpaceBool = canAddSpace(targetPoint);

    if (canAddEndSpaceBool) {
      result.push_back(targetPoint);
    }

    isOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(targetPoint.getRow(), targetPoint.getCol());
  } while (!canAddEndSpaceBool && !isOccupied);

  return result;
}

std::vector<Point2D> ChessPiece::getCardinalSpacesHelper(Point2D point2d, bool isHorizontalCapture) {
  std::vector<Point2D> result(0);
  int direction = 1;
  int origRow = point2d.getRow();
  int origCol = point2d.getCol();
  int targetRow = point2d.getRow();
  int targetCol = point2d.getCol();

  bool canAddEndSpaceBool = false;
  bool isOccupied = false;

  do {
    if (isHorizontalCapture) {
      targetCol += direction;
    } else {
      targetRow += direction;
    }

    Point2D targetPoint(targetRow, targetCol);
    canAddEndSpaceBool = canAddSpace(targetPoint);

    if (canAddEndSpaceBool) {
      result.push_back(targetPoint);
    }

    isOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(targetPoint.getRow(), targetPoint.getCol());
  } while (!canAddEndSpaceBool && !isOccupied);

  targetRow = origRow;
  targetCol = origCol;
  isOccupied = false;

  do {
    if (isHorizontalCapture) {
      targetCol -= direction;
    } else {
      targetRow -= direction;
    }

    Point2D targetPoint(targetRow, targetCol);
    canAddEndSpaceBool = canAddSpace(targetPoint);

    if (canAddEndSpaceBool) {
      result.push_back(targetPoint);
    }

    isOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(targetPoint.getRow(), targetPoint.getCol());
  } while (!canAddEndSpaceBool && !isOccupied);

  return result;
}

std::vector<Point2D> ChessPiece::getDiagonalSpaces(Point2D point2d) {
  std::vector<Point2D> firstEndSpaces = getDiagonalSpacesHelper(point2d, true);
  std::vector<Point2D> secondEndSpaces = getDiagonalSpacesHelper(point2d, false);
  firstEndSpaces.reserve(firstEndSpaces.size() + secondEndSpaces.size());
  firstEndSpaces.insert(firstEndSpaces.end(), secondEndSpaces.begin(), secondEndSpaces.end());
  return firstEndSpaces;
}

std::vector<Point2D> ChessPiece::getCardinalSpaces(Point2D point2d) {
  std::vector<Point2D> firstEndSpaces = getCardinalSpacesHelper(point2d, true);
  std::vector<Point2D> secondEndSpaces = getCardinalSpacesHelper(point2d, false);
  firstEndSpaces.reserve(firstEndSpaces.size() + secondEndSpaces.size());
  firstEndSpaces.insert(firstEndSpaces.end(), secondEndSpaces.begin(), secondEndSpaces.end());
  return firstEndSpaces;
}

std::vector<Point2D> ChessPiece::getQueenSpaces(Point2D point2d) {
  std::vector<Point2D> firstEndSpaces = getCardinalSpaces(point2d);
  std::vector<Point2D> secondEndSpaces = getDiagonalSpaces(point2d);
  firstEndSpaces.reserve(firstEndSpaces.size() + secondEndSpaces.size());
  firstEndSpaces.insert(firstEndSpaces.end(), secondEndSpaces.begin(), secondEndSpaces.end());
  return firstEndSpaces;
}

void ChessPiece::afterPieceMoved(Point2DPair point2dPair) {
  captureTargets.clear();
  Point2D point2d(point2dPair.getSrcRow(), point2dPair.getSrcCol());
  setMovementTargets(point2d);
}

std::vector<Point2D> ChessPiece::getCaptureTargets() {
  return captureTargets;
}

void ChessPiece::setMovementTargets(Point2D point2d) {
}