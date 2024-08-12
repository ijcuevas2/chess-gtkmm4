//
// Created by Ismael Cuevas on 8/11/24.
//

#include "ChessWindowMediator/ChessWindowMediator.h"

sigc::signal<void(std::string)> ChessWindowMediator::getAfterFileLoaded() {
  return afterFileLoaded;
}

sigc::signal<void()> ChessWindowMediator::getOpenFileDialogSignal() {
  return openFileDialog;
}
