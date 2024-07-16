//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSWINDOW_H
#define CHESS_CHESSWINDOW_H
#include <gtkmm/window.h>
#include "../ChessBoard/ChessBoardModel.h"

class ChessWindow : public Gtk::Window {
public:
    ChessWindow() : Gtk::Window() {
      set_title("Chess GTKMM4");
      set_default_size(400, 400);

      // You can specify the path to the pieces directory here
      m_chessBoardModel = Gtk::make_managed<ChessBoardModel>();
      set_child(*m_chessBoardModel);
    }

private:
    ChessBoardModel* m_chessBoardModel;
};


#endif //CHESS_CHESSWINDOW_H
