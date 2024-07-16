//
// Created by Ismael Cuevas on 7/15/24.
//

#ifndef CHESS_CHESSMOVEMENTUTILS_H
#define CHESS_CHESSMOVEMENTUTILS_H


#include <vector>
#include "BoardSpace.h"
#include "./ChessPieces/EmptyPiece.h"
#include "Game.h"
#include "ChessPieces/Pawn.h"
#include <QLabel>
#include <QGraphicsView>
#include "../views/PawnPromotionView/PawnPromotionView.h"
#include "../views/MainChessView/ChessView.h"

// TODO: Check if name could be changed
class ChessMovementUtils {
private:
    inline static int currentTurn = 1;
    inline static std::vector<BoardSpace*> boardSpaceList;
    // inline static QLabel* turnLabelPtr;
    inline static Game* gamePtr;
    // inline static ChessView* chessViewPtr;
    static void setBoardSpaceBackground(BoardSpace* boardSpace);
    static void incrementTurn();

    static bool isTurnPlayerPiece(ChessPiece* chessPiece);
    static void tryMovingChessPiece();
    static void moveChessPiece();
    static const bool canMove(BoardSpace* firstBoardSpace, BoardSpace* secondBoardSpace);

    static void handleCastling(Coordinates coordinates);
    static void handleEnPassantCapture(BoardSpace* firstBoardSpace, BoardSpace* secondBoardSpace);
    static const int firstIndex = 0;
    static const int lastIndex = 7;
    static const int boardSize = 8;
public:
    // TODO: Consider refactoring the Set and Get APIs
    static void setChessPieceAtIndex(ChessPiece* chessPiece, int targetX, int targetY);
    static ChessPiece* getChessPieceAtIndex(int xIndex, int yIndex);
    static BoardSpace* getBoardSpaceAtIndex(int xIndex, int yIndex);
    static bool haveSamePlayerId(Coordinates coordinates);
    static void showHints(BoardSpace* boardSpace);
    static void hideHints();
    static void addBoardSpace(BoardSpace* boardSpace);
    static void setLabelPtr(QLabel* qLabel);
    static void setGamePtr(Game* gamePtr);
    static void setChessViewPtr(ChessView* chessViewPtr);
    // static ChessView* getChessViewPtr();
    static bool isBoardIndexOccupied(int targetX, int targetY);
    static int getCurrentTurn();
    static int getMovedTwoSpacesTurn(int targetX, int targetY);

    static void clearBoardSpaceList();

    static PlayerID getCurrentTurnPlayerId();
    static void afterPawnMoved();
    static void handlePawnPromotion(Coordinates coordinates);
    static bool isPawnEligibleForPromotion(ChessPiece *chessPiece, Coordinates coordinates);
    static int getFirstIndex();
    static int getLastIndex();
    static int getBoardSize();
};

#endif //CHESS_CHESSMOVEMENTUTILS_H
