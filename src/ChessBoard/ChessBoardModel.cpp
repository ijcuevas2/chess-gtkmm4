//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessBoard/ChessBoardModel.h"

ChessBoardModel::ChessBoardModel() : board(8, std::vector<BoardSpace *>(8)) {
  initBoard();
  chessBoardMediator.getCurrentTurnSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getCurrentTurn));
  chessBoardMediator.getIsBoardIndexOccupiedSignal().connect(
          sigc::mem_fun(*this, &ChessBoardModel::isBoardSpaceOccupied));
  chessBoardMediator.getIsTurnPlayerSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isTurnPlayerHelper));
  chessBoardMediator.getIsTurnPlayersChessPieceSignal().connect(
          sigc::mem_fun(*this, &ChessBoardModel::isTurnPlayersChessPieceHelper));
  chessBoardMediator.getUpdateKingPositionSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::updateKingPosition));
  chessBoardMediator.getIsKingOccupyingSpaceSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isKingOccupyingSpace));
  chessBoardMediator.getSetEnPassantSquareSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::setEnPassantSquare));
  chessBoardMediator.getIsEnPassantSquareSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::IsEnPassantSquare));
}

void ChessBoardModel::initBoard() {
  std::string defaultFenStateStr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w AHah - 0 1";
  initChessBoardFromFenStateString(defaultFenStateStr);
}

bool ChessBoardModel::isKingChessPiecePtr(ChessPiece *chessPiecePtr) {
  return chessPiecePtr->getPieceType() == PieceType::KING;
}

void ChessBoardModel::assignChessPieceToBoardSpaceIndex(ChessPiece *sourceChessPiecePtr, int row, int col) {
  if (this->board[row][col] != nullptr) {
    ChessPiece *oldPiecePtr = this->getChessPiecePtr(row, col);
    if (oldPiecePtr != nullptr) {
      delete oldPiecePtr;
      oldPiecePtr = nullptr;
    }
    this->board[row][col]->setChessPiecePtr(sourceChessPiecePtr);
  }
}

void ChessBoardModel::setNewBoardSpaceAtIndex(ChessPiece *chessPiecePtr, int row, int col) {
  BoardSpace *boardSpace = new BoardSpace(chessPiecePtr, row, col);
  this->board[row][col] = boardSpace;
}

