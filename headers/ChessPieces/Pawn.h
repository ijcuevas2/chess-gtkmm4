//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "ChessPiece.h"
#include "ChessBoardMediator/ChessBoardMediator.h"

class Pawn : public virtual ChessPiece {
private:
    bool isFirstMove = true;
    int movedTwoSpacesTurn = -1;
    bool isEnPassantEligible = false;
public:
    Pawn(PlayerID playerId, ChessBoardMediator &chessBoardMediator) : ChessPiece(playerId, PieceType::PAWN, chessBoardMediator) {
    }

    bool isCorrectDirection(Point2DPair point2DPair);
    bool canMoveFirstTurn(Point2DPair point2DPair);
    bool canDiagonalCapture(Point2DPair point2DPair);
    bool canMoveSingleSpaceForward(Point2DPair point2DPair);
    bool isDiagonalMove(Point2DPair point2DPair);
    bool canCapture(Point2DPair point2DPair);
    bool canEnPassantCapture(Point2DPair point2DPair);
    void setUsedFirstMove();
    void setMovedTwoSpacesTurn(Point2DPair point2DPair);
    bool isMovingByTwoSpaces(Point2DPair point2DPair);
    void afterPieceMoved(Point2DPair point2DPair) override;
    bool isPieceBlockingPath(Point2DPair point2DPair) override;
    bool getIsValidPath(Point2DPair point2DPair) override;
    int getMovedTwoSpacesTurn();
};

#endif //CHESS_PAWN_H
