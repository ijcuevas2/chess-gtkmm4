//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "ChessPiece.h"

class Bishop : public virtual ChessPiece {
public:
    Bishop(PlayerID playerId) : ChessPiece(playerId, PieceType::BISHOP) {
    }
    bool canMoveToTarget(Coordinates coordinates) override;
    void afterPieceMoved(Coordinates coordinates) override;
};


#endif //CHESS_BISHOP_H
