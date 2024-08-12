//
// Created by Ismael Cuevas on 7/22/24.
//

#ifndef CHESS_CHESSBOARDCONTROLLER_H
#define CHESS_CHESSBOARDCONTROLLER_H

#include <gtkmm.h>
#include "ChessBoardModel.h"
#include "FenModel/FenModel.h"
#include "ChessWindowMediator/ChessWindowMediator.h"

class ChessBoardController {
public:
    ChessBoardController(ChessWindowMediator & chessWindowMediator);
    void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
    void on_pressed(int n_press, double x, double y, int width, int height);
    void initBoard();
    void clearBoard();
    void saveStateToFile();
    PlayerID getTurnPlayerId();
private:
    ChessBoardModel chessBoardModel{};
    ChessWindowMediator & chessWindowMediator;
    FenModel fenModel{chessBoardModel, chessWindowMediator};
};


#endif //CHESS_CHESSBOARDCONTROLLER_H
