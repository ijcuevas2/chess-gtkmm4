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
    int row;
    int col;

public:
    int getCol() const;
    int getRow() const;

    BoardSpace(ChessPiece* chessPiecePtr, int row, int col);
    void setSelectedBackground();
    void setUnselectedBackground();
    ChessPiece* getChessPiecePtr();
    void clearChessPiecePtr();
    PlayerID getPlayerId();
    void setChessPiecePtr(ChessPiece* chessPiecePtr);
    void initMarker();
    bool canMovePieceToIndex(int destX, int destY);
    void showHint();
    void hideHint();
};


#endif //CHESS_BOARDSPACE_H
