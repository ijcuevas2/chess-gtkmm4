//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H
#include "ChessPiece.h"
#include "Rook.h"

class King : public virtual ChessPiece {
private:
    bool hasMoved;
    bool isInCheck;
public:
    King(PlayerID playerId) : ChessPiece(playerId, PieceType::KING) {
    }
    bool canMove(Coordinates coordinates) override;
    bool HasMoved() const;
    bool IsInCheck() const;
    void afterPieceMoved(Coordinates coordinates) override;
    std::vector<Rook*> rooksEligibleForCastling();
    void addRookEligibleForCastling(std::vector<Rook*> & rookPtrList, int xIndex, int yIndex);
    void addRookEligibleForCastlingHelper(Rook* rookPtr, std::vector<Rook*> & rookPtrList, int xIndex, int yIndex);
};


#endif //CHESS_KING_H
