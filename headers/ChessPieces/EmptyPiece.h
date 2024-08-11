//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_EMPTYPIECE_H
#define CHESS_EMPTYPIECE_H

#include "ChessPiece.h"

class EmptyPiece : public virtual ChessPiece {
public:
    EmptyPiece(ChessBoardMediator &chessBoardMediator)
            : ChessPiece(PlayerID::NONE, PieceType::EMPTY_PIECE, chessBoardMediator) {}

    bool canMoveToTarget(Point2DPair point2DPair) override;

    bool getIsValidPath(Point2DPair point2DPair) override;
};


#endif //CHESS_EMPTYPIECE_H
