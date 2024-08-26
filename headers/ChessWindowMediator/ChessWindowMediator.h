//
// Created by Ismael Cuevas on 8/11/24.
//

#ifndef CHESS_CHESSWINDOWMEDIATOR_H
#define CHESS_CHESSWINDOWMEDIATOR_H
#include <glibmm/signalproxy.h>
#include <sigc++/signal.h>
#include <glibmm/dispatcher.h>

class ChessWindowMediator {
public:
    sigc::signal<void()> getOpenSaveDialogSignal();
    sigc::signal<void()> getOpenFileDialogSignal();
    sigc::signal<void(std::string)> getAfterFileLoadedSignal();
    sigc::signal<void()> getUpdateUiSignal();
    sigc::signal<void()> getOnUndoButtonClicked();
    sigc::signal<void(bool)> getUpdateUndoButtonUiSignal();
    sigc::signal<void()> getUpdateLabelSignal();
private:
    sigc::signal<void()> openSaveDialog;
    sigc::signal<void()> openFileDialog;
    sigc::signal<void(std::string)> afterFileLoaded;
    sigc::signal<void()> updateUi;
    sigc::signal<void()> onUndoButtonPressed;
    sigc::signal<void(bool)> updateUndoButtonUi;
    sigc::signal<void()> updateLabel;
};


#endif //CHESS_CHESSWINDOWMEDIATOR_H
