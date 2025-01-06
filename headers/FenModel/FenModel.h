//
// Created by Ismael Cuevas on 7/28/24.
//

#ifndef CHESS_FENMODEL_H
#define CHESS_FENMODEL_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <deque>
#include <stdexcept>
#include "../../headers/Utils/FileUtils.h"
#include "ChessBoard/ChessBoardModel.h"
#include "ChessMediator/ChessMediator.h"

class FenModel {
public:
    FenModel(ChessBoardModel & chessBoardModel, ChessMediator & chessMediator);
    void saveBoardState();
    void saveStateToFile(std::string filePath);
    void loadGame(std::string filePath);
    void loadGameFromPath();
    bool getIsThreeFoldRepetitionDraw();
private:
    ChessBoardModel & chessBoardModel;
    ChessMediator & chessMediator;
    std::unordered_map<std::string, int> fenStateCountMap;
    int counter = 0;
    fs::path dirName;
    std::string encodeChessBoard();
    char getChessPieceEncoding(ChessPiece *chessPiecePtr);
    void clearCounter();
    std::string getCounterStr();
    std::deque<std::string> fenDeque;
    std::string getBoardState();
    std::string getTurnPlayerEncoding();
    void updateBoardFromLatestFenString();
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
    bool saveGame(std::string content, std::string inputFilePath);
    std::string getHalfMoveClock();
    std::string getCurrentTurn();
    std::string getEnpassantSquare();
    bool validateFenState(std::string fenState);
    void initChessBoardFromBoardConfig(std::string boardConfigStr);
    bool calculateUndoButtonEnabled();
    void afterUndoButtonPressed();
    std::string getLatestFenString();
    bool hasFenStateStored();
    std::string toAlgebraicNotation(int row, int col);
    Point2D fromAlgebraicNotation(std::string algebraicNotation);
    Point2DPair getPrevMoveHints(std::string srcPoint2dEncoding, std::string tgtPoint2dEncoding);
    std::string getLastPieceMovedEncoding();
    std::string getOrigFenState(std::string fenState);
    void updateFenStateCountMap(std::string chessBoardEncoding);
};

#endif //CHESS_FENMODEL_H
