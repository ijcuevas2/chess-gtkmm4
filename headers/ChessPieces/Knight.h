//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "ChessPiece.h"

class Knight : public virtual ChessPiece {
public:
    Knight(PlayerID playerId, ChessMediator & chessMediator) : ChessPiece(playerId, PieceType::KNIGHT, chessMediator) {
    }

    bool getIsValidPath(Point2DPair point2dPair) override;

    bool isPieceBlockingPath(Point2DPair point2dPair) override;
};


#endif //CHESS_KNIGHT_H
