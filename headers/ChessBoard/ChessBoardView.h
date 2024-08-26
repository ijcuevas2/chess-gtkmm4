//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSBOARDVIEW_H
#define CHESS_CHESSBOARDVIEW_H

#include <gtkmm.h>
#include "ChessBoardModel.h"
#include "../ChessImagesInfo/ChessImagesInfo.h"
#include "ChessBoard/ChessBoardController.h"
#include "ChessWindowMediator/ChessWindowMediator.h"

class ChessBoardView : public Gtk::Box {
public:
    ChessBoardView(ChessWindowMediator & chessWindowMediator);
private:
    void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
    void on_pressed(int n_press, double x, double y);
    void onNewGameClicked();
    void onExitClicked();
    void onSaveClicked();
    void onLoadClicked();
    void initBoard();
    void clearBoard();
    void updateLabel();
    Gtk::DrawingArea m_drawingArea;
    Glib::RefPtr<Gio::Menu> m_menuModel;
    Gtk::PopoverMenuBar *m_menuBar;
    Glib::RefPtr<Gio::SimpleAction> m_newGameAction;
    Glib::RefPtr<Gio::SimpleAction> m_exitAction;
    Glib::RefPtr<Gio::SimpleAction> m_saveAction;
    Glib::RefPtr<Gio::SimpleAction> m_loadAction;
    ChessWindowMediator & chessWindowMediator;
    ChessBoardController chessBoardController{chessWindowMediator};

    Gtk::Box *m_toolbar;
    Gtk::Button *m_undoButton;
    Gtk::Label *m_currentPlayerLabel;

    void onUndoButtonClicked();
    void handleLoad(std::string result);
    void updateUi();
    void updateUndoButtonUi(bool isEnabled);
};

#endif //CHESS_CHESSBOARDVIEW_H
