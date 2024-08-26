//
// Created by Ismael Cuevas on 8/11/24.
//

#include "ChessWindowMediator/ChessWindowMediator.h"

sigc::signal<void(std::string)> ChessWindowMediator::getAfterFileLoadedSignal() {
  return afterFileLoaded;
}

sigc::signal<void()> ChessWindowMediator::getOpenFileDialogSignal() {
  return openFileDialog;
}

sigc::signal<void()> ChessWindowMediator::getOpenSaveDialogSignal() {
  return openSaveDialog;
}

sigc::signal<void()> ChessWindowMediator::getUpdateUiSignal() {
  return updateUi;
}

sigc::signal<void()> ChessWindowMediator::getOnUndoButtonClicked() {
  return onUndoButtonPressed;
}

sigc::signal<void(bool)> ChessWindowMediator::getUpdateUndoButtonUiSignal() {
  return updateUndoButtonUi;
}

sigc::signal<void()> ChessWindowMediator::getUpdateLabelSignal() {
  return updateLabel;
}

