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
    bool canCastle;
    bool isInCheck;
    bool isCheckmate;
public:
    King(PlayerID playerId, ChessMediator & chessMediator);
    bool getCanCastle();
    void setCanCastleToFalse();
    bool getIsCheckmate();
    void setIsCheckmate(bool value);
    void setIsInCheck(bool inCheck);
    bool getIsInCheck();
    bool getIsValidPath(Point2DPair point2dPair) override;
    void afterPieceMoved(Point2DPair point2dPair) override;
    bool isPieceBlockingPath(Point2DPair point2dPair) override;
};


#endif //CHESS_KING_H
