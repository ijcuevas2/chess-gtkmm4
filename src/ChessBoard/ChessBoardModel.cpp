//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessBoard/ChessBoardModel.h"

ChessBoardModel::ChessBoardModel() : board(8, std::vector<BoardSpace *>(8)) {
  initBoard();
  chessBoardMediator.getCurrentTurnSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getCurrentTurn));
  chessBoardMediator.getIsBoardIndexOccupiedSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isBoardSpaceOccupied));
  chessBoardMediator.getMovedTwoSpacesTurnSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getMovedTwoSpacesTurn));
  chessBoardMediator.getIsTurnPlayerSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isTurnPlayerHelper));
  chessBoardMediator.getIsTurnPlayersChessPieceSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isTurnPlayersChessPieceHelper));
  chessBoardMediator.getUpdateKingPositionSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::updateKingPosition));
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
      ChessPiece *chessPiecePtr = this->initChessPiece(pieceEncoding);
      if (isKingChessPiecePtr(chessPiecePtr)) {
        updateKingPosition(chessPiecePtr->getPlayerId(), row, col);
      }

      setBoardSpaceAtIndex(chessPiecePtr, row, col);
    }
  }
}

bool ChessBoardModel::isKingChessPiecePtr(ChessPiece* chessPiecePtr) {
  return chessPiecePtr->getPieceType() == PieceType::KING;
}

void ChessBoardModel::assignChessPieceToBoardSpaceIndex(ChessPiece *sourceChessPiecePtr, int row, int col) {
  if (this->board[row][col] != nullptr) {
    ChessPiece* oldPiecePtr = this->getChessPiecePtr(row, col);
    if (oldPiecePtr != nullptr) {
      delete oldPiecePtr;
      oldPiecePtr = nullptr;
    }
    this->board[row][col]->setChessPiecePtr(sourceChessPiecePtr);
  }
}

void ChessBoardModel::setBoardSpaceAtIndex(ChessPiece *chessPiecePtr, int row, int col) {
  BoardSpace* boardSpace = new BoardSpace(chessPiecePtr, row, col);
  this->board[row][col] = boardSpace;
}

int ChessBoardModel::getBoardSize() {
  return BOARD_SIZE;
}

