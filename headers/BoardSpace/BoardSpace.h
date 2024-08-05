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
    bool showMarkerValue = false;
    int row;
    int col;

public:
    int getCol() const;
    int getRow() const;

    BoardSpace(ChessPiece* chessPiecePtr, int row, int col);
    ChessPiece* getChessPiecePtr();
    void clearChessPiecePtr();
    PlayerID getPlayerId();
    void setChessPiecePtr(ChessPiece* chessPiecePtr);
    bool getShowMarker();
    void showMarker();
    void hideMarker();
    void showHintMarkers(BoardSpace* boardSpacePtr);
    void hideHintMarkers(BoardSpace* boardSpacePtr);
};


#endif //CHESS_BOARDSPACE_H
