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
  primary_click_controller->signal_released().connect(sigc::mem_fun(*this, &ChessWindow::on_header_bar_primary_click_released));
  header_bar->add_controller(primary_click_controller);

  set_titlebar(*header_bar);

  set_titlebar_right_click_behavior();

  m_chessBoardView = Gtk::make_managed<ChessBoardView>(chessMediator);
  chessMediator.getOpenFileDialogSignal().connect(sigc::mem_fun(*this, &ChessWindow::openFileDialog));
  chessMediator.getOpenSaveDialogSignal().connect(sigc::mem_fun(*this, &ChessWindow::saveFileDialog));
  chessMediator.getOpenCheckmateDialogSignal().connect(sigc::mem_fun(*this, &ChessWindow::openCheckmateDialog));
  chessMediator.getOpenStalemateDialogSignal().connect(sigc::mem_fun(*this, &ChessWindow::openStalemateDialog));
  chessMediator.getOnRequestDrawActionSignal().connect(sigc::mem_fun(*this, &ChessWindow::onRequestDrawAction));
  chessMediator.getOnSurrenderActionSignal().connect(sigc::mem_fun(*this, &ChessWindow::onRequestForfeitAction));
  chessMediator.getOpenThreefoldRepetitionDialogSignal().connect(sigc::mem_fun(*this, &ChessWindow::onThreefoldRepetitionDrawAction));
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
                       std::string filePath = file->get_path();
                       std::string chessExtension = ".chess";
                       size_t pos = filePath.find(chessExtension);
                       if (pos == std::string::npos) {
                          filePath += chessExtension;
                       }

                       chessMediator.getSaveStateToFileSignal().emit(filePath);
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
  Glib::RefPtr<Gio::File> initial_folder = Gio::File::create_for_path(currentPath.string());
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

void ChessWindow::openCheckmateDialog() {
  PlayerID playerId = chessMediator.getOpponentTurnPlayerIdSignal().emit();
  std::string playerStr = playerId == PlayerID::PLAYER_WHITE ? "White" : "Black";
  std::string message = playerStr + " wins!";
  std::string title = "Checkmate";
  this->openNewGameQuitDialogWithMessage(message, title);
}

void ChessWindow::openStalemateDialog() {
  std::string message = "Draw!";
  std::string title = "Stalemate";
  this->openNewGameQuitDialogWithMessage(message, title);
}

void ChessWindow::openOpponentHasSurrenderedDialog() {
  PlayerID playerId = chessMediator.getOpponentTurnPlayerIdSignal().emit();
  std::string playerStr = playerId == PlayerID::PLAYER_WHITE ? "White" : "Black";
  std::string message =  playerStr + " wins!";
  std::string title = "Opponent Surrenders";
  this->openNewGameQuitDialogWithMessage(message, title);
}

void ChessWindow::openNewGameQuitDialogWithMessage(const std::string message, const std::string title) {
  auto dialog = Gtk::make_managed<Gtk::Window>();
  dialog->set_title(title);
  dialog->set_transient_for(*this);
  dialog->set_modal(true);
  dialog->set_default_size(200, 100);

  header_bar = Gtk::make_managed<Gtk::HeaderBar>();
  header_bar->set_show_title_buttons(false);
  header_bar->set_title_widget(*Gtk::make_managed<Gtk::Label>(title));

  dialog->set_titlebar(*header_bar);

  this->set_sensitive(false);

  auto content_area = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  content_area->set_margin(16);
  content_area->set_homogeneous(true);  // Distribute space evenly
  dialog->set_child(*content_area);

  auto label = Gtk::make_managed<Gtk::Label>(message);
  content_area->append(*label);

  auto button_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 8);
  button_box->set_halign(Gtk::Align::CENTER);  // Center the button box
  button_box->set_valign(Gtk::Align::CENTER);  // Vertically center the button box
  content_area->append(*button_box);

  auto new_game_button = Gtk::make_managed<Gtk::Button>("New Game");
  auto quit_button = Gtk::make_managed<Gtk::Button>("Quit");
  button_box->append(*new_game_button);
  button_box->append(*quit_button);
  new_game_button->signal_clicked().connect([dialog, this]() {
      this->set_sensitive(true);
      dialog->close();
      chessMediator.getNewGameSignal().emit();
  });

  quit_button->signal_clicked().connect([dialog, this]() {
      this->close();
  });

  dialog->present();
}

bool ChessWindow::on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state) {
  if (keyval == GDK_KEY_Escape) {
    chessMediator.getClearSelectedBoardSpaceUISignal().emit();
    chessMediator.getUpdateUiSignal().emit();
    return true;
  }

  return false;
}

