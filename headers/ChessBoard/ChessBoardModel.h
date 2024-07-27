//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSBOARDMODEL_H
#define CHESS_CHESSBOARDMODEL_H

#include <iostream>
#include <vector>
#include <filesystem>
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
#include "gtkmm.h"
#include "../ChessImagesInfo/ChessImagesInfo.h"
#include <glibmm/signalproxy.h>
#include <sigc++/signal.h>

class ChessBoardModel : public Gtk::DrawingArea {
public:
    ChessBoardModel();
    void initBoard();
    int getBoardSize();
    ChessPiece* getChessPiecePtr(int row, int col);
    BoardSpace* getBoardSpacePtr(int row, int col);
    void assignChessPieceToBoardSpaceIndex(ChessPiece* sourceChessPiecePtr, int row, int col);
    void setBoardSpaceAtIndex(ChessPiece* chessPiecePtr, int row, int col);
    ChessPiece* initChessPiece(std::string pieceEncoding);
    ChessPiece* initChessPiece(PieceType pieceType, PlayerID playerId);
    std::vector<std::vector<std::string>> getBoardConfig();
    PieceType parsePieceType(std::string pieceEncoding);
    PlayerID parsePlayerId(std::string pieceEncoding);
    Glib::RefPtr<Gdk::Pixbuf> getPieceImageContent(ChessPiece *chessPiece);
    bool isValidEncoding(std::vector<std::vector<std::string>> chessBoard);
    void setSelectedBoardSpacePtr(BoardSpace* boardSpacePtr);
    BoardSpace* getSelectedBoardSpacePtr();
    bool hasSelectedBoardSpacePtr();
    void clearSelectedBoardSpacePtr();
    bool isEmptyPiece(ChessPiece* chessPiecePtr);
    bool isSelectedBoardSpacePtr(int row, int col);
    bool isBoardSpaceOccupied(int row, int col);
    bool isTurnPlayersChessPiece(ChessPiece* chessPiece, int targetRow, int targetCol);
    void clearChessPiecePtr(ChessPiece* chessPiecePtr);
    void clearSelectedBoardSpace();
    void clearBoard();
    PlayerID getTurnPlayerId();
    void updateTurnPlayerId();
    bool isTurnPlayer(ChessPiece* chessPiecePtr);
    bool isTurnPlayer(PlayerID playerId);
private:
    const int BOARD_SIZE = 8;
    int currentTurn = 1;
    std::vector<std::vector<BoardSpace*>> board;
    ChessImagesInfo chessImagesInfo{};
    BoardSpace* selectedBoardSpacePtr;
    PlayerID turnPlayerId{PlayerID::PLAYER_LIGHT};
};


#endif //CHESS_CHESSBOARDMODEL_H
