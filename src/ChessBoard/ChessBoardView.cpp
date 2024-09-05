#include "../../headers/ChessBoard/ChessBoardView.h"
#include <iostream>

ChessBoardView::ChessBoardView(ChessMediator & chessMediator) : Gtk::Box(Gtk::Orientation::VERTICAL), chessMediator(chessMediator) {
  int width = 450;
  int height = 450;
  m_drawingArea.set_content_width(width);
  m_drawingArea.set_content_height(height);

  m_drawingArea.set_draw_func(sigc::mem_fun(*this, &ChessBoardView::on_draw));
  chessMediator.getUpdateUiSignal().connect(sigc::mem_fun(*this, &ChessBoardView::updateUi));
  chessMediator.getUpdateUndoButtonUiSignal().connect(sigc::mem_fun(*this, &ChessBoardView::updateUndoButtonUi));
  chessMediator.getUpdateLabelSignal().connect(sigc::mem_fun(*this, &ChessBoardView::updateLabel));

  auto controller = Gtk::GestureClick::create();
  controller->signal_pressed().connect(sigc::mem_fun(*this, &ChessBoardView::on_pressed));
  m_drawingArea.add_controller(controller);

  m_menuModel = Gio::Menu::create();
  auto fileMenu = Gio::Menu::create();
  m_menuModel->append_submenu("File", fileMenu);

  m_newGameAction = Gio::SimpleAction::create("new_game");
  m_exitAction = Gio::SimpleAction::create("exit");
  m_saveAction = Gio::SimpleAction::create("save");
  m_loadAction = Gio::SimpleAction::create("load");

  m_newGameAction->signal_activate().connect([this](const Glib::VariantBase &) {
      this->onNewGameClicked();
  });
  m_exitAction->signal_activate().connect([this](const Glib::VariantBase &) {
      this->onExitClicked();
  });
  m_saveAction->signal_activate().connect([this](const Glib::VariantBase &) {
      this->onSaveClicked();
  });
  m_loadAction->signal_activate().connect([this](const Glib::VariantBase &) {
      this->onLoadClicked();
  });

  auto app = Gtk::Application::get_default();
  app->add_action(m_newGameAction);
  app->add_action(m_exitAction);
  app->add_action(m_saveAction);
  app->add_action(m_loadAction);

  fileMenu->append("New Game", "app.new_game");
  fileMenu->append("Save", "app.save");
  fileMenu->append("Load", "app.load");
  fileMenu->append("Exit", "app.exit");

  m_menuBar = Gtk::make_managed<Gtk::PopoverMenuBar>(m_menuModel);

  m_toolbar = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
  m_toolbar->set_spacing(5);
  m_toolbar->set_margin(5);

  m_currentPlayerLabel = Gtk::make_managed<Gtk::Label>("Current Turn: White");
  m_currentPlayerLabel->set_halign(Gtk::Align::START);
  m_toolbar->append(*m_currentPlayerLabel);

  auto spacer = Gtk::make_managed<Gtk::Label>();
  spacer->set_hexpand(true);
  m_toolbar->append(*spacer);

  m_undoButton = Gtk::make_managed<Gtk::Button>("Undo");
  m_undoButton->signal_clicked().connect(sigc::mem_fun(*this, &ChessBoardView::onUndoButtonClicked));
  m_toolbar->append(*m_undoButton);

  append(*m_menuBar);
  append(*m_toolbar);
  append(m_drawingArea);
  initBoard();
}

void ChessBoardView::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height) {
  chessBoardController.on_draw(cr, width, height);
}

void ChessBoardView::on_pressed(int n_press, double x, double y) {
  int height = m_drawingArea.get_height();
  int width = m_drawingArea.get_width();
  chessBoardController.on_pressed(n_press, x, y, width, height);
  updateLabel();
  m_drawingArea.queue_draw();
}

void ChessBoardView::updateLabel() {
  PlayerID playerId = chessMediator.getTurnPlayerIdSignal().emit();
  bool isWhiteTurn = playerId == PlayerID::PLAYER_WHITE;
  std::string turnLabel = isWhiteTurn ? "Current Turn: White" : "Current Turn: Black";

  bool isInCheck = chessMediator.getIsKingInCheckSignal().emit(playerId);
  if (isInCheck) {
    turnLabel += " (In Check!) ";
  }

  if (m_currentPlayerLabel != nullptr) {
    m_currentPlayerLabel->set_text(turnLabel);
  }
}

void ChessBoardView::initBoard() {
  chessBoardController.initBoard();
  updateUndoButtonUi(false);
}

void ChessBoardView::clearBoard() {
  chessBoardController.clearBoard();
}

void ChessBoardView::onNewGameClicked() {
  clearBoard();
  initBoard();
  m_drawingArea.queue_draw();
  this->updateLabel();
}

void ChessBoardView::onSaveClicked() {
  chessMediator.getOpenSaveDialogSignal().emit();
}

void ChessBoardView::onLoadClicked() {
  chessMediator.getOpenFileDialogSignal().emit();
}

void ChessBoardView::updateUi() {
  m_drawingArea.queue_draw();
}

void ChessBoardView::onExitClicked() {
  auto app = Gtk::Application::get_default();
  app->quit();
}

void ChessBoardView::onUndoButtonClicked() {
  chessMediator.getOnUndoButtonClicked().emit();
}

void ChessBoardView::updateUndoButtonUi(bool isEnabled) {
  m_undoButton->set_sensitive(isEnabled);
}
