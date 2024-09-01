//
// Created by Ismael Cuevas on 7/22/24.
//

#ifndef CHESS_CHESSBOARDCONTROLLER_H
#define CHESS_CHESSBOARDCONTROLLER_H

#include <gtkmm.h>
#include "ChessBoardModel.h"
#include "FenModel/FenModel.h"
#include "ChessMediator/ChessMediator.h"

class ChessBoardController {
public:
    ChessBoardController(ChessMediator & chessMediator);
    void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
    void on_pressed(int n_press, double x, double y, int width, int height);
    void initBoard();
    void saveStateToFile();
    void loadStateFromFile(std::string filePath);
    void clearBoard();
    PlayerID getTurnPlayerId();
private:
    ChessMediator & chessMediator;
    ChessBoardModel chessBoardModel{chessMediator};
    FenModel fenModel{chessBoardModel, chessMediator};
    void updateHalfTurnClock(ChessPiece* srcChessPiecePtr, ChessPiece* targetChessPiecePtr);
    void resetChessBoardUI();
};


#endif //CHESS_CHESSBOARDCONTROLLER_H
