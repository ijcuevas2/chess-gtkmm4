//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSBOARDMODEL_H
#define CHESS_CHESSBOARDMODEL_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <filesystem>
#include <format>
#include <print>
#include <map>
#include "../ChessPieces/ChessPiece.h"
#include "../BoardSpace/BoardSpace.h"
#include "../../headers/ChessPieces/Rook.h"
#include "../../headers/ChessPieces/Knight.h"
#include "../../headers/ChessPieces/Bishop.h"
#include "../../headers/ChessPieces/Queen.h"
#include "../../headers/ChessPieces/King.h"
#include "../../headers/ChessPieces/Pawn.h"
#include "../../headers/ChessPieces/EmptyPiece.h"
#include "Point2D/Point2D.h"
#include "gtkmm.h"
#include "../ChessImagesInfo/ChessImagesInfo.h"
#include <glibmm/signalproxy.h>
#include <sigc++/signal.h>
#include <cctype>
#include "../../headers/Utils/MathUtils.h"
#include "ChessMediator/ChessMediator.h"

class ChessBoardModel : public Gtk::DrawingArea {
public:
    ChessBoardModel(ChessMediator & chessMediator);
    void initBoard();
    int getBoardSize();
    ChessPiece *getChessPiecePtr(int row, int col);
    BoardSpace *getBoardSpacePtr(int row, int col);
    void assignChessPieceToBoardSpaceIndex(ChessPiece *sourceChessPiecePtr, int row, int col);
    void setNewBoardSpaceAtIndex(ChessPiece *chessPiecePtr, int row, int col);
    ChessPiece *initEmptyPiece();
    Glib::RefPtr<Gdk::Pixbuf> getPieceImageContent(ChessPiece *chessPiece);
    bool isValidEncoding(std::vector<std::vector<std::string>> & chessBoard);
    void setSelectedBoardSpacePtr(BoardSpace *boardSpacePtr);
    BoardSpace *getSelectedBoardSpacePtr();
    bool hasSelectedBoardSpacePtr();
    void clearSelectedBoardSpacePtr();
    bool isEmptyPiece(ChessPiece *chessPiecePtr);
    bool isSelectedBoardSpacePtr(BoardSpace *boardSpacePtr);
    bool isSelectedBoardSpacePtr(int row, int col);
    bool isBoardSpaceOccupied(int row, int col);
    bool isTurnPlayersChessPiece(ChessPiece *chessPiece, int targetRow, int targetCol);
    bool isTurnPlayersChessPieceHelper(PlayerID playerId, int targetRow, int targetCol);
    bool isKingChessPiecePtr(ChessPiece *chessPiecePtr);
    void clearChessPiecePtr(ChessPiece *chessPiecePtr);
    void updateKingPosition(PlayerID playerId, int row, int col);
    void clearSelectedBoardSpace();
    void clearBoard();
    PlayerID getTurnPlayerId();
    void updateTurnPlayerId();
    bool isTurnPlayer(BoardSpace *boardSpacePtr);
    bool isTurnPlayer(ChessPiece *chessPiecePtr);
    bool isTurnPlayerHelper(PlayerID playerId);
    bool canOpponentsPiecesPutKingInCheck(PlayerID playerId, Point2DPair point2DPair);
    int getCurrentTurn();
    int getHalfMoveClock();
    void incrementHalfMoveClock();
    void resetHalfMoveClock();
    void showHintMarkers(BoardSpace *boardSpacePtr);
    void hideHintMarkers();
    bool isKingOccupyingSpace(Point2D point2D);
    PlayerID getOppositePlayerId(PlayerID playerId);
    Point2D whiteKingCoordinates;
    Point2D blackKingCoordinates;
    Point2D getKingCoordinates(PlayerID playerId);
    void calculateKingIsInCheck(PlayerID playerId);
    void initChessBoardFromFenStateString(std::string fenStateStr);
    void initChessBoardFromBoardConfig(std::string boardConfigStr);
    void clearEnPassantSquare();
    void setEnPassantSquare(Point2D point2D);
private:
    const int BOARD_SIZE = 8;
    int currentTurn = 1;
    int halfMoveClock = 0;
    Point2D enPassantSquare{-1, -1};
    int whitePawnCaptureRow = 4;
    int blackPawnCaptureRow = 3;
    std::vector<std::vector<BoardSpace *>> board;
    ChessImagesInfo chessImagesInfo{};
    ChessMediator & chessMediator;
    BoardSpace *selectedBoardSpacePtr;
    PlayerID turnPlayerId{PlayerID::PLAYER_WHITE};
    ChessPiece* initChessPieceFromStr(std::string chessPieceStr);
    void restoreCastlingInfo(std::string castlingStr);
    void restoreCastlingInfoHelper(int row, int col);
    PlayerID getTurnPlayerFromStr(std::string turnPlayerId);
    ChessPiece *initChessPieceFromChar(char chessPieceChar);
    int getCounterValue(int col, int counter);
    void updateUndoButtonStatus();
    bool isPawn(Point2D pair);
    bool IsEnPassantSquare(Point2D pair);
};


#endif //CHESS_CHESSBOARDMODEL_H
