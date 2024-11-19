//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "ChessPiece.h"
#include "../../enum/PawnEnpassantRow.h"

class Pawn : public virtual ChessPiece {
private:
    bool isFirstMove = true;
    bool isCorrectDirection(Point2DPair point2dPair);
    bool canMoveFirstTurn(Point2DPair point2dPair);
    bool canDiagonalCapture(Point2DPair point2dPair);
    bool canMoveSingleSpaceForward(Point2DPair point2dPair);
    bool isDiagonalMove(Point2DPair point2dPair);
    bool canCapture(Point2DPair point2dPair);
public:
    Pawn(PlayerID playerId, ChessMediator & chessMediator) : ChessPiece(playerId, PieceType::PAWN, chessMediator) {
    }

    bool isEnPassantCapture(Point2DPair point2dPair);
    void setUsedFirstMove();
    void setEnpassantSquare(Point2DPair point2dPair);
    bool isMovingByTwoSpaces(Point2DPair point2dPair);
    void afterPieceMoved(Point2DPair point2dPair) override;
    bool isPieceBlockingPath(Point2DPair point2dPair) override;
    bool getIsValidPath(Point2DPair point2dPair) override;
    void clearEnPassantCaptureSquare(Point2DPair point2dPair);
    int getMovedTwoSpacesTurn();
    int getCapturingPieceEnpassantRow();
    void setMovementTargets(Point2D point2d) override;
};

#endif //CHESS_PAWN_H
