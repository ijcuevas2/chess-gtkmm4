//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_EMPTYPIECE_H
#define CHESS_EMPTYPIECE_H
#include "ChessPiece.h"

class EmptyPiece : public virtual ChessPiece {
public:
    EmptyPiece(ChessBoardMediator & chessBoardMediator)
            : ChessPiece(PlayerID::NONE, PieceType::EMPTY_PIECE, chessBoardMediator) { }
    bool canMoveToTarget(Coordinates coordinates) override;
    void afterPieceMoved(Coordinates coordinates) override;
};


#endif //CHESS_EMPTYPIECE_H
