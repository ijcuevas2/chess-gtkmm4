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

bool ChessPiece::canMoveToTargetWhileInCheck(Point2DPair point2dPair) {
  bool canMoveToTargetBool = canMoveToTarget(point2dPair);
  Point2D targetPoint(point2dPair.getTgtRow(), point2dPair.getTgtCol());
  bool isPointContainedInKingMovementTargets = chessMediator.getIsPointContainedInKingMovementTargetsSignal().emit(playerId, targetPoint);
  return canMoveToTargetBool && isPointContainedInKingMovementTargets;
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

/**
 * @TODO: REMOVE THIS FUNCTION
 */
bool ChessPiece::canAddSpace(Point2D point2d) {
  bool isValidTargetPoint = isValidPoint2D(point2d);
  if (isValidTargetPoint) {
    bool isBoardSpaceOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(point2d.getRow(), point2d.getCol());
    if (!isBoardSpaceOccupied) {
      return true;
    } else {
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

std::vector<Point2D> ChessPiece::getDiagonalSpacesHelper(Point2D point2d, bool isNorth, bool isEast, Point2D kingPoint) {
  std::vector<Point2D> result(0);
  int horizontalDirection = isEast ? 1 : -1;
  int verticalDirection = isNorth ? -1 : 1;
  int targetRow = point2d.getRow();
  int targetCol = point2d.getCol();

  bool canAddSpaceBool = false;
  bool isOccupied = false;
  bool isValidPointBool = true;

  do {
    targetCol += horizontalDirection;
    targetRow += verticalDirection;

    Point2D targetPoint(targetRow, targetCol);
    if (targetPoint == kingPoint) {
      targetCol += horizontalDirection;
      targetRow += verticalDirection;
      targetPoint = Point2D(targetRow, targetCol);
    }

    canAddSpaceBool = canAddSpace(targetPoint);

    if (canAddSpaceBool) {
      result.push_back(targetPoint);
    }

    isValidPointBool = isValidPoint2D(targetPoint);

    if (isValidPointBool) {
      isOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(targetRow, targetCol);
    }
  } while (canAddSpaceBool && !isOccupied && isValidPointBool);

  return result;
}

std::vector<Point2D> ChessPiece::getCardinalSpacesHelper(Point2D point2d, bool isHorizontal, bool isIncreasing, Point2D kingPoint) {
  std::vector<Point2D> result(0);
  int direction = isIncreasing ? 1 : -1;
  int targetRow = point2d.getRow();
  int targetCol = point2d.getCol();

  bool canAddSpaceBool = false;
  bool isOccupied = false;
  bool isValidPointBool = true;

  do {
    if (isHorizontal) {
      targetCol += direction;
    } else {
      targetRow += direction;
    }

    Point2D targetPoint(targetRow, targetCol);
    if (targetPoint == kingPoint) {
      continue;
    }

    canAddSpaceBool = canAddSpace(targetPoint);

    if (canAddSpaceBool) {
      result.push_back(targetPoint);
    }

    isValidPointBool = isValidPoint2D(targetPoint);
    if (isValidPointBool) {
      isOccupied = chessMediator.getIsBoardIndexOccupiedSignal().emit(targetRow, targetCol);
    }
  } while (canAddSpaceBool && !isOccupied && isValidPointBool);

  return result;
}

std::vector<Point2D> ChessPiece::getDiagonalSpaces(Point2D point2d, Point2D kingPoint) {
  std::vector<Point2D> result(0);
  std::vector<Point2D> northEastSpaces = getDiagonalSpacesHelper(point2d, true, true, kingPoint);
  std::vector<Point2D> northWestSpaces = getDiagonalSpacesHelper(point2d, true, false, kingPoint);
  std::vector<Point2D> southEastSpaces = getDiagonalSpacesHelper(point2d, false, true, kingPoint);
  std::vector<Point2D> southWestSpaces = getDiagonalSpacesHelper(point2d, false, false, kingPoint);
  result.insert(result.end(), northEastSpaces.begin(), northEastSpaces.end());
  result.insert(result.end(), northWestSpaces.begin(), northWestSpaces.end());
  result.insert(result.end(), southEastSpaces.begin(), southEastSpaces.end());
  result.insert(result.end(), southWestSpaces.begin(), southWestSpaces.end());
  return result;
}

std::vector<Point2D> ChessPiece::getCardinalSpaces(Point2D point2d, Point2D kingPoint) {
  std::vector<Point2D> result(0);
  std::vector<Point2D> firstEndSpaces = getCardinalSpacesHelper(point2d, true, true, kingPoint);
  std::vector<Point2D> secondEndSpaces = getCardinalSpacesHelper(point2d, true, false, kingPoint);
  std::vector<Point2D> thirdEndSpaces = getCardinalSpacesHelper(point2d, false, true, kingPoint);
  std::vector<Point2D> fourthEndSpaces = getCardinalSpacesHelper(point2d, false, false, kingPoint);
  result.insert(result.end(), firstEndSpaces.begin(), firstEndSpaces.end());
  result.insert(result.end(), secondEndSpaces.begin(), secondEndSpaces.end());
  result.insert(result.end(), thirdEndSpaces.begin(), thirdEndSpaces.end());
  result.insert(result.end(), fourthEndSpaces.begin(), fourthEndSpaces.end());
  return result;
}

std::vector<Point2D> ChessPiece::getQueenSpaces(Point2D point2d) {
  std::vector<Point2D> firstEndSpaces = getCardinalSpaces(point2d);
  std::vector<Point2D> secondEndSpaces = getDiagonalSpaces(point2d);
  firstEndSpaces.reserve(firstEndSpaces.size() + secondEndSpaces.size());
  firstEndSpaces.insert(firstEndSpaces.end(), secondEndSpaces.begin(), secondEndSpaces.end());
  return firstEndSpaces;
}

std::vector<Point2D> ChessPiece::getAllSpacesHelper(Point2D point2d, Point2D kingPoint = Point2D(-1, -1)) {
}

void ChessPiece::afterPieceMoved(Point2DPair point2dPair) {
}

std::vector<Point2D> ChessPiece::getMovementTargets(Point2D point2d) {
  std::vector<Point2D> movementTargets;
  return movementTargets;
}

bool ChessPiece::hasPlayerId(PlayerID playerId) {
  return this->playerId == playerId;
}

bool ChessPiece::hasOpponentPlayerId(PlayerID playerId) {
  return this->playerId != playerId;
}