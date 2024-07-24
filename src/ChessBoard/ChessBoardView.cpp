//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessBoard/ChessBoardView.h"

ChessBoardView::ChessBoardView() : Gtk::Box(Gtk::Orientation::VERTICAL) {
  m_drawingArea.set_content_width(450);
  m_drawingArea.set_content_height(450);
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

  // Add the menu bar to the box
  append(*m_menuBar);

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
  m_drawingArea.queue_draw();
}

void ChessBoardView::initBoard() {
  chessBoardController.initBoard();
}

void ChessBoardView::clearBoard() {
  chessBoardController.clearBoard();
}

void ChessBoardView::on_new_game_clicked() {
  // Handle new game action
  // Implement your new game logic here
  clearBoard();
  initBoard();
  m_drawingArea.queue_draw();
}

void ChessBoardView::on_exit_clicked() {
  // Handle exit action
  auto app = Gtk::Application::get_default();
  app->quit();
}
