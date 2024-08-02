//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "ChessPiece.h"

class Rook : public virtual ChessPiece {
public:
    Rook(PlayerID playerId, ChessBoardMediator & chessBoardMediator) : ChessPiece(playerId, PieceType::ROOK, chessBoardMediator) {
    }

    // bool canMoveToTarget(Coordinates coordinates) override;
    void afterPieceMoved(Coordinates coordinates) override;
    bool isPieceBlockingPath(Coordinates coordinates) override;
    Coordinates getNextCoordinates(Coordinates coordinates) override;
    bool getIsValidPath(Coordinates coordinates) override;
    void setHasMoved();
    bool getHasMoved();
private:
    bool hasMoved = false;
};


#endif //CHESS_ROOK_H