PlayerID ChessBoardModel::parsePlayerId(std::string pieceEncoding) {
  const char firstChar = pieceEncoding[0];
  switch (firstChar) {
    case 'D':
      return PlayerID::PLAYER_BLACK;
      break;
    case 'L':
      return PlayerID::PLAYER_WHITE;
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

BoardSpace* ChessBoardModel::getBoardSpacePtr(int row, int col) {
  const int currentBoardSize = this->board.size();
  if (currentBoardSize != 0) {
    return this->board[row][col];
  }

  return nullptr;
}

ChessPiece* ChessBoardModel::initChessPiece(PieceType pieceType, PlayerID playerId) {
  ChessPiece* piece = NULL;
  switch (pieceType) {
    case PieceType::ROOK:
      piece = new Rook(playerId, chessBoardMediator);
      break;
    case PieceType::KNIGHT:
      piece = new Knight(playerId, chessBoardMediator);
      break;
    case PieceType::BISHOP:
      piece = new Bishop(playerId, chessBoardMediator);
      break;
    case PieceType::QUEEN:
      piece = new Queen(playerId, chessBoardMediator);
      break;
    case PieceType::KING:
      piece = new King(playerId, chessBoardMediator);
      break;
    case PieceType::PAWN:
      piece = new Pawn(playerId, chessBoardMediator);
      break;
    case PieceType::EMPTY_PIECE:
      piece = new EmptyPiece(chessBoardMediator);
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
      showHintMarkers(boardSpacePtr);
    }
  }
}

bool ChessBoardModel::isEmptyPiece(ChessPiece *chessPiecePtr) {
  if (chessPiecePtr != nullptr) {
    return chessPiecePtr->getPieceType() == PieceType::EMPTY_PIECE;
  }

  return false;
}

bool ChessBoardModel::isSelectedBoardSpacePtr(BoardSpace* boardSpacePtr) {
  return boardSpacePtr == this->selectedBoardSpacePtr;
}

bool ChessBoardModel::isSelectedBoardSpacePtr(int row, int col) {
  BoardSpace* boardSpacePtr = this->board[row][col];
  return boardSpacePtr == this->selectedBoardSpacePtr;
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

bool ChessBoardModel::isTurnPlayersChessPiece(ChessPiece *chessPiece, int tgtRow, int tgtCol) {
  PlayerID playerId = chessPiece->getPlayerId();
  return isTurnPlayersChessPieceHelper(playerId, tgtRow, tgtCol);
}

bool ChessBoardModel::isTurnPlayersChessPieceHelper(PlayerID playerId, int tgtRow, int tgtCol) {
  ChessPiece* targetChessPiece = getChessPiecePtr(tgtRow, tgtCol);
  PlayerID targetPlayerId = targetChessPiece->getPlayerId();
  bool isTurnPlayersChessPiece = targetPlayerId == playerId;
  return isTurnPlayersChessPiece;
}

void ChessBoardModel::clearSelectedBoardSpace() {
  EmptyPiece* emptyPiece = new EmptyPiece(chessBoardMediator);
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

  turnPlayerId = PlayerID::PLAYER_WHITE;
}

PlayerID ChessBoardModel::getTurnPlayerId() {
  return turnPlayerId;
}

void ChessBoardModel::updateTurnPlayerId() {
  if (turnPlayerId == PlayerID::PLAYER_WHITE) {
    turnPlayerId = PlayerID::PLAYER_BLACK;
  } else if (turnPlayerId == PlayerID::PLAYER_BLACK) {
    turnPlayerId = PlayerID::PLAYER_WHITE;
    currentTurn++;
  }
}

bool ChessBoardModel::isTurnPlayer(BoardSpace* boardSpacePtr) {
  ChessPiece* chessPiecePtr = boardSpacePtr->getChessPiecePtr();
  return isTurnPlayer(chessPiecePtr);
}

bool ChessBoardModel::isTurnPlayer(ChessPiece* chessPiecePtr) {
  PlayerID playerId = chessPiecePtr->getPlayerId();
  return isTurnPlayerHelper(playerId);
}

bool ChessBoardModel::isTurnPlayerHelper(PlayerID playerId) {
  return turnPlayerId == playerId;
}

int ChessBoardModel::getCurrentTurn() {
  return currentTurn;
}

int ChessBoardModel::getHalfMoveClock() {
  return halfMoveClock;
}

void ChessBoardModel::showHintMarkers(BoardSpace* boardSpacePtr) {
  ChessPiece* chessPiecePtr = boardSpacePtr->getChessPiecePtr();
  int srcRow = boardSpacePtr->getRow();
  int srcCol = boardSpacePtr->getCol();

  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      BoardSpace* boardSpace = getBoardSpacePtr(row, col);
      Point2DPair point2DPair(srcRow, srcCol, row, col);
      if (chessPiecePtr->canMoveToTarget (point2DPair)) {
        boardSpace->showMarker();
      }
    }
  }
}

void ChessBoardModel::hideHintMarkers() {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      BoardSpace* boardSpace = getBoardSpacePtr(row, col);
      boardSpace->hideMarker();
    }
  }
}

int ChessBoardModel::getMovedTwoSpacesTurn(int row, int col) {
  ChessPiece *chessPiece = getChessPiecePtr(row, col);
  if (chessPiece != NULL && chessPiece->getPieceType() == PieceType::PAWN) {
    Pawn *pawn = dynamic_cast<Pawn*>(chessPiece);
    int turn = pawn->getMovedTwoSpacesTurn();
    return turn;
  }

  return -1;
}

void ChessBoardModel::updateKingPosition(PlayerID playerId, int row, int col) {
  if (playerId == PlayerID::PLAYER_WHITE) {
    whiteKingCoordinates.setRow(row);
    whiteKingCoordinates.setCol(col);
  } else if (playerId == PlayerID::PLAYER_BLACK) {
    blackKingCoordinates.setRow(row);
    blackKingCoordinates.setCol(col);
  }
}

bool ChessBoardModel::canOpponentsPiecesPutKingInCheck(PlayerID playerId, Point2DPair point2DPair) {
  int tgtRow = point2DPair.getTgtRow();
  int tgtCol = point2DPair.getTgtCol();
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      ChessPiece* chessPiecePtr = getChessPiecePtr(tgtRow, tgtCol);
      Point2DPair currCoordinates(row, col, tgtRow, tgtCol);
      bool isCurrChessPieceAbleToCheck = chessPiecePtr->canMoveToTarget(currCoordinates);
      if (isCurrChessPieceAbleToCheck) {
        return true;
      }
    }
  }
}