void ChessWindow::onRequestDrawAction() {
  std::string title = "Request for Draw";
  std::string message = "Your opponent is requesting a draw!";
  auto dialog = Gtk::make_managed<Gtk::Window>();
  dialog->set_title(title);
  dialog->set_transient_for(*this);
  dialog->set_modal(true);
  dialog->set_default_size(200, 100);

  header_bar = Gtk::make_managed<Gtk::HeaderBar>();
  header_bar->set_show_title_buttons(false);
  header_bar->set_title_widget(*Gtk::make_managed<Gtk::Label>(title));

  dialog->set_titlebar(*header_bar);

  this->set_sensitive(false);

  auto content_area = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  content_area->set_margin(16);
  content_area->set_homogeneous(true);  // Distribute space evenly
  dialog->set_child(*content_area);

  auto label = Gtk::make_managed<Gtk::Label>(message);
  content_area->append(*label);
  auto button_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 8);
  button_box->set_halign(Gtk::Align::CENTER);  // Center the button box
  button_box->set_valign(Gtk::Align::CENTER);  // Vertically center the button box
  content_area->append(*button_box);

  auto accept_button = Gtk::make_managed<Gtk::Button>("Accept");
  auto reject_button = Gtk::make_managed<Gtk::Button>("Reject");
  button_box->append(*accept_button);
  button_box->append(*reject_button);

  accept_button->signal_clicked().connect([dialog, this]() {
      dialog->close();
      std::string reason = "The request for a draw has been accepted";
      this->onDrawConditionTrigger(reason);
  });

  reject_button->signal_clicked().connect([dialog, this]() {
      this->set_sensitive(true);
      dialog->close();
  });

  dialog->present();
}

void ChessWindow::onRequestForfeitAction() {
  std::string title = "";
  PlayerID playerId = chessMediator.getTurnPlayerIdSignal().emit();
  auto dialog = Gtk::make_managed<Gtk::Window>();
  dialog->set_title(title);
  dialog->set_transient_for(*this);
  dialog->set_modal(true);
  dialog->set_default_size(200, 100);

  header_bar = Gtk::make_managed<Gtk::HeaderBar>();
  header_bar->set_show_title_buttons(false);
  header_bar->set_title_widget(*Gtk::make_managed<Gtk::Label>(title));

  dialog->set_titlebar(*header_bar);

  this->set_sensitive(false);

  auto content_area = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  content_area->set_margin(16);
  content_area->set_homogeneous(true);  // Distribute space evenly
  dialog->set_child(*content_area);

  std::string message = "Would the following player like to surrender?";
  auto messageLabel = Gtk::make_managed<Gtk::Label>(message);
  content_area->append(*messageLabel);

  std::string playerIdStr = playerId == PlayerID::PLAYER_WHITE ? "White" : "Black";
  auto playerIdLabel = Gtk::make_managed<Gtk::Label>(playerIdStr);
  content_area->append(*playerIdLabel);

  auto button_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 8);
  button_box->set_halign(Gtk::Align::CENTER);  // Center the button box
  button_box->set_valign(Gtk::Align::CENTER);  // Vertically center the button box
  content_area->append(*button_box);

  auto yes_button = Gtk::make_managed<Gtk::Button>("Yes");
  auto no_button = Gtk::make_managed<Gtk::Button>("No");
  button_box->append(*yes_button);
  button_box->append(*no_button);

  yes_button->signal_clicked().connect([dialog, this]() {
      this->set_sensitive(true);
      dialog->close();
      openOpponentHasSurrenderedDialog();
  });

  no_button->signal_clicked().connect([dialog, this]() {
      dialog->close();
      this->set_sensitive(true);
  });

  dialog->signal_close_request().connect([dialog, this]() {
      dialog->close();
      this->set_sensitive(true);
      // @TODO: look at this line, it may cause an issue
      delete dialog;
      return true;
  }, false);

  dialog->present();
}

void ChessWindow::onThreefoldRepetitionDrawAction() {
  std::string reason = "Threefold Repetition Draw!";
  onDrawConditionTrigger(reason);
}

void ChessWindow::onDrawConditionTrigger(std::string reason) {
  std::string title = "Draw!";
  std::string message = reason;
  auto dialog = Gtk::make_managed<Gtk::Window>();
  dialog->set_title(title);
  dialog->set_transient_for(*this);
  dialog->set_modal(true);
  dialog->set_default_size(200, 100);

  header_bar = Gtk::make_managed<Gtk::HeaderBar>();
  header_bar->set_show_title_buttons(false);
  header_bar->set_title_widget(*Gtk::make_managed<Gtk::Label>(title));

  dialog->set_titlebar(*header_bar);

  this->set_sensitive(false);

  auto content_area = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
  content_area->set_margin(16);
  content_area->set_homogeneous(true);  // Distribute space evenly
  dialog->set_child(*content_area);

  auto label = Gtk::make_managed<Gtk::Label>(message);
  content_area->append(*label);

  auto button_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 8);
  button_box->set_halign(Gtk::Align::CENTER);  // Center the button box
  button_box->set_valign(Gtk::Align::CENTER);  // Vertically center the button box
  content_area->append(*button_box);

  auto new_game_button = Gtk::make_managed<Gtk::Button>("New Game");
  auto quit_button = Gtk::make_managed<Gtk::Button>("Quit");
  button_box->append(*new_game_button);
  button_box->append(*quit_button);

  new_game_button->signal_clicked().connect([dialog, this]() {
      this->set_sensitive(true);
      dialog->close();
      chessMediator.getNewGameSignal().emit();
  });

  quit_button->signal_clicked().connect([dialog, this]() {
      this->close();
  });

  dialog->present();
}
