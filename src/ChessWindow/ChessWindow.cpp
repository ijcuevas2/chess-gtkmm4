//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessWindow/ChessWindow.h"

ChessWindow::ChessWindow() {
  set_title("Chess GTKMM4");
  set_default_size(400, 400);

  // You can specify the path to the pieces directory here
  m_chessBoardView = Gtk::make_managed<ChessBoardView>();
  set_child(*m_chessBoardView);
}