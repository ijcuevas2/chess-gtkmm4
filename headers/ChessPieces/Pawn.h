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

    bool canMoveToTarget(Coordinates coordinates) override;
    bool isCorrectDirection(Coordinates coordinates);
    bool canMoveFirstTurn(Coordinates coordinates);
    bool canDiagonalCapture(Coordinates coordinates);
    bool canMoveSingleSpaceForward(Coordinates coordinates);
    bool isDiagonalMove(Coordinates coordinates);
    bool canCapture(Coordinates coordinates);
    bool canEnPassantCapture(Coordinates coordinates);
    void setUsedFirstMove();
    void setMovedTwoSpacesTurn(Coordinates coordinates);
    void afterPieceMoved(Coordinates coordinates) override;
    bool isPieceBlockingPath(Coordinates coordinates) override;
    bool getIsValidPath(Coordinates coordinates) override;
    Coordinates getNextCoordinates(Coordinates coordinates) override;
    int getMovedTwoSpacesTurn();
};

#endif //CHESS_PAWN_H
