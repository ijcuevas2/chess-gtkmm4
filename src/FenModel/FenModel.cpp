//
// Created by Ismael Cuevas on 7/28/24.
//

#include "../../headers/FenModel/FenModel.h"

FenModel::FenModel(ChessBoardModel &chessBoardModel, ChessMediator & chessMediator) : chessBoardModel(chessBoardModel), chessMediator(chessMediator) {
  chessMediator.getAfterFileLoadedSignal().connect(sigc::mem_fun(*this, &FenModel::loadStateFromFile));
  chessMediator.getOnUndoButtonClicked().connect(sigc::mem_fun(*this, &FenModel::afterUndoButtonPressed));
  chessMediator.getSaveStateToFileSignal().connect(sigc::mem_fun(*this, &FenModel::saveStateToFile));
  chessMediator.getPointFromAlgebraicNotationSignal().connect(sigc::mem_fun(*this, &FenModel::fromAlgebraicNotation));
  chessMediator.getSetPrevMoveFromStringSignal().connect(sigc::mem_fun(*this, &FenModel::getPrevMoveHints));
}

std::string FenModel::encodeChessBoard() {
  std::string encoding = "";
  int boardSize = chessBoardModel.getBoardSize();
  int lastIndex = boardSize - 1;
  for (int row = 0; row < boardSize; ++row) {
    for (int col = 0; col < boardSize; ++col) {
      ChessPiece *chessPiecePtr = chessBoardModel.getChessPiecePtr(row, col);
      PieceType pieceType = chessPiecePtr->getPieceType();
      if (pieceType == PieceType::EMPTY_PIECE) {
        counter++;
      } else {
        if (counter > 0) {
          std::string counterStr = getCounterStr();
          encoding += counterStr;
        }

        encoding += getChessPieceEncoding(chessPiecePtr);
      }

      if (col == lastIndex) {
        std::string counterStr = getCounterStr();
        encoding += counterStr;
        encoding += "/";
      }
    }
  }

  return encoding;
}

bool FenModel::validateFenState(std::string fenState) {
  char delimiter = ' ';
  std::vector<std::string> fenSplitArr = StringUtils::split(fenState, delimiter);
  std::string boardConfigStr = fenSplitArr[0];
  char boardConfigDelimiter = '/';
  std::vector<std::string> boardConfig = StringUtils::split(fenState, boardConfigDelimiter);
  size_t boardSize = boardConfig.size();
  return boardSize == 8;
}

std::string FenModel::getTurnPlayerEncoding() {
  PlayerID playerId = chessBoardModel.getTurnPlayerId();
  std::string turnPlayerEncoding = "";
  switch (playerId) {
    case PlayerID::PLAYER_WHITE:
      turnPlayerEncoding = " w ";
      break;
    case PlayerID::PLAYER_BLACK:
      turnPlayerEncoding = " b ";
      break;
    default:
      break;
  }

  return turnPlayerEncoding;
}

std::string FenModel::getBoardState() {
  std::string chessEncoding = defaultFenStateStr;
  if (!fenDeque.empty()) {
    chessEncoding = fenDeque.back();
    fenDeque.pop_back();
  }

  return chessEncoding;
}

void FenModel::saveBoardState() {
  std::string resultEncoding = "";

  std::string chessEncoding = encodeChessBoard();
  resultEncoding += chessEncoding;

  std::string turnPlayerEncoding = getTurnPlayerEncoding();
  resultEncoding += turnPlayerEncoding;

  std::string castlingAvailabilityEncoding = getCastlingAvailability();
  resultEncoding += castlingAvailabilityEncoding;

  std::string enPassantSquare = getEnpassantSquare();
  resultEncoding += enPassantSquare;

  std::string halfMoveClockTurn = getHalfMoveClock();
  resultEncoding += halfMoveClockTurn;

  std::string currentTurn = getCurrentTurn();
  resultEncoding += currentTurn;

  std::string lastPieceMovedEncoding = getLastPieceMovedEncoding();
  resultEncoding += lastPieceMovedEncoding;

  fenDeque.push_back(resultEncoding);
  chessMediator.getUpdateUndoButtonUiSignal().emit(true);
}

std::string FenModel::getLastPieceMovedEncoding() {
  Point2DPair point2dPair = chessBoardModel.getPrevMoves();
  int srcRow = point2dPair.getSrcRow();
  int srcCol = point2dPair.getSrcCol();
  int tgtRow = point2dPair.getTgtRow();
  int tgtCol = point2dPair.getTgtCol();
  std::string srcAlgebraicNotation = toAlgebraicNotation(srcRow, srcCol);
  std::string tgtAlgebraicNotation = toAlgebraicNotation(tgtRow, tgtCol);
  return " " + srcAlgebraicNotation + " " + tgtAlgebraicNotation;
}

