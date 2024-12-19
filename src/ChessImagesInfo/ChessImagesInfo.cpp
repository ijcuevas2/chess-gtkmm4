//
// Created by Ismael Cuevas on 7/20/24.
//

#include "../../headers/ChessImagesInfo/ChessImagesInfo.h"

ChessImagesInfo::ChessImagesInfo() {
  std::map<PieceType, std::map<PlayerID, std::string>> chessPieceMap = {
          {PieceType::KING,   {{PlayerID::PLAYER_WHITE, "white_king.svg"},   {PlayerID::PLAYER_BLACK, "black_king.svg"}}},
          {PieceType::QUEEN,  {{PlayerID::PLAYER_WHITE, "white_queen.svg"},  {PlayerID::PLAYER_BLACK, "black_queen.svg"}}},
          {PieceType::ROOK,   {{PlayerID::PLAYER_WHITE, "white_rook.svg"},   {PlayerID::PLAYER_BLACK, "black_rook.svg"}}},
          {PieceType::BISHOP, {{PlayerID::PLAYER_WHITE, "white_bishop.svg"}, {PlayerID::PLAYER_BLACK, "black_bishop.svg"}}},
          {PieceType::KNIGHT, {{PlayerID::PLAYER_WHITE, "white_knight.svg"}, {PlayerID::PLAYER_BLACK, "black_knight.svg"}}},
          {PieceType::PAWN,   {{PlayerID::PLAYER_WHITE, "white_pawn.svg"},   {PlayerID::PLAYER_BLACK, "black_pawn.svg"}}}
  };
  std::vector<std::string> fileNames = {
          "white_king.svg",
          "white_queen.svg",
          "white_rook.svg",
          "white_bishop.svg",
          "white_knight.svg",
          "white_pawn.svg",
          "black_king.svg",
          "black_queen.svg",
          "black_rook.svg",
          "black_bishop.svg",
          "black_knight.svg",
          "black_pawn.svg"
  };

  setChessPieceMap(chessPieceMap);
  std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> piecesContentMap;
  fs::path imageDir = "/chess_resources/images/";

  for (size_t i = 0; i < fileNames.size(); ++i) {
    fs::path filePath = imageDir / fileNames[i];
    std::string filePathString = filePath.string();
    Glib::RefPtr<Gdk::Pixbuf> pixBuf;

    bool isValidFile = doesFileExist(filePathString);
    if (isValidFile) {
      try {
         pixBuf = Gdk::Pixbuf::create_from_resource(filePathString);
      } catch (const std::exception & ex) {
         std::cerr << "Error loading asset:" << ex.what() << std::endl;
      }
    }

    piecesContentMap[fileNames[i]] = pixBuf;
  }

  setPiecesContentMap(piecesContentMap);
}

void ChessImagesInfo::setChessPieceMap(std::map<PieceType, std::map<PlayerID, std::string>> chessPieceMap) {
  this->chessPieceMap = chessPieceMap;
}

void ChessImagesInfo::setPiecesContentMap(std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> piecesContentMap) {
  this->piecesContentMap = piecesContentMap;
}

Glib::RefPtr<Gdk::Pixbuf> ChessImagesInfo::getPieceImageContent(ChessPiece *chessPiece) {
  PlayerID playerId = chessPiece->getPlayerId();
  PieceType pieceType = chessPiece->getPieceType();

  std::string chessImagePath = chessPieceMap[pieceType][playerId];
  Glib::RefPtr<Gdk::Pixbuf> pixBuf = piecesContentMap[chessImagePath];
  return pixBuf;
}

bool ChessImagesInfo::doesFileExist(const std::string & filePath) {
  std::filesystem::path pathToCheck(filePath);

  bool isValidPath = std::filesystem::exists(pathToCheck);
  bool isRegularFile = std::filesystem::is_regular_file(pathToCheck);
  return isValidPath && isRegularFile;
}