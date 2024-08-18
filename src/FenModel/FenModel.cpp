//
// Created by Ismael Cuevas on 7/28/24.
//

#include "../../headers/FenModel/FenModel.h"

FenModel::FenModel(ChessBoardModel &chessBoardModel, ChessWindowMediator & chessWindowMediator) : chessBoardModel(chessBoardModel), chessWindowMediator(chessWindowMediator) {
  chessWindowMediator.getAfterFileLoaded().connect(sigc::mem_fun(*this, &FenModel::loadStateFromFile));
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

void FenModel::loadChessBoardFromFenState(std::string fenStateStr) {
  bool isValidFenState = validateFenState(fenStateStr);
  char delimiter = ' ';

  if (!isValidFenState) {
    fenStateStr = defaultFenStateStr;
  }

  std::vector<std::string> fenSplitArr = StringUtils::split(fenStateStr, delimiter);
  std::string boardConfigStr = fenSplitArr[0];
  std::string currentTurnStr = fenSplitArr[1];
  std::string castlingStr = fenSplitArr[2];
  std::string enPassantSquareStr = fenSplitArr[3];
  std::string halfTurnClockStr = fenSplitArr[4];
  std::string turnCounterStr = fenSplitArr[5];
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

void FenModel::initChessBoardFromBoardConfig(std::string boardConfigStr) {
  char delimiter = '/';
  std::vector<std::string> boardConfig = StringUtils::split(boardConfigStr, delimiter);
  for (int col = 0; col < boardConfig.size(); ++col) {
    std::string currentString = boardConfig.at(col);
    for (int i = 0; i < currentString.size(); ++i) {
      char currentChar = currentString.at(i);
    }
  }
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

  fenDeque.push_back(resultEncoding);
}

std::string FenModel::getHalfMoveClock() {
  int halfMoveClockInt = chessBoardModel.getHalfMoveClock();
  std::string halfMoveClock = " " + std::to_string(halfMoveClockInt) + " ";
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
  bool hasRookMoved = true;
  bool hasKingMoved = true;

  if (isRook(rookPtr) && isKing(kingPtr)) {
    hasRookMoved = rookPtr->getHasMoved();
    hasKingMoved = kingPtr->getHasMoved();
  }

  return !hasRookMoved && !hasKingMoved;
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

std::string FenModel::generateGMTFilename() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&in_time_t), "%Y-%m-%d_%H-%M-%S_GMT");
  std::string chessExtension = ".chess";
  std::string fileName = ss.str() + chessExtension;
  return fileName;
}

bool FenModel::saveGame(std::string content) {
  if (!isChessSavesDirValid) {
    return false;
  }

  fs::path gmtFileName = generateGMTFilename();
  fs::path filePath = dirName / gmtFileName;
  std::ofstream file(filePath, std::ios::out | std::ios::trunc);
  if (!file.is_open()) {
    std::cerr << "Error opening file '" << filePath << "' for writing." << std::endl;
    return false;
  }

  file << content;

  if (file.fail()) {
    std::cerr << "Error writing to file '" << filePath << "'." << std::endl;
    file.close();
    return false;
  }

  file.close();
  std::cout << "Chess board saved to '" << filePath << "'." << std::endl;
  return true;
}

void FenModel::saveStateToFile() {
  isChessSavesDirValid = createSaveDirectory();
  if (isChessSavesDirValid) {
    std::string fenEncoding = getBoardState();
    saveGame(fenEncoding);
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
  getLatestFenString();
}

std::string FenModel::getEnpassantSquare() {
  std::string enPassantSquare = " - ";
  return enPassantSquare;
}

void FenModel::getLatestFenString() {
  if (!fenDeque.empty()) {
    std::string fenState = fenDeque.back();
    fenDeque.pop_back();
  }
}