//
// Created by Ismael Cuevas on 7/15/24.
//

#ifndef CHESS_BOARDSPACE_H
#define CHESS_BOARDSPACE_H


#include "../ChessPieces/ChessPiece.h"
#include "../HintMarker/HintMarker.h"

class BoardSpace {
private:
    ChessPiece *chessPiece;
    HintMarker *hintMarker;
    bool hasDarkBackground;
    int xIndex;
    int yIndex;

public:
    int getXIndex() const;
    int getYIndex() const;

    BoardSpace(ChessPiece* chessPiece, int xIndex, int yIndex);
    void setSelectedBackground();
    void setUnselectedBackground();
    ChessPiece* getChessPiece();
    PlayerID getPlayerId();
    void setChessPiece(ChessPiece* chessPiece);
    void initMarker();
    bool canMovePieceToIndex(int destX, int destY);
    void showHint();
    void hideHint();
};


#endif //CHESS_BOARDSPACE_H
