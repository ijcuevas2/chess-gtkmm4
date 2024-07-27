//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessWindow/ChessWindow.h"

ChessWindow::ChessWindow(): m_box(Gtk::Orientation::VERTICAL) {
  set_title("Chess GTKMM4");
  set_default_size(450, 450);

  m_chessBoardView = Gtk::make_managed<ChessBoardView>();
  set_child(*m_chessBoardView);
}