#include "../../headers/ChessBoard/ChessBoardView.h"
#include <iostream>

ChessBoardView::ChessBoardView() : Gtk::Box(Gtk::Orientation::VERTICAL) {
  int width = 450;
  int height = 450;
  m_drawingArea.set_content_width(width);
  m_drawingArea.set_content_height(height);

  m_drawingArea.set_draw_func(sigc::mem_fun(*this, &ChessBoardView::on_draw));

  auto controller = Gtk::GestureClick::create();
  controller->signal_pressed().connect(sigc::mem_fun(*this, &ChessBoardView::on_pressed));
  m_drawingArea.add_controller(controller);

  // Create the menu model
  m_menuModel = Gio::Menu::create();
  auto fileMenu = Gio::Menu::create();
  m_menuModel->append_submenu("File", fileMenu);

  // Create actions
  m_newGameAction = Gio::SimpleAction::create("new_game");
  m_exitAction = Gio::SimpleAction::create("exit");

  // Connect action signals using lambda functions
  m_newGameAction->signal_activate().connect([this](const Glib::VariantBase&) {
      this->on_new_game_clicked();
  });
  m_exitAction->signal_activate().connect([this](const Glib::VariantBase&) {
      this->on_exit_clicked();
  });

  // Add actions to the application
  auto app = Gtk::Application::get_default();
  app->add_action(m_newGameAction);
  app->add_action(m_exitAction);

  // Add menu items
  fileMenu->append("New Game", "app.new_game");
  fileMenu->append("Exit", "app.exit");

  // Create the menu bar
  m_menuBar = Gtk::make_managed<Gtk::PopoverMenuBar>(m_menuModel);

  // Create the toolbar
  m_toolbar = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
  m_toolbar->set_spacing(5);
  m_toolbar->set_margin(5);

  // Add the current player turn label to the left side of the toolbar
  m_currentPlayerLabel = Gtk::make_managed<Gtk::Label>("Current Turn: White");
  m_currentPlayerLabel->set_halign(Gtk::Align::START);
  m_toolbar->append(*m_currentPlayerLabel);

  // Add a spacer to push the undo button to the right
  auto spacer = Gtk::make_managed<Gtk::Label>();
  spacer->set_hexpand(true);
  m_toolbar->append(*spacer);

  // Add the undo button to the toolbar
  m_undoButton = Gtk::make_managed<Gtk::Button>("Undo");
  m_undoButton->signal_clicked().connect(sigc::mem_fun(*this, &ChessBoardView::on_undo_clicked));
  m_toolbar->append(*m_undoButton);

  // Add the menu bar to the box
  append(*m_menuBar);

  // Add the toolbar to the box
  append(*m_toolbar);

  // Add the drawing area to the box
  append(m_drawingArea);
}

void ChessBoardView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
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
  PlayerID playerId = chessBoardController.getTurnPlayerId();
  bool isWhiteTurn = playerId == PlayerID::PLAYER_WHITE;
  std::string turnLabel = isWhiteTurn ? "Current Turn: White" : "Current Turn: Black";
  if (m_currentPlayerLabel != nullptr) {
    m_currentPlayerLabel->set_text(turnLabel);
  }
}

void ChessBoardView::initBoard() {
  chessBoardController.initBoard();
}

void ChessBoardView::clearBoard() {
  chessBoardController.clearBoard();
}

void ChessBoardView::on_new_game_clicked() {
  // Handle new game action
  clearBoard();
  initBoard();
  m_drawingArea.queue_draw();
  this->updateLabel();
}

void ChessBoardView::on_exit_clicked() {
  // Handle exit action
  auto app = Gtk::Application::get_default();
  app->quit();
}

void ChessBoardView::on_undo_clicked() {
  // Implement undo logic here
  std::cout << "Undo clicked" << std::endl;
}