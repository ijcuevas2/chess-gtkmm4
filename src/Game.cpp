//
// Created by Ismael Cuevas on 7/15/24.
//

#include "../headers/Game.h"
#include "../headers/ChessPieces/Rook.h"
#include "../headers/ChessPieces/Knight.h"
#include "../headers/ChessPieces/Bishop.h"
#include "../headers/ChessPieces/Queen.h"
#include "../headers/ChessPieces/King.h"
#include "../headers/ChessPieces/Pawn.h"
#include "../headers/ChessPieces/EmptyPiece.h"

Game::Game() {
  for (int i = 0; i < boardSize; ++i) {
    this->board.push_back(std::vector<BoardSpace*>(8));
  }

  initializeBoard();
}

Game::~Game() {
  for (std::vector<BoardSpace*> vec : this->board) {
    for (BoardSpace* pBoardSpace : vec) {
      delete pBoardSpace;
    }

    vec.clear();
  }

  this->board.clear();
}

ChessPiece* Game::getChessPieceAtBoardIndex(int xIndex, int yIndex) {
  if (xIndex < 0 || xIndex > 7 || yIndex < 0 || yIndex > 7) {
    return NULL;
  }

  if ((!board.empty()) && (!board[yIndex].empty()) && board[yIndex][xIndex] != NULL) {
    return this->board[yIndex][xIndex]->getChessPiece();
  }

  return NULL;
}

std::vector<std::vector<BoardSpace*>> Game::getBoard() {
  return this->board;
}

int Game::getBoardSize() {
  return this->boardSize;
}

// TODO: ADD NULL CHECKS FOR INDICES
void Game::setChessPieceAtBoardIndex(ChessPiece* chessPiece, int xIndex, int yIndex) {
  if (xIndex < 0 || xIndex > 7 || yIndex < 0 || yIndex > 7) {
    return;
  }

  BoardSpace* boardSpace = this->board[yIndex][xIndex];
  if (boardSpace != NULL) {
    ChessPiece* currentChessPiece = boardSpace->getChessPiece();
    if (currentChessPiece != NULL) {
      delete currentChessPiece;
    }

    boardSpace->setChessPiece(chessPiece);
  }
}

BoardSpace* Game::getBoardSpaceAtIndex(int xIndex, int yIndex) {
  int boardSize = getBoardSize();
  if (xIndex < boardSize && yIndex < boardSize) {
    return board[yIndex][xIndex];
  }

  return NULL;
}

void Game::setBoardSpaceAtIndex(ChessPiece* chessPiece, int xIndex, int yIndex) {
  BoardSpace* boardSpace = new BoardSpace(chessPiece, xIndex, yIndex);
  this->board[yIndex][xIndex] = boardSpace;
}

bool Game::isValidEncoding(std::vector<std::vector<std::string>> chessBoard) {
  const int EXPECTED_NUM_ROWS = 8;
  const int EXPECTED_NUM_SPACES = 8;

  if (chessBoard.size() != EXPECTED_NUM_ROWS) {
    return false;
  }

  for (std::vector<std::string> & row : chessBoard) {
    if (row.size() != EXPECTED_NUM_SPACES) {
      return false;
    }

    for (std::string & pieceEncoding : row) {
      if (pieceEncoding.size() != 2) {
        return false;
      }
    }
  }

  return true;
}

PlayerID Game::parsePlayerId(std::string pieceEncoding) {
  // TODO: IMPLEMENT TRY CATCH
  // TODO: CONSIDER BUGS WITH TYPE COERCION
  const char firstChar = pieceEncoding[0];
  switch (firstChar) {
    case 'D':
      return PlayerID::PLAYER_DARK;
      break;
    case 'L':
      return PlayerID::PLAYER_LIGHT;
      break;
    case 'E':
      return PlayerID::NONE;
      break;
    default:
      return PlayerID::NONE;
      break;
  }
}

PieceType Game::parsePieceType(std::string pieceEncoding) {
  const char secondChar = pieceEncoding[1];
  switch (secondChar) {
    case 'R':
      return PieceType::ROOK;
      break;
    case 'N':
      return PieceType::KNIGHT;
      break;
    case 'B':
      return PieceType::BISHOP;
      break;
    case 'K':
      return PieceType::KING;
      break;
    case 'Q':
      return PieceType::QUEEN;
      break;
    case 'P':
      return PieceType::PAWN;
      break;
    case 'E':
      return PieceType::EMPTY_PIECE;
      break;
    default:
      return PieceType::EMPTY_PIECE;
      break;
  }
}

ChessPiece* Game::initChessPiece(std::string pieceEncoding) {
  PieceType pieceType = parsePieceType(pieceEncoding);
  PlayerID playerId = parsePlayerId(pieceEncoding);
  ChessPiece* piece = NULL;

  switch (pieceType) {
    case PieceType::ROOK:
      piece = new Rook(playerId);
      break;
    case PieceType::KNIGHT:
      piece = new Knight(playerId);
      break;
    case PieceType::BISHOP:
      piece = new Bishop(playerId);
      break;
    case PieceType::QUEEN:
      piece = new Queen(playerId);
      break;
    case PieceType::KING:
      piece = new King(playerId);
      break;
    case PieceType::PAWN:
      piece = new Pawn(playerId);
      break;
    case PieceType::EMPTY_PIECE:
      piece = new EmptyPiece();
      break;
  }

  return piece;
}

void Game::parseChessBoard(std::vector<std::vector<std::string>> chessBoard) {
  if (!isValidEncoding(chessBoard)) {
    return;
  }

  for (size_t y = 0; y < chessBoard.size(); ++y) {
    for (size_t x = 0; x < chessBoard[y].size(); ++x) {
      ChessPiece* chessPiece = initChessPiece(chessBoard[y][x]);
      // TODO: LOOK UP POTENTIAL BUGS WITH MIXING SIZE_T AND INT
      setBoardSpaceAtIndex(chessPiece, x, y);
    }
  }
}


void Game::initializeBoard() {
    std::vector<std::vector<std::string>> chessBoard = {{"DR", "DN", "DB", "DQ", "DK", "DB", "DN", "DR"},
                                                        {"DP", "DP", "DP", "DP", "DP", "DP", "DP", "DP"},
                                                        {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
                                                        {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
                                                        {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
                                                        {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
                                                        {"LP", "LP", "LP", "LP", "LP", "LP", "LP", "LP"},
                                                        {"LR", "LN", "LB", "LQ", "LK", "LB", "LN", "LR"}};
//  std::vector<std::vector<std::string>> chessBoard = {{"EE", "DN", "DB", "DQ", "DK", "DB", "DN", "DR"},
//                                                      {"LP", "DP", "DP", "DP", "DP", "DP", "DP", "DP"},
//                                                      {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
//                                                      {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
//                                                      {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
//                                                      {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
//                                                      {"DP", "LP", "LP", "LP", "LP", "LP", "LP", "LP"},
//                                                      {"EE", "EE", "EE", "EE", "LK", "EE", "EE", "LR"}};
  this->parseChessBoard(chessBoard);
  chessBoard.clear();
}
