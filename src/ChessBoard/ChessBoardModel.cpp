//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessBoard/ChessBoardModel.h"

ChessBoardModel::ChessBoardModel() : board(8, std::vector<BoardSpace*>(8)) {
  this->initBoard();
}

std::vector<std::vector<std::string>> ChessBoardModel::getBoardConfig() {
  std::vector<std::vector<std::string>> boardConfig = {
          {"DR", "DN", "DB", "DQ", "DK", "DB", "DN", "DR"},
          {"DP", "DP", "DP", "DP", "DP", "DP", "DP", "DP"},
          {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
          {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
          {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
          {"EE", "EE", "EE", "EE", "EE", "EE", "EE", "EE"},
          {"LP", "LP", "LP", "LP", "LP", "LP", "LP", "LP"},
          {"LR", "LN", "LB", "LQ", "LK", "LB", "LN", "LR"}
  };

  return boardConfig;
}

void ChessBoardModel::initBoard() {
  std::vector<std::vector<std::string>> boardConfig = this->getBoardConfig();
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      std::string pieceEncoding = boardConfig[row][col];
      ChessPiece *chessPiece = this->initChessPiece(pieceEncoding);
      setBoardSpaceAtIndex(chessPiece, row, col);
    }
  }
}

void ChessBoardModel::setBoardSpaceAtIndex(ChessPiece *chessPiece, int row, int col) {
  BoardSpace *boardSpace = new BoardSpace(chessPiece, row, col);
  this->board[row][col] = boardSpace;
}

int ChessBoardModel::getBoardSize() {
  return BOARD_SIZE;
}

PlayerID ChessBoardModel::parsePlayerId(std::string pieceEncoding) {
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

PieceType ChessBoardModel::parsePieceType(std::string pieceEncoding) {
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

ChessPiece *ChessBoardModel::getChessPiece(int row, int col) {
  if (this->board.size() != 0) {
    return this->board[row][col]->getChessPiece();
  }

  return nullptr;
}

BoardSpace *ChessBoardModel::getBoardSpace(int row, int col) {
  if (this->board.size() != 0) {
    return this->board[row][col];
  }

  return nullptr;
}

ChessPiece *ChessBoardModel::initChessPiece(std::string pieceEncoding) {
  PieceType pieceType = parsePieceType(pieceEncoding);
  PlayerID playerId = parsePlayerId(pieceEncoding);
  ChessPiece *piece = NULL;

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

bool ChessBoardModel::isValidEncoding(std::vector<std::vector<std::string>> chessBoard) {
  const int EXPECTED_NUM_ROWS = 8;
  const int EXPECTED_NUM_SPACES = 8;

  if (chessBoard.size() != EXPECTED_NUM_ROWS) {
    return false;
  }

  for (std::vector<std::string> &row: chessBoard) {
    if (row.size() != EXPECTED_NUM_SPACES) {
      return false;
    }

    for (std::string &pieceEncoding: row) {
      if (pieceEncoding.size() != 2) {
        return false;
      }
    }
  }

  return true;
}
