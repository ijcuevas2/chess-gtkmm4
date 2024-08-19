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
    sigc::signal<void()> getOpenFileDialogSignal();
    sigc::signal<void(std::string)> getAfterFileLoaded();
    sigc::signal<void()> getUpdateUiSignal();
private:
    sigc::signal<void()> openFileDialog;
    sigc::signal<void(std::string)> afterFileLoaded;
    sigc::signal<void()> updateUi;
};


#endif //CHESS_CHESSWINDOWMEDIATOR_H
