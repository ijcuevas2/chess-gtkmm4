//
// Created by Ismael Cuevas on 7/28/24.
//

#ifndef CHESS_FENMODEL_H
#define CHESS_FENMODEL_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <deque>
#include "ChessBoard/ChessBoardModel.h"
#include "../../headers/ChessWindowMediator/ChessWindowMediator.h"

class FenModel {
public:
    FenModel(ChessBoardModel & chessBoardModel, ChessWindowMediator & chessWindowMediator);
    void saveBoardState();
    void saveStateToFile();
    void loadStateFromFile(std::string filePath);
private:
    ChessBoardModel & chessBoardModel;
    ChessWindowMediator & chessWindowMediator;
    int counter = 0;
    fs::path dirName;
    std::string encodeChessBoard();
    char getChessPieceEncoding(ChessPiece *chessPiecePtr);
    void clearCounter();
    std::string getCounterStr();
    std::deque<std::string> fenDeque;
    std::string getBoardState();
    std::string getTurnPlayerEncoding();
    void getLatestFenString();
    bool canCastle(int rookRow, int rookCol, int kingRow, int kingCol);
    bool canBlackQueenSideRookCastle();
    bool canBlackKingSideRookCastle();
    bool canWhiteQueenSideRookCastle();
    bool canWhiteKingSideRookCastle();
    bool createSaveDirectory();
    bool isChessSavesDirValid = false;
    std::string getCastlingAvailability();
    bool isRook(ChessPiece *chessPiecePtr);
    bool isKing(ChessPiece *chessPiecePtr);
    bool saveGame(std::string content);
    std::string generateGMTFilename();
};

#endif //CHESS_FENMODEL_H
