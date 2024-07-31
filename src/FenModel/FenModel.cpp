//
// Created by Ismael Cuevas on 7/28/24.
//

#include "../../headers/FenModel/FenModel.h"

FenModel::FenModel(ChessBoardModel & chessBoardModel) : chessBoardModel(chessBoardModel) {
}

std::string FenModel::encodeChessBoard() {
  std::string encoding = "";
  int boardSize = chessBoardModel.getBoardSize();
  int lastIndex = boardSize - 1;
  for (int row = 0; row < boardSize; ++row) {
    for (int col = 0; col < boardSize; ++col) {
      ChessPiece* chessPiecePtr = chessBoardModel.getChessPiecePtr(row, col);
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

char FenModel::getChessPieceEncoding(ChessPiece* chessPiecePtr) {
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

bool FenModel::canCastle(int rookRow, int rookCol, int kingRow, int kingCol) {
  Rook* rookPtr = dynamic_cast<Rook*>(chessBoardModel.getChessPiecePtr(rookRow, rookCol));
  bool hasRookMoved = rookPtr->getHasMoved();
  King* kingPtr = dynamic_cast<King*>(chessBoardModel.getChessPiecePtr(kingRow, kingCol));
  bool hasKingMoved = kingPtr->getHasMoved();
  return !hasRookMoved && !hasKingMoved;
}
