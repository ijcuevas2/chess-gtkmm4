//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSBOARDMODEL_H
#define CHESS_CHESSBOARDMODEL_H
#include <gtkmm.h>


class ChessBoardModel: public Gtk::DrawingArea {
public:
    ChessBoardModel() {
      set_content_width(400);
      set_content_height(400);
      set_draw_func(sigc::mem_fun(*this, &ChessBoardModel::on_draw));
      add_controller(Gtk::GestureClick::create());
      auto controller = Gtk::GestureClick::create();
      controller->signal_pressed().connect(sigc::mem_fun(*this, &ChessBoardModel::on_pressed));
      add_controller(controller);
      load_pieces();
    }

    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    }

    void on_pressed(int n_press, double x, double y) {
    }

    void load_pieces(){
    }
};


#endif //CHESS_CHESSBOARDMODEL_H
