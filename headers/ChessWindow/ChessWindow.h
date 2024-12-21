//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSWINDOW_H
#define CHESS_CHESSWINDOW_H

#include <gtkmm.h>
#include <gdkmm/surface.h>
#include "../ChessBoard/ChessBoardView.h"
#include "ChessMediator/ChessMediator.h"

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
    Gtk::HeaderBar* header_bar;
    void openFileDialog();
    void saveFileDialog();
    void clearClick();
    bool on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);
    ChessMediator chessMediator;
    void on_header_bar_primary_click_released(int n_press, double x, double y);
    void set_titlebar_right_click_behavior();
    void openCheckmateDialog();
    void openStalemateDialog();
    void openDialogWithMessage(const std::string message);
};

#endif //CHESS_CHESSWINDOW_H
