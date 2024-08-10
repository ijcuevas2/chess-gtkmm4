//
// Created by Ismael Cuevas on 7/27/24.
//

#ifndef CHESS_CHESSBOARDMEDIATOR_H
#define CHESS_CHESSBOARDMEDIATOR_H
#include <gtkmm.h>
#include "Point2DPair/Point2DPair.h"
#include "../enum/Player.h"

class ChessBoardMediator {
public:
    sigc::signal<int()> getCurrentTurnSignal();
    sigc::signal<bool(int, int)> getIsBoardIndexOccupiedSignal();
    sigc::signal<int(int, int)> getMovedTwoSpacesTurnSignal();
    sigc::signal<bool(PlayerID)> getIsTurnPlayerSignal();
    sigc::signal<bool(PlayerID, int, int)> getIsTurnPlayersChessPieceSignal();
    sigc::signal<void(PlayerID, int, int)> getUpdateKingPositionSignal();
    sigc::signal<bool(PlayerID, Point2DPair)> getCanOpponentsPiecesPutKingInCheckSignal();
private:
    sigc::signal<int()> getCurrentTurn;
    sigc::signal<bool(int, int)> isBoardIndexOccupied;
    sigc::signal<int(int, int)> getMovedTwoSpacesTurn;
    sigc::signal<bool(PlayerID)> isTurnPlayer;
    sigc::signal<bool(PlayerID, int, int)> isTurnPlayersChessPiece;
    sigc::signal<void(PlayerID, int, int)> updateKingPosition;
    sigc::signal<bool(PlayerID, Point2DPair)> canOpponentsPiecesPutKingInCheck;
};


#endif //CHESS_CHESSBOARDMEDIATOR_H
