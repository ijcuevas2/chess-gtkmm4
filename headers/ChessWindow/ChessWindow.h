//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSWINDOW_H
#define CHESS_CHESSWINDOW_H
#include <gtkmm.h>
#include "../ChessBoard/ChessBoardView.h"

class ChessWindow : public Gtk::Window {
public:
    ChessWindow();
private:
    ChessBoardView* m_chessBoardView;
};


#endif //CHESS_CHESSWINDOW_H
