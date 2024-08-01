//
// Created by Ismael Cuevas on 7/28/24.
//

#ifndef CHESS_FENMODEL_H
#define CHESS_FENMODEL_H

#include <iostream>
#include <cctype>
#include <stack>
#include "ChessBoard/ChessBoardModel.h"

class FenModel {
public:
    FenModel(ChessBoardModel & chessBoardModel);
    void saveBoardState();
private:
    ChessBoardModel & chessBoardModel;
    int counter = 0;
    std::string encodeChessBoard();
    char getChessPieceEncoding(ChessPiece* chessPiecePtr);
    void clearCounter();
    std::string getCounterStr();
    std::stack<std::string> fenBoardStateStack;
    std::string getBoardState();
    std::string getTurnPlayerEncoding();
    bool canCastle(int rookRow, int rookCol, int kingRow, int kingCol);
    bool canBlackQueenSideRookCastle();
    bool canBlackKingSideRookCastle();
    bool canWhiteQueenSideRookCastle();
    bool canWhiteKingSideRookCastle();
    std::string getCastlingAvailability();
    bool isRook(ChessPiece* chessPiecePtr);
    bool isKing(ChessPiece* chessPiecePtr);
};

#endif //CHESS_FENMODEL_H
