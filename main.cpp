#include <gtkmm.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include "headers/ChessWindow/ChessWindow.h"

int main(int argc, char **argv) {
  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<ChessWindow>(argc, argv);
}