//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "../../enum/PieceType.h"
#include "../../enum/Player.h"
#include "../Point2DPair/Point2DPair.h"
#include "../../headers/Utils/MathUtils.h"
#include "../../headers/Utils/StringUtils.h"
#include "Point2D/Point2D.h"
#include "ChessMediator/ChessMediator.h"
#include <iostream>

class ChessPiece {
public:
    void setChessPieceImagePath();
    ChessPiece(PlayerID playerId, PieceType pieceType, ChessMediator & chessMediator);
    virtual ~ChessPiece();
    int actualDistance(int source, int dest);
    int absoluteDistance(int source, int dest);
    bool isValidPoint2DPair(Point2DPair point2dPair);
    bool isValidPoint2D(Point2D point2d);
    void copyChessPiece(ChessPiece *chessPiecePtr);
    PlayerID getPlayerId();
    PieceType getPieceType();
    void setPlayerId(PlayerID playerId);
    void setPieceType(PieceType pieceType);
    std::vector<Point2D> getHorizontalSpaces(Point2D point2d, bool isIncreasing);
    virtual bool canMoveToTarget(Point2DPair point2dPair);
    virtual void afterPieceMoved(Point2DPair point2dPair);
    virtual void setMovementTargets(Point2D point2d);
    std::vector<Point2D> getCaptureTargets();
private:
    std::vector<Point2D> getCardinalSpacesHelper(Point2D point2d, bool isHorizontal);
    std::vector<Point2D> getDiagonalSpacesHelper(Point2D point2d, bool isEastDirection);
protected:
    bool canAddSpace(Point2D point2d);
    virtual bool getIsValidPath(Point2DPair point2dPair) = 0;
    virtual Point2DPair getNextCoordinates(Point2DPair point2dPair);
    virtual bool isPieceBlockingPath(Point2DPair point2dPair);
    std::vector<Point2D> captureTargets;
    std::vector<Point2D> getCardinalSpaces(Point2D point2d);
    std::vector<Point2D> getDiagonalSpaces(Point2D point2d);
    std::vector<Point2D> getQueenSpaces(Point2D point2d);
    PieceType pieceType;
    PlayerID playerId;
    ChessMediator & chessMediator;
};

#endif //CHESS_CHESSPIECE_H
