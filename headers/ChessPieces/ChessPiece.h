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
    virtual bool getIsValidPath(Point2DPair point2dPair) = 0;
    virtual Point2DPair getNextCoordinates(Point2DPair point2dPair);
    virtual bool canMoveToTarget(Point2DPair point2dPair);
    virtual void afterPieceMoved(Point2DPair point2dPair);
    virtual bool isPieceBlockingPath(Point2DPair point2dPair);
    void copyChessPiece(ChessPiece *chessPiecePtr);
    PlayerID getPlayerId();
    PieceType getPieceType();
    void setPlayerId(PlayerID playerId);
    void setPieceType(PieceType pieceType);
protected:
    PieceType pieceType;
    PlayerID playerId;
    ChessMediator & chessMediator;
};

#endif //CHESS_CHESSPIECE_H
