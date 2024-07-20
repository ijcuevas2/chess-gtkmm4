//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSWINDOW_H
#define CHESS_CHESSWINDOW_H
#include <gtkmm.h>
#include "../ChessBoard/ChessBoardModel.h"

class ChessWindow : public Gtk::Window {
public:
    ChessWindow();
private:
    ChessBoardModel* m_chessBoardModel;
};


#endif //CHESS_CHESSWINDOW_H