std::string FenModel::getHalfMoveClock() {
  int halfMoveClockInt = chessBoardModel.getHalfMoveClock();
  std::string halfMoveClock = std::to_string(halfMoveClockInt) + " ";
  return halfMoveClock;
}

std::string FenModel::getCurrentTurn() {
  int currentTurnInt = chessBoardModel.getCurrentTurn();
  std::string currentTurn = std::to_string(currentTurnInt);
  return currentTurn;
}

std::string FenModel::getCounterStr() {
  if (counter == 0) {
    return "";
  }

  std::string counterStr = std::to_string(counter);
  clearCounter();
  return counterStr;
}

void FenModel::clearCounter() {
  counter = 0;
}

char FenModel::getChessPieceEncoding(ChessPiece *chessPiecePtr) {
  PieceType pieceType = chessPiecePtr->getPieceType();
  PlayerID playerId = chessPiecePtr->getPlayerId();
  char pieceEncoding = ' ';
  switch (pieceType) {
    case PieceType::ROOK:
      pieceEncoding = 'r';
      break;
    case PieceType::KNIGHT:
      pieceEncoding = 'n';
      break;
    case PieceType::BISHOP:
      pieceEncoding = 'b';
      break;
    case PieceType::QUEEN:
      pieceEncoding = 'q';
      break;
    case PieceType::KING:
      pieceEncoding = 'k';
      break;
    case PieceType::PAWN:
      pieceEncoding = 'p';
      break;
    default:
      break;
  }

  char pieceEncodingResult = ' ';
  switch (playerId) {
    case PlayerID::PLAYER_BLACK:
      pieceEncodingResult = pieceEncoding;
      break;
    case PlayerID::PLAYER_WHITE:
      pieceEncodingResult = toupper(pieceEncoding);
      break;
    default:
      break;
  }

  return pieceEncodingResult;
}

std::string FenModel::canBlackQueenSideRookCastle() {
  int rookRow = 0;
  int rookCol = 0;
  int kingRow = 0;
  int kingCol = 4;
  bool canCastleVal = canCastle(rookRow, rookCol, kingRow, kingCol);
  if (canCastleVal) {
    return "a";
  }

  return "";
}

std::string FenModel::canBlackKingSideRookCastle() {
  int rookRow = 0;
  int rookCol = 7;
  int kingRow = 0;
  int kingCol = 4;

  bool canCastleVal = canCastle(rookRow, rookCol, kingRow, kingCol);
  if (canCastleVal) {
    return "h";
  }

  return "";
}

std::string FenModel::canWhiteQueenSideRookCastle() {
  int rookRow = 7;
  int rookCol = 0;
  int kingRow = 7;
  int kingCol = 4;

  bool canCastleVal = canCastle(rookRow, rookCol, kingRow, kingCol);
  if (canCastleVal) {
    return "A";
  }

  return "";
}

std::string FenModel::canWhiteKingSideRookCastle() {
  int rookRow = 7;
  int rookCol = 7;
  int kingRow = 7;
  int kingCol = 4;

  bool canCastleVal = canCastle(rookRow, rookCol, kingRow, kingCol);
  if (canCastleVal) {
    return "H";
  }

  return "";
}

std::string FenModel::getCastlingAvailability() {
  std::string castlingAvailabilityEncoding = "";
  castlingAvailabilityEncoding += canWhiteQueenSideRookCastle();
  castlingAvailabilityEncoding += canWhiteKingSideRookCastle();
  castlingAvailabilityEncoding += canBlackQueenSideRookCastle();
  castlingAvailabilityEncoding += canBlackKingSideRookCastle();
  return castlingAvailabilityEncoding;
}

bool FenModel::isRook(ChessPiece *chessPiecePtr) {
  if (chessPiecePtr != nullptr) {
    return chessPiecePtr->getPieceType() == PieceType::ROOK;
  }

  return false;
}

bool FenModel::isKing(ChessPiece *chessPiecePtr) {
  if (chessPiecePtr != nullptr) {
    return chessPiecePtr->getPieceType() == PieceType::KING;
  }

  return false;
}

bool FenModel::canCastle(int rookRow, int rookCol, int kingRow, int kingCol) {
  Rook *rookPtr = dynamic_cast<Rook *>(chessBoardModel.getChessPiecePtr(rookRow, rookCol));
  King *kingPtr = dynamic_cast<King *>(chessBoardModel.getChessPiecePtr(kingRow, kingCol));
  bool canRookCastle = true;
  bool canKingCastle = true;

  if (isRook(rookPtr) && isKing(kingPtr)) {
    canRookCastle = rookPtr->getCanCastle();
    canKingCastle = kingPtr->getCanCastle();
  }

  return canRookCastle && canKingCastle;
}

