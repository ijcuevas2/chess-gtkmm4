//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "ChessPiece.h"

class Knight : public virtual ChessPiece {
public:
    Knight(PlayerID playerId) : ChessPiece(playerId, PieceType::KNIGHT) {
    }
    bool canMoveToTarget(Coordinates coordinates) override;
    void afterPieceMoved(Coordinates coordinates) override;
};


#endif //CHESS_KNIGHT_H
