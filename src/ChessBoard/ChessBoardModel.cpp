//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessBoard/ChessBoardModel.h"

ChessBoardModel::ChessBoardModel(ChessMediator & chessMediator) : chessMediator(chessMediator) {
  chessMediator.getCurrentTurnSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getCurrentTurn));
  chessMediator.getIsBoardIndexOccupiedSignal().connect(
          sigc::mem_fun(*this, &ChessBoardModel::isBoardSpaceOccupied));
  chessMediator.getIsTurnPlayerSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isTurnPlayerHelper));
  chessMediator.getIsTurnPlayersChessPieceSignal().connect(
          sigc::mem_fun(*this, &ChessBoardModel::isTurnPlayersChessPieceHelper));
  chessMediator.getUpdateKingPositionSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::updateKingPosition));
  chessMediator.getIsKingOccupyingSpaceSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isKingOccupyingSpace));
  chessMediator.getSetEnPassantSquareSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::setEnPassantSquare));
  chessMediator.getIsEnPassantSquareSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isEnPassantSquare));
  chessMediator.getEnPassantCoordinatesSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getEnPassantCoordinates));
  chessMediator.getClearEnPassantSquareSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::clearEnPassantSquare));
  chessMediator.getClearEnPassantCaptureSpaceSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::clearEnPassantCaptureSpace));
  chessMediator.getEnPassantSquareSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getEnPassantSquare));
  chessMediator.getSetPrevMoveSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::setPrevMoves));
  chessMediator.getIsKingInCheckSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::isPlayerIdKingInCheck));
  chessMediator.getIsKingValidPathSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getIsKingValidPath));
  chessMediator.getTurnPlayerIdSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getTurnPlayerId));
  chessMediator.getRookCanCastleSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getRookCanCastle));
  chessMediator.getMoveRookAfterCastleSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::moveRookAfterCastle));
  chessMediator.getOpponentTurnPlayerIdSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getOpponentTurnPlayerId));
  chessMediator.getInitBoardWithCaptureInfo().connect(sigc::mem_fun(*this, &ChessBoardModel::initBoardWithCaptureInfo));
  chessMediator.getClearBoard().connect(sigc::mem_fun(*this, &ChessBoardModel::clearBoard));
}

void ChessBoardModel::initBoardWithCaptureInfo() {
  initBoardSpacePointers();
  initBoard();
  // initMovementTargets();
}

//void ChessBoardModel::initMovementTargets() {
//  for (int row = 0; row < BOARD_SIZE; ++row) {
//    for (int col = 0; col < BOARD_SIZE; ++col) {
//      ChessPiece* chessPiecePtr = getChessPiecePtr(row, col);
//      Point2D point2d(row, col);
//      chessPiecePtr->setMovementTargets(point2d);
//    }
//  }
//}

void ChessBoardModel::initBoardSpacePointers() {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      board[row][col] = nullptr;
    }
  }
}

Point2D ChessBoardModel::getEnPassantSquare() {
  return enPassantSquare;
}

void ChessBoardModel::initBoard() {
  std::string defaultFenStateStr = StringUtils::DEFAULT_FEN_STATE_STR;
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
    board[row][col]->setChessPiecePtr(sourceChessPiecePtr);
  }
}

void ChessBoardModel::assignEmptySpaceToBoardSpaceIndex(int row, int col) {
  EmptyPiece* emptyPiece = new EmptyPiece(chessMediator);
  assignChessPieceToBoardSpaceIndex(emptyPiece, row, col);
}

void ChessBoardModel::setNewBoardSpaceAtIndex(ChessPiece *chessPiecePtr, int row, int col) {
  BoardSpace* boardSpace = new BoardSpace(chessPiecePtr, row, col);
  this->board[row][col] = boardSpace;
}

int ChessBoardModel::getBoardSize() {
  return BOARD_SIZE;
}

ChessPiece *ChessBoardModel::getChessPiecePtr(int row, int col) {
  // NOTE: Maybe, a proper check should be added if the board is initialized
  BoardSpace* boardSpace = this->board[row][col];
  if (boardSpace != nullptr) {
    ChessPiece* chessPiece =  boardSpace->getChessPiecePtr();
    if (chessPiece != nullptr) {
      return chessPiece;
    }
  }

  return nullptr;
}

BoardSpace *ChessBoardModel::getBoardSpacePtr(int row, int col) {
  BoardSpace* boardSpace = this->board[row][col];
  return boardSpace;
}

ChessPiece *ChessBoardModel::initEmptyPiece() {
  return new EmptyPiece(chessMediator);
}

