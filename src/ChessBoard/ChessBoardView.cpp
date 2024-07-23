//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessBoard/ChessBoardView.h"

ChessBoardView::ChessBoardView() {
  set_content_width(400);
  set_content_height(400);
  set_draw_func(sigc::mem_fun(*this, &ChessBoardView::on_draw));
  add_controller(Gtk::GestureClick::create());
  auto controller = Gtk::GestureClick::create();
  controller->signal_pressed().connect(sigc::mem_fun(*this, &ChessBoardView::on_pressed));
  add_controller(controller);
}

void ChessBoardView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
  chessBoardController.on_draw(cr, width, height);
}

void ChessBoardView::on_pressed(int n_press, double x, double y) {
  int height = get_height();
  int width = get_width();
  chessBoardController.on_pressed(n_press, x, y, width, height);
  queue_draw();
}

