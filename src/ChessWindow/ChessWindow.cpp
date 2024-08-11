//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessWindow/ChessWindow.h"

ChessWindow::ChessWindow() : m_box(Gtk::Orientation::VERTICAL) {
  set_title("Chess");
  set_default_size(450, 450);
  property_decorated() = false;
  m_chessBoardView = Gtk::make_managed<ChessBoardView>(handleOnLoadClickedSignal);
  set_child(*m_chessBoardView);
  handleOnLoadClickedSignal.connect(sigc::mem_fun(*this, &ChessWindow::handleOnLoadClicked));
}

std::string ChessWindow::handleOnLoadClicked() {
  this->openFileDialog();
  return "";
}

void ChessWindow::openFileDialog() {
  auto dialog = Gtk::FileDialog::create();
  dialog->set_title("Please choose a file");
  dialog->set_modal(true);

  auto filters = Gio::ListStore<Gtk::FileFilter>::create();

  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  filters->append(filter_text);

  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  filters->append(filter_any);

  dialog->set_filters(filters);

  dialog->open(*this, [this, dialog](const Glib::RefPtr<Gio::AsyncResult>& result) {
      try {
        auto file = dialog->open_finish(result);
        if (file) {
          std::cout << "File selected: " << file->get_path() << std::endl;
          // Handle the selected file here
        }
      } catch (const Glib::Error& error) {
        if (error.code() != Gtk::DialogError::DISMISSED) {
          std::cerr << "Error opening file: " << error.what() << std::endl;
        } else {
          std::cout << "File selection cancelled." << std::endl;
        }
      }
  });
}
