//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessWindow/ChessWindow.h"

ChessWindow::ChessWindow() : m_box(Gtk::Orientation::VERTICAL) {
  set_title("Chess");
  set_default_size(450, 450);

  header_bar = Gtk::make_managed<Gtk::HeaderBar>();
  header_bar->set_show_title_buttons(true);
  header_bar->set_decoration_layout(":close");
  header_bar->set_title_widget(*Gtk::make_managed<Gtk::Label>("Chess"));

  auto primary_click_controller = Gtk::GestureClick::create();
  primary_click_controller->set_button(GDK_BUTTON_PRIMARY);  // Listen for any button
  primary_click_controller->signal_released().connect(
          sigc::mem_fun(*this, &ChessWindow::on_header_bar_primary_click_released));
  header_bar->add_controller(primary_click_controller);

  set_titlebar(*header_bar);

  set_titlebar_right_click_behavior();

  m_chessBoardView = Gtk::make_managed<ChessBoardView>(chessMediator);
  chessMediator.getOpenFileDialogSignal().connect(sigc::mem_fun(*this, &ChessWindow::openFileDialog));
  chessMediator.getOpenSaveDialogSignal().connect(sigc::mem_fun(*this, &ChessWindow::saveFileDialog));
  set_child(*m_chessBoardView);

  // Create an event controller for key events
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(sigc::mem_fun(*this, &ChessWindow::on_key_pressed), false);
  add_controller(controller);
}

void ChessWindow::on_header_bar_primary_click_released(int n_press, double x, double y) {
  clearClick();
}

void ChessWindow::set_titlebar_right_click_behavior() {
  auto settings = Gtk::Settings::get_default();
  if (settings) {
    settings->property_gtk_titlebar_right_click() = "none";
  }
}

void ChessWindow::clearClick() {
  header_bar->set_sensitive(false);
  header_bar->set_sensitive(true);
}

void ChessWindow::saveFileDialog() {
  auto dialog = Gtk::FileDialog::create();

  std::string fileName = FileUtils::generateGMTFilename();
  dialog->set_title("Save File");
  dialog->set_modal(true);
  dialog->set_initial_name(fileName);

  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Chess Files (*.chess)");
  filter_text->add_mime_type("text/plain");

  // Create a Gio::ListStore to hold the filters
  auto filters = Gio::ListStore<Gtk::FileFilter>::create();
  filters->append(filter_text);

  // Set the filters
  dialog->set_filters(filters);

  // Set default filter
  dialog->set_default_filter(filter_text);

  // Use save() for saving files
  dialog->save(*this,
               [this, dialog](const Glib::RefPtr<Gio::AsyncResult>& result) {
                   try {
                     auto file = dialog->save_finish(result);
                     if (file) {
                       std::cout << "File selected for saving: " << file->get_path() << std::endl;
                       // Here you would typically save your file
                     }
                   } catch (const Glib::Error& error) {
                     std::cerr << "Error: " << error.what() << std::endl;
                   }
               });
}

void ChessWindow::openFileDialog() {
  Glib::RefPtr<Gtk::FileDialog> dialog = Gtk::FileDialog::create();
  dialog->set_title("Please choose a file");
  dialog->set_modal(true);
  // dialog->set_initial_name("file.txt");

  Glib::RefPtr<Gio::ListStore<Gtk::FileFilter>> filters = Gio::ListStore<Gtk::FileFilter>::create();
  std::string chessSavesDir = "chess_saves";
  fs::path currentPath = fs::current_path() / chessSavesDir;
  Glib::RefPtr<Gio::File> initial_folder = Gio::File::create_for_path(currentPath);
  dialog->set_initial_folder(initial_folder);

  Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Chess Save Files (*.chess)");
  filter_any->add_pattern("*.chess");
  filters->append(filter_any);

  dialog->set_filters(filters);

  dialog->open(*this, [this, dialog](const Glib::RefPtr<Gio::AsyncResult>& result) {
      try {
        Glib::RefPtr<Gio::File> file = dialog->open_finish(result);
        if (file) {
          std::string filePath = file->get_path();
          std::cout << "File selected: " << filePath << std::endl;
          // Handle the selected file here
          chessMediator.getAfterFileLoadedSignal().emit(filePath);
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

bool ChessWindow::on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state) {
  if (keyval == GDK_KEY_Escape) {
    chessMediator.getClearSelectedBoardSpaceUISignal().emit();
    chessMediator.getUpdateUiSignal().emit();
    return true;
  }

  return false;
}