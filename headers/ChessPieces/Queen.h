//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "ChessPiece.h"

class Queen : public virtual ChessPiece {
public:
    Queen(PlayerID playerId, ChessBoardMediator & chessBoardMediator) : ChessPiece(playerId, PieceType::QUEEN, chessBoardMediator) {
    }

    bool canMoveDiagonal(Coordinates coordinates);
    bool canMoveHorizontal(Coordinates coordinates);
    bool isPieceBlockingPath(Coordinates coordinates) override;
    Coordinates getNextCoordinates(Coordinates coordinates) override;
    bool getIsValidPath(Coordinates coordinates) override;
};
#endif //CHESS_QUEEN_H
