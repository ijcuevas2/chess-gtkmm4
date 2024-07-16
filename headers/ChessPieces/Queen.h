//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "ChessPiece.h"

class Queen : public virtual ChessPiece {
public:
    Queen(PlayerID playerId) : ChessPiece(playerId, PieceType::QUEEN) {
    }
    bool canMove(Coordinates coordinates) override;
    bool canMoveDiagonal(Coordinates coordinates);
    bool canMoveHorizontal(Coordinates coordinates);
    void afterPieceMoved(Coordinates coordinates) override;
};
#endif //CHESS_QUEEN_H
