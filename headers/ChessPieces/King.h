//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H \
#include "ChessPiece.h"
#include "Rook.h"
#include "ChessBoardMediator/ChessBoardMediator.h"

class King : public virtual ChessPiece {
private:
    bool hasMoved;
    bool isInCheck;
public:
    King(PlayerID playerId, ChessBoardMediator &chessBoardMediator) : ChessPiece(playerId, PieceType::KING, chessBoardMediator) {
    }

    std::vector<Point2DPair> getAdjacentCoordinates(Point2DPair point2DPair);
    bool canMoveToTarget(Point2DPair point2DPair) override;
    bool getHasMoved();
    void setHasMoved();
    bool getIsInCheck();
    bool getIsValidPath(Point2DPair point2DPair) override;
    void afterPieceMoved(Point2DPair point2DPair) override;
    bool isPieceBlockingPath(Point2DPair point2DPair) override;
};


#endif //CHESS_KING_H
