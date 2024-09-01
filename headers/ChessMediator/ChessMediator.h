//
// Created by Ismael Cuevas on 9/1/24.
//

#ifndef CHESS_CHESSMEDIATOR_H
#define CHESS_CHESSMEDIATOR_H
#include <glibmm/signalproxy.h>
#include <sigc++/signal.h>
#include <glibmm/dispatcher.h>
#include "Point2DPair/Point2DPair.h"
#include "Point2D/Point2D.h"
#include "../enum/Player.h"

class ChessMediator {
public:
    sigc::signal<void()> getOpenSaveDialogSignal();
    sigc::signal<void()> getOpenFileDialogSignal();
    sigc::signal<void(std::string)> getAfterFileLoadedSignal();
    sigc::signal<void()> getUpdateUiSignal();
    sigc::signal<void()> getOnUndoButtonClicked();
    sigc::signal<void(bool)> getUpdateUndoButtonUiSignal();
    sigc::signal<void()> getUpdateLabelSignal();
    sigc::signal<int()> getCurrentTurnSignal();
    sigc::signal<bool(int, int)> getIsBoardIndexOccupiedSignal();
    sigc::signal<bool(PlayerID)> getIsTurnPlayerSignal();
    sigc::signal<bool(PlayerID, int, int)> getIsTurnPlayersChessPieceSignal();
    sigc::signal<void(PlayerID, int, int)> getUpdateKingPositionSignal();
    sigc::signal<bool(Point2D)> getIsKingOccupyingSpaceSignal();
    sigc::signal<bool(PlayerID, Point2DPair)> getCanOpponentsPiecesPutKingInCheckSignal();
    sigc::signal<void(Point2D)> getSetEnPassantSquareSignal();
    sigc::signal<bool(Point2D)> getIsEnPassantSquareSignal();
private:
    sigc::signal<void()> openSaveDialog;
    sigc::signal<void()> openFileDialog;
    sigc::signal<void(std::string)> afterFileLoaded;
    sigc::signal<void()> updateUi;
    sigc::signal<void()> onUndoButtonPressed;
    sigc::signal<void(bool)> updateUndoButtonUi;
    sigc::signal<void()> updateLabel;
    sigc::signal<int()> getCurrentTurn;
    sigc::signal<bool(int, int)> isBoardIndexOccupied;
    sigc::signal<bool(PlayerID)> isTurnPlayer;
    sigc::signal<bool(PlayerID, int, int)> isTurnPlayersChessPiece;
    sigc::signal<void(PlayerID, int, int)> updateKingPosition;
    sigc::signal<bool(Point2D)> isKingOccupyingSpace;
    sigc::signal<bool(PlayerID, Point2DPair)> canOpponentsPiecesPutKingInCheck;
    sigc::signal<void(Point2D)> setEnPassantSquare;
    sigc::signal<bool(Point2D)> isEnPassantSquare;
};


#endif //CHESS_CHESSMEDIATOR_H