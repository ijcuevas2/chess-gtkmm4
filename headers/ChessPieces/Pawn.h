//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "ChessPiece.h"

class Pawn : public virtual ChessPiece {
private:
    bool isFirstMove = true;
    int movedTwoSpacesTurn = -1;
    bool isEnPassantEligible = false;
public:
    Pawn(PlayerID playerId): ChessPiece(playerId, PieceType::PAWN) {
    }

    bool canMove(Coordinates coordinates) override;
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
    int getMovedTwoSpacesTurn();
};

#endif //CHESS_PAWN_H
