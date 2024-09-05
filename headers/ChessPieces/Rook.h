//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "ChessPiece.h"

class Rook : public virtual ChessPiece {
public:
    Rook(PlayerID playerId, ChessMediator & chessMediator) : ChessPiece(playerId, PieceType::ROOK, chessMediator) {
    }

    bool getIsValidPath(Point2DPair point2dPair) override;
    Point2DPair getNextCoordinates(Point2DPair point2dPair) override;
    void afterPieceMoved(Point2DPair point2dPair) override;
    void setHasMoved();
    bool getHasMoved();
private:
    bool hasMoved = false;
};


#endif //CHESS_ROOK_H
