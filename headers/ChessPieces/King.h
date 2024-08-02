//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H
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

    bool canMoveToTarget(Coordinates coordinates) override;
    bool getHasMoved();
    void setHasMoved();
    bool IsInCheck() const;
    bool getIsValidPath(Coordinates coordinates) override;
    void afterPieceMoved(Coordinates coordinates) override;
    std::vector<Rook*> rooksEligibleForCastling();
    void addRookEligibleForCastling(std::vector<Rook*> & rookPtrList, int xIndex, int yIndex);
    void addRookEligibleForCastlingHelper(Rook* rookPtr, std::vector<Rook*> & rookPtrList, int xIndex, int yIndex);
    bool isPieceBlockingPath(Coordinates coordinates) override;
};


#endif //CHESS_KING_H
