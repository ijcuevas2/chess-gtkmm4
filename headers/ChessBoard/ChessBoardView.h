//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSBOARDVIEW_H
#define CHESS_CHESSBOARDVIEW_H
#include <gtkmm.h>
#include "ChessBoardModel.h"
#include "../ChessImagesInfo/ChessImagesInfo.h"
#include "ChessBoard/ChessBoardController.h"

class ChessBoardView : public Gtk::DrawingArea {
public:
    ChessBoardView();
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void on_pressed(int n_press, double x, double y);
private:
    ChessBoardModel chessBoardModel{};
    ChessBoardController chessBoardController{chessBoardModel};
};


#endif //CHESS_CHESSBOARDVIEW_H
