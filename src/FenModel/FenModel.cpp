//
// Created by Ismael Cuevas on 7/28/24.
//

#include "../../headers/FenModel/FenModel.h"

FenModel::FenModel(ChessBoardModel &chessBoardModel) : chessBoardModel(chessBoardModel) {
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
  std::string chessEncoding = fenBoardStateStack.top();
  fenBoardStateStack.pop();
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

  fenBoardStateStack.push(resultEncoding);
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

bool FenModel::canBlackQueenSideRookCastle() {
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

bool FenModel::canBlackKingSideRookCastle() {
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

bool FenModel::canWhiteQueenSideRookCastle() {
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

bool FenModel::canWhiteKingSideRookCastle() {
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
  std::string fileName = ss.str() + ".txt";
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
    std::string fenEncoding = encodeChessBoard();
    saveGame(fenEncoding);
  }
}

void FenModel::loadStateFromFile() {
}