//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "ChessPiece.h"

class Bishop : public virtual ChessPiece {
public:
    Bishop(PlayerID playerId, ChessBoardMediator & chessBoardMediator) : ChessPiece(playerId, PieceType::BISHOP, chessBoardMediator) {
    }
    // bool canMoveToTarget(Coordinates coordinates) override;
    bool getIsValidPath(Coordinates coordinates) override;
    void afterPieceMoved(Coordinates coordinates) override;
    bool isPieceBlockingPath(Coordinates coordinates) override;
    Coordinates getNextCoordinates(Coordinates coordinates) override;
};


#endif //CHESS_BISHOP_H
