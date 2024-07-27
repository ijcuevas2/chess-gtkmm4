//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessBoard/ChessBoardModel.h"

ChessBoardModel::ChessBoardModel() : board(8, std::vector<BoardSpace *>(8)) {
  initBoard();
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

void ChessBoardModel::assignChessPieceToBoardSpaceIndex(ChessPiece *sourceChessPiecePtr, int row, int col) {
  if (this->board[row][col] != nullptr) {
    PlayerID playerId = sourceChessPiecePtr->getPlayerId();
    PieceType pieceType = sourceChessPiecePtr->getPieceType();
    ChessPiece* targetChessPiecePtr = initChessPiece(pieceType, playerId);
    ChessPiece* oldPiecePtr = this->getChessPiecePtr(row, col);
    if (oldPiecePtr != nullptr) {
      delete oldPiecePtr;
      oldPiecePtr = nullptr;
    }
    this->board[row][col]->setChessPiecePtr(targetChessPiecePtr);
  }
}

void ChessBoardModel::setBoardSpaceAtIndex(ChessPiece *chessPiecePtr, int row, int col) {
  BoardSpace *boardSpace = new BoardSpace(chessPiecePtr, row, col);
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

ChessPiece *ChessBoardModel::getChessPiecePtr(int row, int col) {
  const int currentBoardSize = this->board.size();
  if (currentBoardSize != 0) {
    return this->board[row][col]->getChessPiecePtr();
  }

  return nullptr;
}

BoardSpace *ChessBoardModel::getBoardSpacePtr(int row, int col) {
  const int currentBoardSize = this->board.size();
  if (currentBoardSize != 0) {
    return this->board[row][col];
  }

  return nullptr;
}

ChessPiece *ChessBoardModel::initChessPiece(PieceType pieceType, PlayerID playerId) {
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

ChessPiece *ChessBoardModel::initChessPiece(std::string pieceEncoding) {
  PieceType pieceType = parsePieceType(pieceEncoding);
  PlayerID playerId = parsePlayerId(pieceEncoding);
  ChessPiece *piece = this->initChessPiece(pieceType, playerId);
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

Glib::RefPtr<Gdk::Pixbuf> ChessBoardModel::getPieceImageContent(ChessPiece* chessPiece) {
  return chessImagesInfo.getPieceImageContent(chessPiece);
}

void ChessBoardModel::setSelectedBoardSpacePtr(BoardSpace* boardSpacePtr) {
  ChessPiece* chessPiecePtr = boardSpacePtr->getChessPiecePtr();

  if (chessPiecePtr != nullptr) {
    bool isTurnPlayerBool = isTurnPlayer(chessPiecePtr);
    if (isTurnPlayerBool) {
      this->selectedBoardSpacePtr = boardSpacePtr;
    }
  }
}

bool ChessBoardModel::isEmptyPiece(ChessPiece *chessPiecePtr) {
  if (chessPiecePtr != nullptr) {
    return chessPiecePtr->getPieceType() == PieceType::EMPTY_PIECE;
  }

  return false;
}

bool ChessBoardModel::isSelectedBoardSpacePtr(int row, int col) {
  BoardSpace* boardSpace = this->board[row][col];
  return boardSpace == this->selectedBoardSpacePtr;
}

BoardSpace* ChessBoardModel::getSelectedBoardSpacePtr() {
  return this->selectedBoardSpacePtr;
}

bool ChessBoardModel::hasSelectedBoardSpacePtr() {
  return this->selectedBoardSpacePtr != nullptr;
}

void ChessBoardModel::clearSelectedBoardSpacePtr() {
  this->selectedBoardSpacePtr = nullptr;
}

bool ChessBoardModel::isBoardSpaceOccupied(int row, int col) {
  ChessPiece* chessPiece = this->getChessPiecePtr(row, col);
  PieceType pieceType = chessPiece->getPieceType();
  bool isOccupied = pieceType != PieceType::EMPTY_PIECE;
  return isOccupied;
}

bool ChessBoardModel::isTurnPlayersChessPiece(ChessPiece *chessPiece, int targetRow, int targetCol) {
  PlayerID playerId = chessPiece->getPlayerId();
  ChessPiece* targetChessPiece = getChessPiecePtr(targetRow, targetCol);
  PlayerID targetPlayerId = targetChessPiece->getPlayerId();
  bool isTurnPlayersChessPiece = targetPlayerId == playerId;
  return isTurnPlayersChessPiece;
}

void ChessBoardModel::clearSelectedBoardSpace() {
  this->selectedBoardSpacePtr->clearChessPiecePtr();
  EmptyPiece* emptyPiece = new EmptyPiece();
  this->selectedBoardSpacePtr->setChessPiecePtr(emptyPiece);
}

void ChessBoardModel::clearBoard() {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      board[row][col]->clearChessPiecePtr();
      BoardSpace* boardSpacePtr = board[row][col];
      if (boardSpacePtr != nullptr) {
        delete boardSpacePtr;
        board[row][col] = nullptr;
      }
    }
  }

  turnPlayerId = PlayerID::PLAYER_LIGHT;
}

PlayerID ChessBoardModel::getTurnPlayerId() {
  return turnPlayerId;
}

void ChessBoardModel::updateTurnPlayerId() {
  if (turnPlayerId == PlayerID::PLAYER_LIGHT) {
    turnPlayerId = PlayerID::PLAYER_DARK;
  } else if (turnPlayerId == PlayerID::PLAYER_DARK) {
    turnPlayerId = PlayerID::PLAYER_LIGHT;
    currentTurn++;
  }
}

bool ChessBoardModel::isTurnPlayer(ChessPiece* chessPiecePtr) {
  PlayerID playerId = chessPiecePtr->getPlayerId();
  return isTurnPlayer(playerId);
}

bool ChessBoardModel::isTurnPlayer(PlayerID playerId) {
  return turnPlayerId == playerId;
}
