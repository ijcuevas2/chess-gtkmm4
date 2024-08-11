//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "ChessPiece.h"

class Bishop : public virtual ChessPiece {
public:
    Bishop(PlayerID playerId, ChessBoardMediator &chessBoardMediator) : ChessPiece(playerId, PieceType::BISHOP,
                                                                                   chessBoardMediator) {
    }

    bool getIsValidPath(Point2DPair point2DPair) override;

    Point2DPair getNextCoordinates(Point2DPair point2DPair) override;
};


#endif //CHESS_BISHOP_H
