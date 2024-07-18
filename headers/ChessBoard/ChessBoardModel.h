//
// Created by Ismael Cuevas on 7/16/24.
//

#ifndef CHESS_CHESSBOARDMODEL_H
#define CHESS_CHESSBOARDMODEL_H
#import <iostream>
#import <vector>
#include "../ChessPieces/ChessPiece.h"
#include "../BoardSpace/BoardSpace.h"

class ChessBoardModel {
public:
    ChessBoardModel();
    void initBoard();
    int getBoardSize();
    ChessPiece* getChessPiece(int row, int col);
    BoardSpace* getBoardSpace(int row, int col);
    void setBoardSpaceAtIndex(ChessPiece* chessPiece, int row, int col);

    ChessPiece* initChessPiece(std::string pieceEncoding);
    std::vector<std::vector<std::string>> getBoardConfig();
    PieceType parsePieceType(std::string pieceEncoding);
    bool isValidEncoding(std::vector<std::vector<std::string>> chessBoard);
private:
    const int BOARD_SIZE = 8;
    std::vector<std::vector<BoardSpace*>> board;
};


#endif //CHESS_CHESSBOARDMODEL_H
