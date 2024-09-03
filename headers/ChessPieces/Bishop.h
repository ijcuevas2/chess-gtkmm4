//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "ChessPiece.h"

class Bishop : public virtual ChessPiece {
public:
    Bishop(PlayerID playerId, ChessMediator & chessMediator) : ChessPiece(playerId, PieceType::BISHOP, chessMediator) {
    }

    bool getIsValidPath(Point2DPair point2dPair) override;
    Point2DPair getNextCoordinates(Point2DPair point2dPair) override;
};


#endif //CHESS_BISHOP_H
