//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSWINDOW_H
#define CHESS_CHESSWINDOW_H

#include <gtkmm.h>
#include "../ChessBoard/ChessBoardView.h"
#include <glibmm/signalproxy.h>
#include <sigc++/signal.h>

class ChessWindow : public Gtk::Window {
public:
    ChessWindow();
protected:
    // Child widgets
    Gtk::Box m_box;
    Glib::RefPtr<Gio::Menu> m_menu;
    Gtk::PopoverMenu m_popover_menu;
    Gtk::MenuButton m_menu_button;
    sigc::signal<std::string()> handleOnLoadClickedSignal;
private:
    ChessBoardView *m_chessBoardView;
    std::string handleOnLoadClicked();
    void openFileDialog();
};


#endif //CHESS_CHESSWINDOW_H
