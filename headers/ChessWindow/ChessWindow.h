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
protected:
    // Child widgets
    void on_menu_new_game();
    void on_menu_quit();
    Gtk::Box m_box;
    Glib::RefPtr<Gio::Menu> m_menu;
    Gtk::PopoverMenu m_popover_menu;
    Gtk::MenuButton m_menu_button;
private:
    ChessBoardView* m_chessBoardView;
};


#endif //CHESS_CHESSWINDOW_H
