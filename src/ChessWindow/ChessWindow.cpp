//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessWindow/ChessWindow.h"

ChessWindow::ChessWindow(): m_box(Gtk::Orientation::VERTICAL) {
  set_title("Chess GTKMM4");
  set_default_size(450, 450);


  // Create menu
  m_menu = Gio::Menu::create();
  auto game_menu = Gio::Menu::create();
  game_menu->append("_New Game", "app.new_game");
  game_menu->append("_Quit", "app.quit");
  m_menu->append_submenu("_Game", game_menu);

  // Set up menu button
  m_menu_button.set_label("Menu");
  m_menu_button.set_menu_model(m_menu);

  // Add menu button to the box
  m_box.append(m_menu_button);

  // Add a label to show some content
  auto label = Gtk::make_managed<Gtk::Label>("Chess Board Goes Here");
  m_box.append(*label);

  // Add the box to the window
  set_child(m_box);

  // Add actions
  auto action_group = Gio::SimpleActionGroup::create();
  action_group->add_action("new_game", sigc::mem_fun(*this, &ChessWindow::on_menu_new_game));
  action_group->add_action("quit", sigc::mem_fun(*this, &ChessWindow::on_menu_quit));
  insert_action_group("app", action_group);

  // You can specify the path to the pieces directory here
  m_chessBoardView = Gtk::make_managed<ChessBoardView>();
  set_child(*m_chessBoardView);
}

void ChessWindow::on_menu_new_game() {
  std::cout << "Starting a new chess game" << std::endl;
  // Add logic to start a new game
}

void ChessWindow::on_menu_quit() {
  close();
}