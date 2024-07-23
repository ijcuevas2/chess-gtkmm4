//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "ChessPiece.h"

class Rook : public virtual ChessPiece {
public:
    Rook(PlayerID playerId) : ChessPiece(playerId, PieceType::ROOK) {
    }

    bool canMove(Coordinates coordinates) override;
    void afterPieceMoved(Coordinates coordinates) override;
};


#endif //CHESS_ROOK_H
