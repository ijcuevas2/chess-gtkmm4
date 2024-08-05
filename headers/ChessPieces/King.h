//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H #include "ChessPiece.h"
#include "Rook.h"
#include "ChessBoardMediator/ChessBoardMediator.h"

class King : public virtual ChessPiece {
private:
    bool hasMoved;
    bool isInCheck;
public:
    King(PlayerID playerId, ChessBoardMediator &chessBoardMediator) : ChessPiece(playerId, PieceType::KING, chessBoardMediator) {
    }

    std::vector<Coordinates> getAdjacentCoordinates(Coordinates coordinates);
    bool canMoveToTarget(Coordinates coordinates) override;
    bool getHasMoved();
    void setHasMoved();
    bool getIsInCheck();
    bool getIsValidPath(Coordinates coordinates) override;
    void afterPieceMoved(Coordinates coordinates) override;
    bool isPieceBlockingPath(Coordinates coordinates) override;
};


#endif //CHESS_KING_H
