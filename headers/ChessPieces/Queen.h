//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "ChessPiece.h"

class Queen : public virtual ChessPiece {
public:
    Queen(PlayerID playerId, ChessMediator & chessMediator) : ChessPiece(playerId, PieceType::QUEEN,
                                                                             chessMediator) {
    }

    bool canMoveDiagonal(Point2DPair point2DPair);

    bool canMoveHorizontal(Point2DPair point2DPair);

    Point2DPair getNextCoordinates(Point2DPair point2DPair) override;

    bool getIsValidPath(Point2DPair point2DPair) override;
};

#endif //CHESS_QUEEN_H
