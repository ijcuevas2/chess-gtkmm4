//
// Created by Ismael Cuevas on 7/22/24.
//

#ifndef CHESS_CHESSBOARDCONTROLLER_H
#define CHESS_CHESSBOARDCONTROLLER_H
#include <gtkmm.h>
#include "ChessBoardModel.h"

class ChessBoardController {
public:
    ChessBoardController(ChessBoardModel & chessBoardModel);
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void on_pressed(int n_press, double x, double y, int width, int height);
private:
    ChessBoardModel & chessBoardModel;
};


#endif //CHESS_CHESSBOARDCONTROLLER_H
