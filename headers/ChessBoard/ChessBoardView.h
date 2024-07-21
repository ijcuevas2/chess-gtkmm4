//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSBOARDVIEW_H
#define CHESS_CHESSBOARDVIEW_H
#include <gtkmm.h>
#include "ChessBoardModel.h"
#include "../ChessImagesInfo/ChessImagesInfo.h"

class ChessBoardView : public Gtk::DrawingArea {
    ChessBoardView();
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void on_pressed(int n_press, double x, double y);
    void load_pieces();
private:
    ChessBoardModel* chessBoardModel;
    std::vector<std::vector<BoardSpace*>>* boardPtr;
};


#endif //CHESS_CHESSBOARDVIEW_H
