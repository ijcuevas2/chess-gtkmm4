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
  chessMediator.getIsKingValidPathSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getIsValidKingSpace));
  chessMediator.getTurnPlayerIdSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getTurnPlayerId));
  chessMediator.getRookCanCastleSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getRookCanCastle));
  chessMediator.getMoveRookAfterCastleSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::moveRookAfterCastle));
  chessMediator.getOpponentTurnPlayerIdSignal().connect(sigc::mem_fun(*this, &ChessBoardModel::getOpponentTurnPlayerId));
  chessMediator.getInitBoardWithCaptureInfo().connect(sigc::mem_fun(*this, &ChessBoardModel::initBoardWithCaptureInfo));
  chessMediator.getClearBoard().connect(sigc::mem_fun(*this, &ChessBoardModel::clearBoard));
  chessMediator.getIsPointContainedInKingMovementTargetsSignal().connect(sigc::mem_fun(*this,
                                                                                       &ChessBoardModel::getIsPointContainedInKingMovementTargets));
}

void ChessBoardModel::initBoardWithCaptureInfo() {
  initBoardSpacePointers();
  initBoard();
}

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
  storeKingMovementTargets(turnPlayerId);

  if (turnPlayerId == PlayerID::PLAYER_WHITE) {
    turnPlayerId = PlayerID::PLAYER_BLACK;
  } else if (turnPlayerId == PlayerID::PLAYER_BLACK) {
    turnPlayerId = PlayerID::PLAYER_WHITE;
    currentTurn++;
  }

  storeKingMovementTargets(turnPlayerId);
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
  PlayerID playerId = chessPiecePtr->getPlayerId();
  Point2D srcPoint2d(boardSpacePtr->getRow(), boardSpacePtr->getCol());
  std::vector<Point2D> movementTargets = chessPiecePtr->getMovementTargets(srcPoint2d);
  for (Point2D targetPoint2d : movementTargets) {
    BoardSpace* boardSpace = getBoardSpacePtr(targetPoint2d.getRow(), targetPoint2d.getCol());
    bool canMoveToTarget = true;
    bool isInCheck = isPlayerIdKingInCheck(playerId);
    if (isInCheck) {
      Point2DPair point2dPair(srcPoint2d.getRow(), srcPoint2d.getCol(), targetPoint2d.getRow(), targetPoint2d.getCol());
      canMoveToTarget = canMoveToTarget2(chessPiecePtr, point2dPair);
    }

    if (canMoveToTarget) {
      boardSpace->showMarker();
    }
  }
}

