//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSBOARDVIEW_H
#define CHESS_CHESSBOARDVIEW_H

#include <gtkmm.h>
#include "ChessBoardModel.h"
#include "../ChessImagesInfo/ChessImagesInfo.h"
#include "ChessBoard/ChessBoardController.h"

class ChessBoardView : public Gtk::Box {
public:
    ChessBoardView();

private:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void on_pressed(int n_press, double x, double y);
    void on_new_game_clicked();
    void on_exit_clicked();
    void initBoard();
    void clearBoard();

    ChessBoardController chessBoardController;
    Gtk::DrawingArea m_drawingArea;
    Glib::RefPtr<Gio::Menu> m_menuModel;
    Gtk::PopoverMenuBar* m_menuBar;
    Glib::RefPtr<Gio::SimpleAction> m_newGameAction;
    Glib::RefPtr<Gio::SimpleAction> m_exitAction;

    Gtk::Box* m_toolbar;
    Gtk::Button* m_undoButton;
    void on_undo_clicked();
};

#endif //CHESS_CHESSBOARDVIEW_H
