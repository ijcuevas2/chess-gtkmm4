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
    sigc::signal<void()> getClearSelectedBoardSpaceUISignal();
    sigc::signal<Point2D(Point2DPair)> getEnPassantCoordinatesSignal();
    sigc::signal<void(Point2DPair)> getClearEnPassantCaptureSpaceSignal();
    sigc::signal<void()> getClearEnPassantSquareSignal();
    sigc::signal<void(std::string)> getSaveStateToFileSignal();
    sigc::signal<Point2D()> getEnPassantSquareSignal();
    sigc::signal<Point2D(std::string)> getPointFromAlgebraicNotationSignal();
    sigc::signal<Point2DPair(std::string, std::string)> getSetPrevMoveFromStringSignal();
    sigc::signal<void(Point2DPair)> getSetPrevMoveSignal();
    sigc::signal<bool(PlayerID)> getIsKingInCheckSignal();
    sigc::signal<bool(PlayerID, Point2D)> getIsKingValidPathSignal();
    sigc::signal<PlayerID()> getTurnPlayerIdSignal();
    sigc::signal<bool(Point2D)> getRookCanCastleSignal();
    sigc::signal<void(Point2D)> getMoveRookAfterCastleSignal();
    sigc::signal<void()> getOpenCheckmateDialogSignal();
    sigc::signal<PlayerID()> getOpponentTurnPlayerIdSignal();
    sigc::signal<void()> getNewGameSignal();
    sigc::signal<void()> getInitBoardWithCaptureInfoSignal();
    sigc::signal<void()> getClearBoardSignal();
    sigc::signal<std::optional<std::vector<Point2D>>(PlayerID playerId, Point2D point2d)> getBlockingCheckArrSignal();
    sigc::signal<Point2D(PlayerID)> getKingCoordinatesSignal();
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
    sigc::signal<void()> clearSelectedBoardSpaceUI;
    sigc::signal<Point2D(Point2DPair)> getEnPassantCoordinates;
    sigc::signal<void(Point2DPair)> clearEnPassantCaptureSpace;
    sigc::signal<void()> clearEnPassantSquare;
    sigc::signal<void(std::string)> saveStateToFile;
    sigc::signal<Point2D()> getEnPassantSquare;
    sigc::signal<Point2D(std::string)> getPointFromAlgebraicNotation;
    sigc::signal<Point2DPair(std::string, std::string)> setPrevMoveFromString;
    sigc::signal<void(Point2DPair)> getSetPrevMove;
    sigc::signal<bool(PlayerID)> isKingInCheck;
    sigc::signal<bool(PlayerID, Point2D)> isKingValidPath;
    sigc::signal<PlayerID()> turnPlayerId;
    sigc::signal<bool(Point2D)> getRookCanCastle;
    sigc::signal<void(Point2D)> moveRookAfterCastle;
    sigc::signal<void()> openCheckmateDialog;
    sigc::signal<PlayerID()> opponentPlayerId;
    sigc::signal<void()> newGame;
    sigc::signal<void()> initBoardWithCaptureInfo;
    sigc::signal<void()> clearBoard;
    sigc::signal<std::optional<std::vector<Point2D>>(PlayerID playerId, Point2D point2d)> getBlockingCheckArr;
    sigc::signal<Point2D(PlayerID)> getKingCoordinates;
};


#endif //CHESS_CHESSMEDIATOR_H