bool ChessBoardModel::canMoveToTarget2(ChessPiece* chessPiecePtr, Point2DPair point2dPair) {
  PlayerID playerId = chessPiecePtr->getPlayerId();
  bool isKingInCheck = chessMediator.getIsKingInCheckSignal().emit(playerId);
  bool result;
  if (isKingInCheck) {
    result = chessPiecePtr->canMoveToTargetWhileInCheck(point2dPair);
  } else {
    result = chessPiecePtr->canMoveToTarget(point2dPair);
  }

  return result;
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

void ChessBoardModel::calculateOpponentKingIsInCheck(PlayerID playerId) {
  PlayerID opponentPlayerId = getOpponentPlayerId(playerId);
  Point2D kingPoint2D = getKingPoint2D(opponentPlayerId);
  int kingRow = kingPoint2D.getRow();
  int kingCol = kingPoint2D.getCol();
  ChessPiece* chessPiecePtr = getChessPiecePtr(kingRow, kingCol);
  bool isKingPtr = isKingChessPiecePtr(chessPiecePtr);
  if (isKingPtr) {
    bool isValidKingSpace = getIsValidKingSpace(opponentPlayerId, kingPoint2D);
    if (!isValidKingSpace) {
      King* king = dynamic_cast<King*>(chessPiecePtr);
      king->setIsInCheck(true);
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

  enPassantSquare = chessMediator.getPointFromAlgebraicNotationSignal().emit(enPassantSquareStr);
  halfMoveClock = std::stoi(halfTurnClockStr);
  currentTurn = std::stoi(turnCounterStr);

  initChessBoardFromBoardConfig(boardConfigStr);
  turnPlayerId = getTurnPlayerFromStr(turnPlayerStr);
  PlayerID opponentId = getOpponentPlayerId(turnPlayerId);
  restoreCastlingState(castlingStr);
  setPrevMovesFromStrings(srcBoardSpace, tgtBoardSpace);
  calculateOpponentKingIsInCheck(opponentId);
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

void ChessBoardModel::restoreCastlingState(std::string castlingStr) {
  bool blackRookQueenSideCanCastle = StringUtils::containsCharacter(castlingStr, 'a');
  if (blackRookQueenSideCanCastle) {
    restoreCastlingStateHelper(0, 0);
  }

  bool blackRookKingSideCanCastle = StringUtils::containsCharacter(castlingStr, 'h');
  if (blackRookKingSideCanCastle) {
    restoreCastlingStateHelper(0, 7);
  }

  bool whiteRookQueenSideCanCastle = StringUtils::containsCharacter(castlingStr, 'A');
  if (whiteRookQueenSideCanCastle) {
    restoreCastlingStateHelper(7, 0);
  }

  bool whiteRookKingSideCanCastle = StringUtils::containsCharacter(castlingStr, 'H');
  if (whiteRookKingSideCanCastle) {
    restoreCastlingStateHelper(7, 7);
  }
}

void ChessBoardModel::restoreCastlingStateHelper(int row, int col) {
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

        if (isPawnChessPiecePtr(chessPiecePtr)) {
          updatePawnFirstTurn(chessPiecePtr, row);
        }

        setNewBoardSpaceAtIndex(chessPiecePtr, row, targetCol);
      }
    }
  }
}

void ChessBoardModel::updatePawnFirstTurn(ChessPiece* chessPiecePtr, int row) {
  Pawn* pawn = dynamic_cast<Pawn*>(chessPiecePtr);
  PlayerID playerId = chessPiecePtr->getPlayerId();
  bool isWhiteAfterFirstTurn = playerId == PlayerID::PLAYER_BLACK && row != 1;
  bool isBlackAfterFirstTurn = playerId == PlayerID::PLAYER_WHITE && row != 6;
  if (isWhiteAfterFirstTurn || isBlackAfterFirstTurn) {
    pawn->setUsedFirstMove();
  }
}

bool ChessBoardModel::isPawnChessPiecePtr(ChessPiece* chessPiecePtr) {
  bool result = chessPiecePtr->getPieceType() == PieceType::PAWN;
  return result;
}

bool ChessBoardModel::isKingChessPiecePtr(ChessPiece* chessPiecePtr) {
  bool result = chessPiecePtr->getPieceType() == PieceType::KING;
  return result;
}

bool ChessBoardModel::isBishopChessPiecePtr(ChessPiece* chessPiecePtr) {
  bool result = chessPiecePtr->getPieceType() == PieceType::BISHOP;
  return result;
}

bool ChessBoardModel::isRookChessPiecePtr(ChessPiece* chessPiecePtr) {
  bool result = chessPiecePtr->getPieceType() == PieceType::ROOK;
  return result;
}

bool ChessBoardModel::isQueenChessPiecePtr(ChessPiece* chessPiecePtr) {
  bool result = chessPiecePtr->getPieceType() == PieceType::QUEEN;
  return result;
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

bool ChessBoardModel::getIsCheckmate(PlayerID playerId) {
  Point2D kingPoint2d = getKingPoint2D(playerId);
  King* kingPtr = getPlayerIdKing(playerId);
  bool kingHasNoMovementTargets = false;
  bool canOtherPieceBlockCheck = false;

  if (kingPtr != nullptr) {
    bool isInCheck = kingPtr->getIsInCheck();
    if (!isInCheck) {
      return false;
    }

    std::vector<Point2D> kingMovementTargets = kingPtr->getMovementTargets(kingPoint2d);
    kingHasNoMovementTargets = kingMovementTargets.empty();

    // std::vector
    std::vector<Point2D> playerIdPoints = getPointsByPlayerId(playerId);
    for (Point2D point2d : playerIdPoints) {
      ChessPiece* chessPiecePtr = getChessPiecePtr(point2d.getRow(), point2d.getCol());
      for (Point2D movementTarget : kingMovementTargets) {
        Point2DPair point2dPair(point2d.getRow(), point2d.getCol(), movementTarget.getRow(), movementTarget.getCol());
        bool canMoveToTargetBool = chessPiecePtr->canMoveToTarget(point2dPair);
        if (canMoveToTargetBool) {
          canOtherPieceBlockCheck = true;
        }
      }
    }
  }

  return kingHasNoMovementTargets && canOtherPieceBlockCheck;
}

std::vector<Point2D> ChessBoardModel::getPointsByPlayerId(PlayerID playerId) {
  std::vector<Point2D> playerIdPoints;
  for (int row = 0; row < MathUtils::BOARD_SIZE; ++row) {
    for (int col = 0; col < MathUtils::BOARD_SIZE; ++col) {
      ChessPiece* chessPiecePtr = getChessPiecePtr(row, col);
      bool hasPlayerId = chessPiecePtr->hasPlayerId(playerId);
      if (hasPlayerId) {
        Point2D currentPoint(row, col);
        playerIdPoints.push_back(currentPoint);
      }
    }
  }

  return playerIdPoints;
}

bool ChessBoardModel::getIsValidKingSpace(PlayerID playerId, Point2D targetPoint) {
  bool result = checkIfKnightBlocksKingSpace(playerId, targetPoint);
  if (result) {
    return false;
  }

  result = checkIfPawnBlocksKingSpace(playerId, targetPoint);
  if (result) {
    return false;
  }

  result = checkIfDiagonalCaptureBlocksKingSpace(playerId, targetPoint);
  if (result) {
    return false;
  }

  result = checkIfCardinalCaptureBlocksKingSpace(playerId, targetPoint);
  if (result) {
    return false;
  }

  result = checkIfOpponentKingBlocksKingSpace(playerId, targetPoint);
  if (result) {
    return false;
  }

  return true;
}

std::vector<Point2D> ChessBoardModel::getKnightsThatCanCapturePoint(PlayerID playerId, Point2D targetPoint) {
  std::vector<Point2D> pointsArr = {
    Point2D(targetPoint.getRow() + 1, targetPoint.getCol() + 2),
    Point2D(targetPoint.getRow() - 1, targetPoint.getCol() + 2),
    Point2D(targetPoint.getRow() + 1, targetPoint.getCol() - 2),
    Point2D(targetPoint.getRow() - 1, targetPoint.getCol() - 2),
    Point2D(targetPoint.getRow() + 2, targetPoint.getCol() + 1),
    Point2D(targetPoint.getRow() + 2, targetPoint.getCol() - 1),
    Point2D(targetPoint.getRow() - 2, targetPoint.getCol() + 1),
    Point2D(targetPoint.getRow() - 2, targetPoint.getCol() - 1)
  };

  std::vector<Point2D> result;
  for (Point2D point2d : pointsArr) {
    bool isValidPoint = MathUtils::isValidPoint2D(point2d);
    if (isValidPoint) {
      ChessPiece* chessPiecePtr = getChessPiecePtr(point2d.getRow(), point2d.getCol());
      bool hasOpponentPlayerId = chessPiecePtr->hasOpponentPlayerId(playerId);
      PieceType pieceType = chessPiecePtr->getPieceType();
      if (hasOpponentPlayerId && pieceType == PieceType::KNIGHT) {
        result.push_back(point2d);
      }
    }
  }

  return result;
}

bool ChessBoardModel::checkIfPawnBlocksKingSpace(PlayerID playerId, Point2D targetPoint) {
  std::vector<Point2D> points = getPawnsThatCanCapturePoint(playerId, targetPoint);
  bool hasPoints = !points.empty();
  return hasPoints;
}

bool ChessBoardModel::checkIfOpponentKingBlocksKingSpace(PlayerID playerId, Point2D targetPoint) {
  int offset = 1;

  std::vector<Point2D> pointArr = {
    Point2D(targetPoint.getRow() + offset, targetPoint.getCol()),
    Point2D(targetPoint.getRow() + offset, targetPoint.getCol() + offset),
    Point2D(targetPoint.getRow(), targetPoint.getCol() + offset),
    Point2D(targetPoint.getRow() - offset, targetPoint.getCol() + offset),
    Point2D(targetPoint.getRow() - offset, targetPoint.getCol()),
    Point2D(targetPoint.getRow() - offset, targetPoint.getCol() - offset),
    Point2D(targetPoint.getRow(), targetPoint.getCol() - offset),
    Point2D(targetPoint.getRow() + offset, targetPoint.getCol() - offset),
  };

  for (Point2D point2d : pointArr) {
    bool isValidPoint2d = MathUtils::isValidPoint2D(point2d);
    if (isValidPoint2d) {
      ChessPiece* chessPiecePtr = getChessPiecePtr(point2d.getRow(), point2d.getCol());
      bool hasOpponentId = chessPiecePtr->hasOpponentPlayerId(playerId);
      bool isKingPtr = isKingChessPiecePtr(chessPiecePtr);
      if (hasOpponentId && isKingPtr) {
        return true;
      }
    }
  }

  return false;
}

std::vector<Point2D> ChessBoardModel::getPawnsThatCanCapturePoint(PlayerID playerId, Point2D targetPoint) {
  int direction = playerId == PlayerID::PLAYER_WHITE ? -1 : 1;

  std::vector<Point2D> pointArr = {
          Point2D(targetPoint.getRow() + direction, targetPoint.getCol() - 1),
          Point2D(targetPoint.getRow() + direction, targetPoint.getCol() + 1)
  };

  std::vector<Point2D> result;

  for (Point2D point2d : pointArr) {
    bool isValidPoint2d = MathUtils::isValidPoint2D(point2d);
    if (isValidPoint2d) {
      ChessPiece* chessPiecePtr = getChessPiecePtr(point2d.getRow(), point2d.getCol());
      bool hasOpponentId = chessPiecePtr->hasOpponentPlayerId(playerId);
      bool isPawnPtr = isPawnChessPiecePtr(chessPiecePtr);
      if (hasOpponentId && isPawnPtr) {
        result.push_back(point2d);
      }
    }
  }

  return result;
}

bool ChessBoardModel::checkIfKnightBlocksKingSpace(PlayerID playerId, Point2D targetPoint) {
  std::vector<Point2D> pointArr = getKnightsThatCanCapturePoint(playerId, targetPoint);
  bool hasPoints = !pointArr.empty();
  return hasPoints;
}

std::vector<Point2D> ChessBoardModel::getPointsWithPiecesThatCardinalCapture(PlayerID playerId, Point2D targetPoint) {
  ChessPiece* targetPointPtr = getChessPiecePtr(targetPoint.getRow(), targetPoint.getCol());
  Point2D kingPoint = getKingPoint2D(playerId);
  std::vector<Point2D> pointArr = targetPointPtr->getDiagonalSpaces(targetPoint, kingPoint);
  std::vector<Point2D> result;
  for (Point2D point2d : pointArr) {
    bool isValidPoint2d = MathUtils::isValidPoint2D(point2d);
    if (isValidPoint2d) {
      ChessPiece* chessPiecePtr = getChessPiecePtr(point2d.getRow(), point2d.getCol());
      bool hasOpponentId = chessPiecePtr->hasOpponentPlayerId(playerId);
      bool isRookPtr = isRookChessPiecePtr(chessPiecePtr);
      bool isQueenPtr = isQueenChessPiecePtr(chessPiecePtr);
      bool isDiagonalCapture = isRookPtr || isQueenPtr;
      if (hasOpponentId && isDiagonalCapture) {
        result.push_back(point2d);
      }
    }
  }

  return result;
}

std::vector<Point2D> ChessBoardModel::getPointsWithPiecesThatDiagonalCapture(PlayerID playerId, Point2D targetPoint) {
  ChessPiece* targetPointPtr = getChessPiecePtr(targetPoint.getRow(), targetPoint.getCol());
  Point2D kingPoint = getKingPoint2D(playerId);
  std::vector<Point2D> pointArr = targetPointPtr->getDiagonalSpaces(targetPoint, kingPoint);
  std::vector<Point2D> result;
  for (Point2D point2d : pointArr) {
    bool isValidPoint2d = MathUtils::isValidPoint2D(point2d);
    if (isValidPoint2d) {
      ChessPiece* chessPiecePtr = getChessPiecePtr(point2d.getRow(), point2d.getCol());
      bool hasOpponentId = chessPiecePtr->hasOpponentPlayerId(playerId);
      bool isBishopPtr = isBishopChessPiecePtr(chessPiecePtr);
      bool isQueenPtr = isQueenChessPiecePtr(chessPiecePtr);
      bool isDiagonalCapture = isBishopPtr || isQueenPtr;
      if (hasOpponentId && isDiagonalCapture) {
        result.push_back(point2d);
      }
    }
  }

  return result;
}

bool ChessBoardModel::checkIfDiagonalCaptureBlocksKingSpace(PlayerID playerId, Point2D targetPoint) {
  std::vector<Point2D> pointArr = getPointsWithPiecesThatDiagonalCapture(playerId, targetPoint);
  bool hasPoints = !pointArr.empty();
  return hasPoints;
}

bool ChessBoardModel::checkIfCardinalCaptureBlocksKingSpace(PlayerID playerId, Point2D targetPoint) {
  std::vector<Point2D> pointArr = getPointsWithPiecesThatCardinalCapture(playerId, targetPoint);
  bool hasPoints = !pointArr.empty();
  return hasPoints;
}

bool ChessBoardModel::getIsPointContainedInKingMovementTargets(PlayerID playerId, Point2D targetPoint) {
  Point2D kingPoint2d = getKingPoint2D(playerId);
  ChessPiece* chessPiecePtr = getChessPiecePtr(kingPoint2d.getRow(), kingPoint2d.getCol());
  bool result = false;
  if (chessPiecePtr->getPieceType() == PieceType::KING) {
    std::vector<Point2D> movementTargets = chessPiecePtr->getMovementTargets(kingPoint2d);
    result = isPoint2dInArr(movementTargets, targetPoint);
  }

  return result;
}

std::vector<Point2D> ChessBoardModel::getKingMovementTargets(PlayerID playerId) {
  if (playerId == PlayerID::PLAYER_WHITE) {
    return whiteKingMovementTargets;
  } else if (playerId == PlayerID::PLAYER_BLACK) {
    return blackKingMovementTargets;
  }

  return std::vector<Point2D>();
}

void ChessBoardModel::storeKingMovementTargets(PlayerID playerId) {
  King* kingPtr = getPlayerIdKing(playerId);
  Point2D kingPoint2d = getKingPoint2D(playerId);
  std::vector<Point2D> movementTargets = kingPtr->getMovementTargets(kingPoint2d);

  if (playerId == PlayerID::PLAYER_BLACK) {
    blackKingMovementTargets = movementTargets;
  } else if (playerId == PlayerID::PLAYER_WHITE) {
    blackKingMovementTargets = movementTargets;
  }
}