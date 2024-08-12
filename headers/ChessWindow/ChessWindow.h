//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSWINDOW_H
#define CHESS_CHESSWINDOW_H

#include <gtkmm.h>
#include "../ChessBoard/ChessBoardView.h"
#include "ChessWindowMediator/ChessWindowMediator.h"

class ChessWindow : public Gtk::Window {
public:
    ChessWindow();
protected:
    // Child widgets
    Gtk::Box m_box;
    Glib::RefPtr<Gio::Menu> m_menu;
    Gtk::PopoverMenu m_popover_menu;
    Gtk::MenuButton m_menu_button;
private:
    ChessBoardView *m_chessBoardView;
    void openFileDialog();
    ChessWindowMediator chessWindowMediator;
};


#endif //CHESS_CHESSWINDOW_H
