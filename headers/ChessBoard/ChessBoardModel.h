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
#include <type_traits>
#include <unordered_map>

class ChessBoardModel : public Gtk::DrawingArea {
public:
    ChessBoardModel(ChessMediator & chessMediator);
    void initBoard();
    void initBoardSpacePointers();
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
    void updateKingPosition(PlayerID playerId, int row, int col);
    void clearSelectedBoardSpace();
    void clearBoard();
    PlayerID getTurnPlayerId();
    void updateTurnPlayerId();
    bool isTurnPlayer(BoardSpace *boardSpacePtr);
    bool isTurnPlayer(ChessPiece *chessPiecePtr);
    bool isTurnPlayerHelper(PlayerID playerId);
    bool canOpponentsPiecesPutKingInCheck(PlayerID playerId, Point2DPair point2dPair);
    int getCurrentTurn();
    int getHalfMoveClock();
    void incrementHalfMoveClock();
    void resetHalfMoveClock();
    void showHintMarkers(BoardSpace *boardSpacePtr);
    void hideHintMarkers();
    bool isKingOccupyingSpace(Point2D point2D);
    PlayerID getOpponentPlayerId(PlayerID playerId);
    Point2D whiteKingCoordinates;
    Point2D blackKingCoordinates;
    Point2D getKingPoint2D(PlayerID playerId);
    void calculateOpponentKingIsInCheck(PlayerID playerId);
    void initChessBoardFromFenStateString(std::string fenStateStr);
    void initChessBoardFromBoardConfig(std::string boardConfigStr);
    void clearEnPassantSquare();
    void setEnPassantSquare(Point2D point2d);
    Point2DPair getPrevMoves();
    bool isPlayerIdKingInCheck(PlayerID playerId);
    bool getIsCheckmate(PlayerID playerId);
    // void initMovementTargets();
private:
    const static int BOARD_SIZE = 8;
    int currentTurn = 1;
    int halfMoveClock = 0;
    std::vector<Point2D> blackKingMovementTargets;
    std::vector<Point2D> whiteKingMovementTargets;
    Point2D enPassantSquare{-1, -1};
    Point2DPair prevMoves{-1, -1, -1, -1};
    BoardSpace* board[BOARD_SIZE][BOARD_SIZE];
    ChessImagesInfo chessImagesInfo{};
    ChessMediator & chessMediator;
    BoardSpace *selectedBoardSpacePtr = nullptr;
    PlayerID turnPlayerId{PlayerID::PLAYER_WHITE};
    void restoreCastlingState(std::string castlingStr);
    void restoreCastlingStateHelper(int row, int col);
    PlayerID getTurnPlayerFromStr(std::string turnPlayerId);
    ChessPiece *initChessPieceFromChar(char chessPieceChar);
    bool isPawnChessPiecePtr(ChessPiece* chessPiece);
    bool isKingChessPiecePtr(ChessPiece* chessPiece);
    bool isBishopChessPiecePtr(ChessPiece* chessPiece);
    bool isRookChessPiecePtr(ChessPiece* chessPiece);
    bool isQueenChessPiecePtr(ChessPiece* chessPiece);
    bool isKnightChessPiecePtr(ChessPiece* chessPiece);
    void updatePawnFirstTurn(ChessPiece* chessPiece, int row);
    bool isEnPassantSquare(Point2D point2d);
    Point2D getEnPassantCoordinates(Point2DPair point2dPair);
    void clearEnPassantCaptureSpace(Point2DPair point2dPair);
    bool isEnPassantCapture(Point2DPair point2dPair);
    void assignEmptySpaceToBoardSpaceIndex(int row, int col);
    Point2D getEnPassantSquare();
    void setPrevMovesFromStrings(std::string srcBoardSpace, std::string tgtBoardSpace);
    void setPrevMoves(Point2DPair point2dPair);
    King *getPlayerIdKing(PlayerID playerId);
    bool getIsValidKingSpace(PlayerID playerId, Point2D targetPoint);
    bool getRookCanCastle(Point2D point2d);
    void moveRookAfterCastle(Point2D point2d);
    PlayerID getOpponentTurnPlayerId();
    void initBoardWithCaptureInfo();
    bool containsPoint(const std::vector<Point2D> & points, const Point2D & target);
    bool checkIfKnightBlocksKingSpace(PlayerID playerId, Point2D targetPoint);
    bool checkIfPawnBlocksKingSpace(PlayerID playerId, Point2D targetPoint);
    bool checkIfOpponentKingBlocksKingSpace(PlayerID playerId, Point2D targetPoint);
    bool checkIfDiagonalCaptureBlocksKingSpace(PlayerID playerId, Point2D targetPoint);
    bool checkIfOrthogonalCaptureBlocksKingSpace(PlayerID playerId, Point2D targetPoint);
    std::vector<Point2D> getPointsByPlayerId(PlayerID playerId);
    std::vector<Point2D> getPointsWithPiecesThatDiagonalCapture(PlayerID playerId, Point2D targetPoint);
    std::vector<Point2D> getPointsWithPiecesThatOrthogonalCapture(PlayerID playerId, Point2D targetPoint);
    std::vector<Point2D> getPawnPointsThatCanCapture(PlayerID playerId, Point2D targetPoint);
    std::vector<Point2D> getKnightPointsThatCanCapture(PlayerID playerId, Point2D targetPoint);
    std::optional<std::vector<Point2D>> getCanBlockCheckPointsArr(PlayerID playerId, Point2D point2d);
    template<typename T, typename... Args>
    std::optional<std::vector<T>> hasOnlyOneArrWithElements(const std::vector<T> & first, const Args&... args) {
      static_assert((std::is_same_v<std::vector<T>, Args> && ...), "All arguments must be vectors of the same type");
      const std::vector<T>* nonEmptyVector = nullptr;
      int count = 0;

      auto checkVector = [&](const auto & vec) {
        if (vec.size() > 0) {
          count++;
          nonEmptyVector = &vec;
        }
      };

      checkVector(first);
      (checkVector(args), ...);

      if (count == 1 && nonEmptyVector != nullptr) {
        return *nonEmptyVector;
      }

      return std::nullopt;
    }

    bool getCanBlockCheck(PlayerID playerId, Point2D targetPoint);
    std::vector<Point2D> getDiagonalSpaces(Point2D point2d);
    std::vector<Point2D> getOrthogonalSpaces(Point2D point2d);
    void updateKingMovementTargets(PlayerID playerId);
    std::vector<Point2D> getKingMovementTargets(PlayerID playerId);
    std::vector<Point2D> getCommonElements(const std::vector<Point2D> & vec1, const std::vector<Point2D> & vec2);
};


#endif //CHESS_CHESSBOARDMODEL_H