int ChessBoardModel::getBoardSize() {
  return BOARD_SIZE;
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

ChessPiece *ChessBoardModel::initEmptyPiece() {
  return new EmptyPiece(chessBoardMediator);
}

bool ChessBoardModel::isValidEncoding(std::vector<std::vector<std::string>> & chessBoard) {
  const int EXPECTED_NUM_ROWS = 8;
  const int EXPECTED_NUM_SPACES = 8;

  if (chessBoard.size() != EXPECTED_NUM_ROWS) {
    return false;
  }

  for (std::vector<std::string> & row: chessBoard) {
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

Glib::RefPtr<Gdk::Pixbuf> ChessBoardModel::getPieceImageContent(ChessPiece *chessPiece) {
  return chessImagesInfo.getPieceImageContent(chessPiece);
}

void ChessBoardModel::setSelectedBoardSpacePtr(BoardSpace *boardSpacePtr) {
  ChessPiece *chessPiecePtr = boardSpacePtr->getChessPiecePtr();

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

bool ChessBoardModel::isSelectedBoardSpacePtr(BoardSpace *boardSpacePtr) {
  return boardSpacePtr == this->selectedBoardSpacePtr;
}

bool ChessBoardModel::isSelectedBoardSpacePtr(int row, int col) {
  BoardSpace *boardSpacePtr = this->board[row][col];
  return boardSpacePtr == this->selectedBoardSpacePtr;
}

BoardSpace *ChessBoardModel::getSelectedBoardSpacePtr() {
  return this->selectedBoardSpacePtr;
}

bool ChessBoardModel::hasSelectedBoardSpacePtr() {
  return this->selectedBoardSpacePtr != nullptr;
}

void ChessBoardModel::clearSelectedBoardSpacePtr() {
  this->selectedBoardSpacePtr = nullptr;
}

bool ChessBoardModel::isBoardSpaceOccupied(int row, int col) {
  ChessPiece *chessPiece = this->getChessPiecePtr(row, col);
  PieceType pieceType = chessPiece->getPieceType();
  bool isOccupied = pieceType != PieceType::EMPTY_PIECE;
  return isOccupied;
}

bool ChessBoardModel::isTurnPlayersChessPiece(ChessPiece *chessPiece, int tgtRow, int tgtCol) {
  PlayerID playerId = chessPiece->getPlayerId();
  return isTurnPlayersChessPieceHelper(playerId, tgtRow, tgtCol);
}

bool ChessBoardModel::isTurnPlayersChessPieceHelper(PlayerID playerId, int tgtRow, int tgtCol) {
  ChessPiece *targetChessPiece = getChessPiecePtr(tgtRow, tgtCol);
  PlayerID targetPlayerId = targetChessPiece->getPlayerId();
  bool isTurnPlayersChessPiece = targetPlayerId == playerId;
  return isTurnPlayersChessPiece;
}

void ChessBoardModel::clearSelectedBoardSpace() {
  EmptyPiece *emptyPiece = new EmptyPiece(chessBoardMediator);
  this->selectedBoardSpacePtr->setChessPiecePtr(emptyPiece);
}

void ChessBoardModel::clearBoard() {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      board[row][col]->clearChessPiecePtr();
      BoardSpace *boardSpacePtr = board[row][col];
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

bool ChessBoardModel::isTurnPlayer(BoardSpace *boardSpacePtr) {
  ChessPiece *chessPiecePtr = boardSpacePtr->getChessPiecePtr();
  return isTurnPlayer(chessPiecePtr);
}

bool ChessBoardModel::isTurnPlayer(ChessPiece *chessPiecePtr) {
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

void ChessBoardModel::showHintMarkers(BoardSpace *boardSpacePtr) {
  ChessPiece *chessPiecePtr = boardSpacePtr->getChessPiecePtr();
  int srcRow = boardSpacePtr->getRow();
  int srcCol = boardSpacePtr->getCol();

  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      BoardSpace *boardSpace = getBoardSpacePtr(row, col);
      Point2DPair point2DPair(srcRow, srcCol, row, col);
      if (chessPiecePtr->canMoveToTarget(point2DPair)) {
        boardSpace->showMarker();
      }
    }
  }
}

void ChessBoardModel::hideHintMarkers() {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      BoardSpace *boardSpace = getBoardSpacePtr(row, col);
      boardSpace->hideMarker();
    }
  }
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

bool ChessBoardModel::isKingOccupyingSpace(Point2D point2D) {
  ChessPiece *chessPiece = getChessPiecePtr(point2D.getRow(), point2D.getCol());
  if (chessPiece->getPieceType() == PieceType::KING) {
    return true;
  }

  return false;
}

PlayerID ChessBoardModel::getOppositePlayerId(PlayerID playerId) {
  if (playerId == PlayerID::PLAYER_WHITE) {
    return PlayerID::PLAYER_BLACK;
  }

  return PlayerID::PLAYER_WHITE;
}

Point2D ChessBoardModel::getKingCoordinates(PlayerID playerId) {
  if (playerId == PlayerID::PLAYER_WHITE) {
    return whiteKingCoordinates;
  }

  return blackKingCoordinates;
}

void ChessBoardModel::incrementHalfMoveClock() {
  halfMoveClock++;
}

void ChessBoardModel::resetHalfMoveClock() {
  halfMoveClock = 0;
}

void ChessBoardModel::calculateKingIsInCheck(PlayerID playerId) {
  Point2D kingPoint2D = getKingCoordinates(playerId);
  int kingRow = kingPoint2D.getRow();
  int kingCol = kingPoint2D.getCol();
  King* king = dynamic_cast<King *>(getChessPiecePtr(kingRow, kingCol));
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      ChessPiece *chessPiecePtr = getChessPiecePtr(row, col);
      Point2DPair currCoordinates(row, col, kingRow, kingCol);
      bool isCurrChessPieceAbleToCheck = chessPiecePtr->canMoveToTarget(currCoordinates);
      if (isCurrChessPieceAbleToCheck) {
        king->setIsInCheck(true);
      }
    }
  }
}

ChessPiece* ChessBoardModel::initChessPieceFromChar(char chessPieceChar) {
  ChessPiece* result = nullptr;
  switch (chessPieceChar) {
    case 'r':
      result = new Rook(PlayerID::PLAYER_BLACK, chessBoardMediator);
      break;
    case 'R':
      result = new Rook(PlayerID::PLAYER_WHITE, chessBoardMediator);
      break;
    case 'n':
      result = new Knight(PlayerID::PLAYER_BLACK, chessBoardMediator);
      break;
    case 'N':
      result = new Knight(PlayerID::PLAYER_WHITE, chessBoardMediator);
      break;
    case 'b':
      result = new Bishop(PlayerID::PLAYER_BLACK, chessBoardMediator);
      break;
    case 'B':
      result = new Bishop(PlayerID::PLAYER_WHITE, chessBoardMediator);
      break;
    case 'q':
      result = new Queen(PlayerID::PLAYER_BLACK, chessBoardMediator);
      break;
    case 'Q':
      result = new Queen(PlayerID::PLAYER_WHITE, chessBoardMediator);
      break;
    case 'k':
      result = new King(PlayerID::PLAYER_BLACK, chessBoardMediator);
      break;
    case 'K':
      result = new King(PlayerID::PLAYER_WHITE, chessBoardMediator);
      break;
    case 'p':
      result = new Pawn(PlayerID::PLAYER_BLACK, chessBoardMediator);
      break;
    case 'P':
      result = new Pawn(PlayerID::PLAYER_WHITE, chessBoardMediator);
      break;
  }

  return result;
}

void ChessBoardModel::initChessBoardFromFenStateString(std::string fenStateStr) {
  char delimiter = ' ';
  std::vector<std::string> fenSplitArr = StringUtils::split(fenStateStr, delimiter);
  std::string boardConfigStr = fenSplitArr[0];
  std::string turnPlayerStr = fenSplitArr[1];
  std::string castlingStr = fenSplitArr[2];
  std::string enPassantSquareStr = fenSplitArr[3];
  std::string halfTurnClockStr = fenSplitArr[4];
  std::string turnCounterStr = fenSplitArr[5];

  initChessBoardFromBoardConfig(boardConfigStr);
  turnPlayerId = getTurnPlayerFromStr(turnPlayerStr);
  restoreCastlingInfo(castlingStr);
  // enPassantSquareStr = ;
  halfMoveClock = std::stoi(halfTurnClockStr);
  currentTurn = std::stoi(turnCounterStr);
}

PlayerID ChessBoardModel::getTurnPlayerFromStr(std::string turnPlayerStr) {
  std::string trimmedTurnPlayer = StringUtils::trim(turnPlayerStr);
  if (trimmedTurnPlayer == "b") {
    return PlayerID::PLAYER_BLACK;
  }

  return PlayerID::PLAYER_WHITE;
}

void ChessBoardModel::restoreCastlingInfo(std::string castlingStr) {
  bool blackRookQueenSideCanCastle = StringUtils::containsCharacter(castlingStr, 'a');
  if (!blackRookQueenSideCanCastle) {
    restoreCastlingInfoHelper(0, 0);
  }

  bool blackRookKingSideCanCastle = StringUtils::containsCharacter(castlingStr, 'h');
  if (!blackRookKingSideCanCastle) {
    restoreCastlingInfoHelper(0, 7);
  }

  bool whiteRookQueenSideCanCastle = StringUtils::containsCharacter(castlingStr, 'A');
  if (!whiteRookQueenSideCanCastle) {
    restoreCastlingInfoHelper(7, 0);
  }

  bool whiteRookKingSideCanCastle = StringUtils::containsCharacter(castlingStr, 'H');
  if (!whiteRookKingSideCanCastle) {
    restoreCastlingInfoHelper(7, 7);
  }
}

void ChessBoardModel::restoreCastlingInfoHelper(int row, int col) {
  ChessPiece* chessPiece = getChessPiecePtr(row, col);
  if (chessPiece->getPieceType() == PieceType::ROOK) {
    Rook* rook = dynamic_cast<Rook*>(chessPiece);
    rook->setHasMoved();
  }
}

int ChessBoardModel::getCounterValue(int col, int counter) {
  int actualCounter = std::max(0, counter);
  return col + actualCounter;
}

void ChessBoardModel::initChessBoardFromBoardConfig(std::string boardConfigStr) {
  char delimiter = '/';
  std::vector<std::string> boardConfig = StringUtils::split(boardConfigStr, delimiter);
  for (int row = 0; row < boardConfig.size(); ++row) {
    std::string currentString = boardConfig.at(row);
    int counter = 0;
    for (int col = 0; col < currentString.size(); ++col) {
      char currentChar = currentString.at(col);
      ChessPiece* chessPiecePtr = nullptr;

      if (std::isdigit(currentChar)) {
        int currCounter = MathUtils::charToDigit(currentChar);
        int lastIndex = currCounter - 1;
        for (int i = 0; i < currCounter; ++i) {
          chessPiecePtr = initEmptyPiece();
          int targetCol = col + counter;
          setNewBoardSpaceAtIndex(chessPiecePtr, row, targetCol);
          if (i != lastIndex) {
            counter++;
          }
        }
      } else {
        chessPiecePtr = initChessPieceFromChar(currentChar);
        int targetCol = col + counter;

        if (isKingChessPiecePtr(chessPiecePtr)) {
          updateKingPosition(chessPiecePtr->getPlayerId(), row, col);
        }

        setNewBoardSpaceAtIndex(chessPiecePtr, row, targetCol);
      }
    }
  }
}

bool ChessBoardModel::isPawn(Point2D pair) {
  int row = pair.getRow();
  int col = pair.getCol();
  ChessPiece* chessPiecePtr = getChessPiecePtr(row, col);
  bool isPawnBool = chessPiecePtr->getPieceType() == PieceType::PAWN;
  return isPawnBool;
}

bool ChessBoardModel::IsEnPassantSquare(Point2D point2D) {
  bool isSameRow = point2D.getRow() == enPassantSquare.getRow();
  bool isSameCol = point2D.getCol() == enPassantSquare.getCol();
  return isSameRow && isSameCol;
}

void ChessBoardModel::setEnPassantSquare(Point2D point2D) {
  enPassantSquare = point2D;
}

void ChessBoardModel::clearEnPassantSquare() {
  enPassantSquare.setRow(-1);
  enPassantSquare.setCol(-1);
}