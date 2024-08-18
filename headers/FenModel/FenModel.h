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
    void loadChessBoardFromFenState(std::string fenStateStr);
    char getChessPieceEncoding(ChessPiece *chessPiecePtr);
    void clearCounter();
    std::string getCounterStr();
    std::deque<std::string> fenDeque;
    std::string getBoardState();
    std::string getTurnPlayerEncoding();
    void getLatestFenString();
    bool canCastle(int rookRow, int rookCol, int kingRow, int kingCol);
    std::string canBlackQueenSideRookCastle();
    std::string canBlackKingSideRookCastle();
    std::string canWhiteQueenSideRookCastle();
    std::string canWhiteKingSideRookCastle();
    bool createSaveDirectory();
    bool isChessSavesDirValid = false;
    std::string getCastlingAvailability();
    bool isRook(ChessPiece *chessPiecePtr);
    bool isKing(ChessPiece *chessPiecePtr);
    bool saveGame(std::string content);
    std::string generateGMTFilename();
    std::string getHalfMoveClock();
    std::string getCurrentTurn();
    std::string getEnpassantSquare();
    std::string defaultFenStateStr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w AHah - 0 1";
    bool validateFenState(std::string fenState);
    void initChessBoardFromBoardConfig(std::string boardConfigStr);
};

#endif //CHESS_FENMODEL_H