bool ChessBoardModel::getRookCanCastle(Point2D point2d) {
  int tgtRow = point2d.getRow();
  int tgtCol = point2d.getCol();
  ChessPiece* chessPiece = getChessPiecePtr(tgtRow, tgtCol);
  if (chessPiece == nullptr) {
    return false;
  }

  PieceType pieceType = chessPiece->getPieceType();
  if (pieceType == PieceType::ROOK) {
    Rook* rook = dynamic_cast<Rook*>(chessPiece);
    bool canCastle = rook->getCanCastle();
    return canCastle;
  }

  return false;
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
  EmptyPiece *emptyPiece = new EmptyPiece(chessMediator);
  this->selectedBoardSpacePtr->setChessPiecePtr(emptyPiece);
}

void ChessBoardModel::clearBoard() {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      board[row][col]->clearChessPiecePtr();
      BoardSpace *boardSpacePtr = board[row][col];
      if (boardSpacePtr != nullptr) {
        boardSpacePtr->hideMarker();
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

PlayerID ChessBoardModel::getOpponentTurnPlayerId() {
  if (turnPlayerId == PlayerID::PLAYER_WHITE) {
    return PlayerID::PLAYER_BLACK;
  } else {
    return PlayerID::PLAYER_WHITE;
  }
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
  Point2D srcPoint2d(boardSpacePtr->getRow(), boardSpacePtr->getCol());
  std::vector<Point2D> captureTargets = chessPiecePtr->getMovementTargets(srcPoint2d);
  for (Point2D point2d : captureTargets) {
    BoardSpace* boardSpace = getBoardSpacePtr(point2d.getRow(), point2d.getCol());
    boardSpace->showMarker();
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

PlayerID ChessBoardModel::getOpponentPlayerId(PlayerID playerId) {
  if (playerId == PlayerID::PLAYER_WHITE) {
    return PlayerID::PLAYER_BLACK;
  }

  return PlayerID::PLAYER_WHITE;
}

Point2D ChessBoardModel::getKingPoint2D(PlayerID playerId) {
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
  PlayerID oppositePlayerId = getOpponentPlayerId(playerId);
  Point2D kingPoint2D = getKingPoint2D(oppositePlayerId);
  int kingRow = kingPoint2D.getRow();
  int kingCol = kingPoint2D.getCol();
  ChessPiece* chessPiece = getChessPiecePtr(kingRow, kingCol);
  if (chessPiece->getPieceType() == PieceType::KING) {
    King* king = dynamic_cast<King*>(chessPiece);
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
}

ChessPiece* ChessBoardModel::initChessPieceFromChar(char chessPieceChar) {
  ChessPiece* result = nullptr;
  switch (chessPieceChar) {
    case 'r':
      result = new Rook(PlayerID::PLAYER_BLACK, chessMediator);
      break;
    case 'R':
      result = new Rook(PlayerID::PLAYER_WHITE, chessMediator);
      break;
    case 'n':
      result = new Knight(PlayerID::PLAYER_BLACK, chessMediator);
      break;
    case 'N':
      result = new Knight(PlayerID::PLAYER_WHITE, chessMediator);
      break;
    case 'b':
      result = new Bishop(PlayerID::PLAYER_BLACK, chessMediator);
      break;
    case 'B':
      result = new Bishop(PlayerID::PLAYER_WHITE, chessMediator);
      break;
    case 'q':
      result = new Queen(PlayerID::PLAYER_BLACK, chessMediator);
      break;
    case 'Q':
      result = new Queen(PlayerID::PLAYER_WHITE, chessMediator);
      break;
    case 'k':
      result = new King(PlayerID::PLAYER_BLACK, chessMediator);
      break;
    case 'K':
      result = new King(PlayerID::PLAYER_WHITE, chessMediator);
      break;
    case 'p':
      result = new Pawn(PlayerID::PLAYER_BLACK, chessMediator);
      break;
    case 'P':
      result = new Pawn(PlayerID::PLAYER_WHITE, chessMediator);
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
  std::string srcBoardSpace = fenSplitArr[6];
  std::string tgtBoardSpace = fenSplitArr[7];

  initChessBoardFromBoardConfig(boardConfigStr);
  turnPlayerId = getTurnPlayerFromStr(turnPlayerStr);
  restoreCastlingInfo(castlingStr);
  enPassantSquare = chessMediator.getPointFromAlgebraicNotationSignal().emit(enPassantSquareStr);
  halfMoveClock = std::stoi(halfTurnClockStr);
  currentTurn = std::stoi(turnCounterStr);
  setPrevMovesFromStrings(srcBoardSpace, tgtBoardSpace);
}

void ChessBoardModel::setPrevMoves(Point2DPair point2dPair) {
  prevMoves = point2dPair;
}

void ChessBoardModel::setPrevMovesFromStrings(std::string srcBoardSpace, std::string tgtBoardSpace) {
  if (srcBoardSpace == "-" || tgtBoardSpace == "-") {
    prevMoves = Point2DPair(-1, -1, -1, -1);
    return;
  }

  Point2DPair point2DPair = chessMediator.getSetPrevMoveFromStringSignal().emit(srcBoardSpace, tgtBoardSpace);
  prevMoves = point2DPair;
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
  if (blackRookQueenSideCanCastle) {
    restoreCastlingInfoHelper(0, 0);
  }

  bool blackRookKingSideCanCastle = StringUtils::containsCharacter(castlingStr, 'h');
  if (blackRookKingSideCanCastle) {
    restoreCastlingInfoHelper(0, 7);
  }

  bool whiteRookQueenSideCanCastle = StringUtils::containsCharacter(castlingStr, 'A');
  if (whiteRookQueenSideCanCastle) {
    restoreCastlingInfoHelper(7, 0);
  }

  bool whiteRookKingSideCanCastle = StringUtils::containsCharacter(castlingStr, 'H');
  if (whiteRookKingSideCanCastle) {
    restoreCastlingInfoHelper(7, 7);
  }
}

void ChessBoardModel::restoreCastlingInfoHelper(int row, int col) {
  ChessPiece* candidateRookPiece = getChessPiecePtr(row, col);
  ChessPiece* candidateKingPiece = getChessPiecePtr(row, 4);
  if (candidateRookPiece != nullptr && candidateKingPiece != nullptr) {
    PieceType candidateRookType = candidateRookPiece->getPieceType();
    PieceType candidateKingType = candidateKingPiece->getPieceType();
    if (candidateRookType == PieceType::ROOK && candidateKingType == PieceType::KING) {
      Rook* rook = dynamic_cast<Rook*>(candidateRookPiece);
      rook->setCanCastle(true);
      King* king = dynamic_cast<King*>(candidateKingPiece);
      king->setCanCastle(true);
    }
  }
}

void ChessBoardModel::moveRookAfterCastle(Point2D point2d) {
  int kingRow = point2d.getRow();
  int kingCol = point2d.getCol();
  int srcRookCol = -1;
  int tgtRookCol = -1;
  int firstIndex = 0;
  int lastIndex = 7;
  if (kingCol > 4) {
    srcRookCol = 7;
    tgtRookCol = lastIndex - 2;
  } else {
    srcRookCol = 0;
    tgtRookCol = firstIndex + 3;
  }

  BoardSpace* srcBoardSpacePtr = getBoardSpacePtr(kingRow, srcRookCol);
  BoardSpace* tgtBoardSpacePtr = getBoardSpacePtr(kingRow, tgtRookCol);

  if (srcBoardSpacePtr != nullptr && tgtBoardSpacePtr != nullptr) {
    ChessPiece* srcChessPiecePtr = srcBoardSpacePtr->getChessPiecePtr();
    ChessPiece* tgtChessPiecePtr = tgtBoardSpacePtr->getChessPiecePtr();
    if (tgtChessPiecePtr->getPieceType() == PieceType::EMPTY_PIECE) {
      tgtBoardSpacePtr->setChessPiecePtr(srcChessPiecePtr);
      srcBoardSpacePtr->setChessPiecePtr(tgtChessPiecePtr);
    }
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
          updateKingPosition(chessPiecePtr->getPlayerId(), row, targetCol);
        }

        setNewBoardSpaceAtIndex(chessPiecePtr, row, targetCol);
      }
    }
  }
}

bool ChessBoardModel::isPawn(Point2D point2d) {
  int row = point2d.getRow();
  int col = point2d.getCol();
  ChessPiece* chessPiecePtr = getChessPiecePtr(row, col);
  bool isPawnBool = chessPiecePtr->getPieceType() == PieceType::PAWN;
  return isPawnBool;
}

bool ChessBoardModel::isEnPassantSquare(Point2D point2d) {
  bool isSameRow = point2d.getRow() == enPassantSquare.getRow();
  bool isSameCol = point2d.getCol() == enPassantSquare.getCol();
  return isSameRow && isSameCol;
}

void ChessBoardModel::setEnPassantSquare(Point2D point2d) {
  enPassantSquare = point2d;
}

void ChessBoardModel::clearEnPassantSquare() {
  enPassantSquare.setRow(-1);
  enPassantSquare.setCol(-1);
}

Point2D ChessBoardModel::getEnPassantCoordinates(Point2DPair point2dPair) {
  int enPassantRow = point2dPair.getSrcRow();
  int enPassantCol = point2dPair.getTgtCol();
  Point2D point2d(enPassantRow, enPassantCol);
  return point2d;
}

void ChessBoardModel::clearEnPassantCaptureSpace(Point2DPair point2dPair) {
  Point2D enPassantPoint2d = getEnPassantCoordinates(point2dPair);
  int row = enPassantPoint2d.getRow();
  int col = enPassantPoint2d.getCol();
  assignEmptySpaceToBoardSpaceIndex(row, col);
}

Point2DPair ChessBoardModel::getPrevMoves() {
  return prevMoves;
}

bool ChessBoardModel::isPlayerIdKingInCheck(PlayerID playerId) {
  King* kingPtr = getPlayerIdKing(playerId);
  if (kingPtr != nullptr) {
    bool isInCheck = kingPtr->getIsInCheck();
    return isInCheck;
  }

  return false;
}

King* ChessBoardModel::getPlayerIdKing(PlayerID playerId) {
  Point2D kingCoordinates;
  if (playerId == PlayerID::PLAYER_WHITE) {
    kingCoordinates = whiteKingCoordinates;
  } else if (playerId == PlayerID::PLAYER_BLACK) {
    kingCoordinates = blackKingCoordinates;
  }

  ChessPiece* chessPiece = getChessPiecePtr(kingCoordinates.getRow(), kingCoordinates.getCol());
  PieceType pieceType = chessPiece->getPieceType();
  if (pieceType == PieceType::KING) {
    King* kingPtr = dynamic_cast<King*>(chessPiece);
    return kingPtr;
  }

  return nullptr;
}

bool ChessBoardModel::isPoint2dInArr(std::vector<Point2D> & point2dArr, Point2D point2d) {
  for (int i = 0; i < point2dArr.size(); ++i) {
    Point2D currentPoint = point2dArr[i];
    if (point2d == currentPoint) {
      return true;
    }
  }

  return false;
}

bool ChessBoardModel::getCurrentGameStatus(PlayerID playerId) {
  Point2D kingPoint2d = getKingPoint2D(playerId);
  std::vector<Point2D> adjacentPoints = MathUtils::getAdjacentKingPoints(kingPoint2d);
  King* kingPtr = getPlayerIdKing(playerId);

  if (kingPtr != nullptr) {
    bool isInCheck = kingPtr->getIsInCheck();
    if (!isInCheck) {
      return false;
    }

    int kingRow = kingPoint2d.getRow();
    int kingCol = kingPoint2d.getCol();
    for (Point2D point2d : adjacentPoints) {
      int targetRow = kingPoint2d.getRow() + point2d.getRow();
      int targetCol = kingPoint2d.getCol() + point2d.getCol();
      Point2DPair point2DPair(kingRow, kingCol, targetRow, targetCol);
      bool canMoveToTargetBool = kingPtr->canMoveToTarget(point2DPair);
      if (canMoveToTargetBool) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool ChessBoardModel::getIsKingValidPath(PlayerID playerId, Point2D targetPoint) {
  Point2D kingCoordinates = getKingPoint2D(playerId);
  std::vector<Point2D> adjacentPoints = MathUtils::getAdjacentKingPoints(kingCoordinates);
  PlayerID opponentPlayerId = getOpponentPlayerId(playerId);
  Point2D opponentKingCoordinates = getKingPoint2D(opponentPlayerId);
  std::vector<Point2D> opponentAdjacentPoints = MathUtils::getAdjacentKingPoints(opponentKingCoordinates);

  bool isPoint2dInArrBool = isPoint2dInArr(opponentAdjacentPoints, targetPoint);
  if (isPoint2dInArrBool) {
    return false;
  }

  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      ChessPiece* chessPiece = getChessPiecePtr(row, col);
      if (!isKingChessPiecePtr(chessPiece)) {
        Point2DPair kingMovementPair(row, col, targetPoint.getRow(), targetPoint.getCol());
        bool canMoveToTargetBool = chessPiece->canMoveToTarget(kingMovementPair);
        PlayerID currPiecePlayerId = chessPiece->getPlayerId();
        if (canMoveToTargetBool && playerId != currPiecePlayerId) {
          return false;
        }
      }
    }
  }

  return true;
}