bool FenModel::createSaveDirectory() {
  dirName = "chess_saves";

  if (fs::exists(dirName)) {
   std::cout << "Directory '" << dirName << "' already exists." << std::endl;
   return true;
  }

  std::error_code ec;
  if (fs::create_directory(dirName, ec)) {
    std::cout << "Directory '" << dirName << "' created successfully." << std::endl;
    return true;
  } else {
    std::cerr << "Error creating directory '" << dirName << "': " << ec.message() << std::endl;
    return false;
  }
}

bool FenModel::saveGame(std::string content, std::string inputFilePath = "") {
  if (!isChessSavesDirValid) {
    return false;
  }

  fs::path outputPath = "";
  if (inputFilePath.empty()) {
    fs::path gmtFileName = FileUtils::generateGMTFilename();
    outputPath = dirName / gmtFileName;
  } else {
    outputPath = inputFilePath;
  }

  std::ofstream file(outputPath, std::ios::out | std::ios::trunc);
  if (!file.is_open()) {
    std::cerr << "Error opening file '" << outputPath << "' for writing." << std::endl;
    return false;
  }

  file << content;

  if (file.fail()) {
    std::cerr << "Error writing to file '" << outputPath << "'." << std::endl;
    file.close();
    return false;
  }

  file.close();
  std::cout << "Chess board saved to '" << outputPath << "'." << std::endl;
  return true;
}

void FenModel::saveStateToFile(std::string filePath = "") {
  isChessSavesDirValid = createSaveDirectory();
  if (isChessSavesDirValid) {
    std::string fenEncoding = getBoardState();
    saveGame(fenEncoding, filePath);
  }
}

void FenModel::loadStateFromFile(std::string filePath) {
  fs::path fsFilePath = filePath;

  std::ifstream file(fsFilePath);
  if (!file.is_open()) {
    std::cerr << "Error: unable to open the file " << filePath << std::endl;
    return;
  }

  std::string line;

  try {
    while (std::getline(file, line)) {
      fenDeque.push_back(line);
    }
  } catch (const std::exception & e) {
    std::cerr << "Error loading file: " << e.what() << std::endl;
    file.close();
    return;
  }

  file.close();
  updateBoardFromLatestFenString();
}

std::string FenModel::getEnpassantSquare() {
  Point2D enPassantCoordinates = chessMediator.getEnPassantSquareSignal().emit();
  int row = enPassantCoordinates.getRow();
  int col = enPassantCoordinates.getCol();
  std::string enPassantSquare = " " + toAlgebraicNotation(row, col) + " ";
  return enPassantSquare;
}

bool FenModel::calculateUndoButtonEnabled() {
  bool isEnabled = !fenDeque.empty();
  return isEnabled;
}

bool FenModel::hasFenStateStored() {
  return !fenDeque.empty();
}

std::string FenModel::getLatestFenString() {
  if (hasFenStateStored()) {
    std::string fenStateStr = fenDeque.back();
    return fenStateStr;
  }

  return defaultFenStateStr;
}

void FenModel::updateBoardFromLatestFenString() {
  std::string fenStateStr = getLatestFenString();
  chessBoardModel.clearBoard();
  chessBoardModel.initChessBoardFromFenStateString(fenStateStr);
  chessMediator.getUpdateUiSignal().emit();
  bool isVisible = calculateUndoButtonEnabled();
  chessMediator.getUpdateUndoButtonUiSignal().emit(isVisible);
  chessMediator.getUpdateLabelSignal().emit();
}

void FenModel::afterUndoButtonPressed() {
  if (!fenDeque.empty()) {
    fenDeque.pop_back();
  }

  updateBoardFromLatestFenString();
}

std::string FenModel::toAlgebraicNotation(int row, int col) {
  if (row == -1 || col == -1) {
    return "-";
  }

  char file = static_cast<char>('a' + col);
  char rank = static_cast<char>('8' - row);
  return std::string(1, file) + std::string(1, rank);
}

Point2D FenModel::fromAlgebraicNotation(std::string algebraicNotation) {
  if (algebraicNotation == "-") {
    Point2D result(-1, -1);
    return result;
  }

  // Convert file (column letter) to column index (0-7)
  int col = algebraicNotation[0] - 'a';

  // Convert rank (row number) to row index (0-7)
  int row = '8' - algebraicNotation[1];

  Point2D result(row, col);
  return result;
}

Point2DPair FenModel::getPrevMoveHints(std::string srcPoint2dEncoding, std::string tgtPoint2dEncoding) {
  Point2D srcPoint2d = fromAlgebraicNotation(srcPoint2dEncoding);
  Point2D tgtPoint2d = fromAlgebraicNotation(tgtPoint2dEncoding);
  Point2DPair prevMovePoint2dPair(srcPoint2d.getRow(), srcPoint2d.getCol(), tgtPoint2d.getRow(), tgtPoint2d.getCol());
  return prevMovePoint2dPair;
}