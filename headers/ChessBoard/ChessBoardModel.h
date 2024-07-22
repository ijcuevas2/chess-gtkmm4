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

class ChessBoardModel : public Gtk::DrawingArea {
public:
    ChessBoardModel();
    void initBoard();
    int getBoardSize();
    ChessPiece *getChessPiece(int row, int col);
    BoardSpace *getBoardSpace(int row, int col);
    void setBoardSpaceAtIndex(ChessPiece *chessPiece, int row, int col);
    ChessPiece *initChessPiece(std::string pieceEncoding);
    std::vector<std::vector<std::string>> getBoardConfig();
    PieceType parsePieceType(std::string pieceEncoding);
    PlayerID parsePlayerId(std::string pieceEncoding);
    Glib::RefPtr<Gdk::Pixbuf> getPieceImageContent(ChessPiece *chessPiece);
    bool isValidEncoding(std::vector<std::vector<std::string>> chessBoard);
private:
    const int BOARD_SIZE = 8;
    std::vector<std::vector<BoardSpace*>> board;
    ChessImagesInfo chessImagesInfo{};
};


#endif //CHESS_CHESSBOARDMODEL_H
