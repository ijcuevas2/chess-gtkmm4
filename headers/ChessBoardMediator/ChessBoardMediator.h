//
// Created by Ismael Cuevas on 7/27/24.
//

#ifndef CHESS_CHESSBOARDMEDIATOR_H
#define CHESS_CHESSBOARDMEDIATOR_H
#include <gtkmm.h>
#include "Coordinates/Coordinates.h"
#include "../enum/Player.h"

class ChessBoardMediator {
public:
    sigc::signal<int()> getCurrentTurnSignal();
    sigc::signal<bool(int, int)> getIsBoardIndexOccupiedSignal();
    sigc::signal<int(int, int)> getMovedTwoSpacesTurnSignal();
    sigc::signal<bool(PlayerID)> getIsTurnPlayerSignal();
    sigc::signal<bool(PlayerID, int, int)> getIsTurnPlayersChessPieceSignal();
private:
    sigc::signal<int()> getCurrentTurn;
    sigc::signal<bool(int, int)> isBoardIndexOccupied;
    sigc::signal<int(int, int)> getMovedTwoSpacesTurn;
    sigc::signal<bool(PlayerID)> isTurnPlayer;
    sigc::signal<bool(PlayerID, int, int)> isTurnPlayersChessPiece;
};


#endif //CHESS_CHESSBOARDMEDIATOR_H