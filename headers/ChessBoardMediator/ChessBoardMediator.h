//
// Created by Ismael Cuevas on 7/27/24.
//

#ifndef CHESS_CHESSBOARDMEDIATOR_H
#define CHESS_CHESSBOARDMEDIATOR_H

#include <gtkmm.h>
#include "Point2DPair/Point2DPair.h"
#include "Point2D/Point2D.h"
#include "../enum/Player.h"

class ChessBoardMediator {
public:
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


#endif //CHESS_CHESSBOARDMEDIATOR_H
