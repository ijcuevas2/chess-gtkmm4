//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "../../enum/PieceType.h"
#include "../../enum/Player.h"
#include "../Point2DPair/Point2DPair.h"
#include "ChessBoardMediator/ChessBoardMediator.h"
#include "../../headers/MathUtils/MathUtils.h"
#include "Point2D/Point2D.h"
#include <iostream>

class ChessPiece {
public:
    void setChessPieceImagePath();

    ChessPiece(PlayerID playerId, PieceType pieceType, ChessBoardMediator &chessBoardMediator);

    virtual ~ChessPiece();

    int actualDistance(int source, int dest);

    int absoluteDistance(int source, int dest);

    bool isValidPoint2DPair(Point2DPair point2DPair);

    bool isValidPoint2D(Point2D point2D);

    virtual bool getIsValidPath(Point2DPair point2DPair) = 0;

    virtual Point2DPair getNextCoordinates(Point2DPair point2DPair);

    virtual bool canMoveToTarget(Point2DPair point2DPair);

    virtual void afterPieceMoved(Point2DPair point2DPair);

    virtual bool isPieceBlockingPath(Point2DPair point2DPair);

    void copyChessPiece(ChessPiece *chessPiecePtr);

    PlayerID getPlayerId();

    PieceType getPieceType();

    void setPlayerId(PlayerID playerId);

    void setPieceType(PieceType pieceType);

protected:
    PieceType pieceType;
    PlayerID playerId;
    ChessBoardMediator &chessBoardMediator;
};

#endif //CHESS_CHESSPIECE_H
