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

    bool isCorrectDirection(Point2DPair coordinates);
    bool canMoveFirstTurn(Point2DPair coordinates);
    bool canDiagonalCapture(Point2DPair coordinates);
    bool canMoveSingleSpaceForward(Point2DPair coordinates);
    bool isDiagonalMove(Point2DPair coordinates);
    bool canCapture(Point2DPair coordinates);
    bool canEnPassantCapture(Point2DPair coordinates);
    void setUsedFirstMove();
    void setMovedTwoSpacesTurn(Point2DPair coordinates);
    bool isMovingByTwoSpaces(Point2DPair coordinates);
    void afterPieceMoved(Point2DPair coordinates) override;
    bool isPieceBlockingPath(Point2DPair coordinates) override;
    bool getIsValidPath(Point2DPair coordinates) override;
    int getMovedTwoSpacesTurn();
};

#endif //CHESS_PAWN_H
