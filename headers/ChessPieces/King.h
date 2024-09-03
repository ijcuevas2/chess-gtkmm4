//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "ChessPiece.h"
#include "Rook.h"
#include "Point2D/Point2D.h"

class King : public virtual ChessPiece {
private:
    bool hasMoved;
    bool isInCheck;
public:
    King(PlayerID playerId, ChessMediator & chessMediator) : ChessPiece(playerId, PieceType::KING,
                                                                            chessMediator) {
    }

    std::vector<Point2DPair> getAdjacentCoordinates(Point2DPair point2dPair);

//    bool canMoveToTarget(Point2DPair point2dPair) override;

    bool getHasMoved();

    void setHasMoved();

    void setIsInCheck(bool inCheck);
    bool getIsInCheck();

    bool getIsValidPath(Point2DPair point2dPair) override;

    void afterPieceMoved(Point2DPair point2dPair) override;

    bool isPieceBlockingPath(Point2DPair point2dPair) override;

    std::vector<Point2D> getAdjacentPoints(Point2D point2D);
};


#endif //CHESS_KING_H
