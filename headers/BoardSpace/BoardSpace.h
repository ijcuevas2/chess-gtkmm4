//
// Created by Ismael Cuevas on 7/15/24.
//

#ifndef CHESS_BOARDSPACE_H
#define CHESS_BOARDSPACE_H


#include "../ChessPieces/ChessPiece.h"
#include "../HintMarker/HintMarker.h"

class BoardSpace {
private:
    ChessPiece* chessPiecePtr;
    HintMarker* hintMarkerPtr;
    bool hasDarkBackground;
    int xIndex;
    int yIndex;

public:
    int getXIndex() const;
    int getYIndex() const;

    BoardSpace(ChessPiece* chessPiecePtr, int xIndex, int yIndex);
    void setSelectedBackground();
    void setUnselectedBackground();
    ChessPiece* getChessPiecePtr();
    PlayerID getPlayerId();
    void setChessPiecePtr(ChessPiece* chessPiecePtr);
    void initMarker();
    bool canMovePieceToIndex(int destX, int destY);
    void showHint();
    void hideHint();
};


#endif //CHESS_BOARDSPACE_H
