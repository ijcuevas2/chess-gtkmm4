//
// Created by Ismael Cuevas on 7/20/24.
//

#include "../../headers/ChessImagesInfo/ChessImagesInfo.h"

ChessImagesInfo::ChessImagesInfo() {
  std::map<PieceType, std::map<PlayerID, std::string>> chessPieceMap = {
          {PieceType::KING,   {{PlayerID::PLAYER_LIGHT, "light_king.svg"},   {PlayerID::PLAYER_DARK, "dark_king.svg"}}},
          {PieceType::QUEEN,  {{PlayerID::PLAYER_LIGHT, "light_queen.svg"},  {PlayerID::PLAYER_DARK, "dark_queen.svg"}}},
          {PieceType::ROOK,   {{PlayerID::PLAYER_LIGHT, "light_rook.svg"},   {PlayerID::PLAYER_DARK, "dark_rook.svg"}}},
          {PieceType::BISHOP, {{PlayerID::PLAYER_LIGHT, "light_bishop.svg"}, {PlayerID::PLAYER_DARK, "dark_bishop.svg"}}},
          {PieceType::KNIGHT, {{PlayerID::PLAYER_LIGHT, "light_knight.svg"}, {PlayerID::PLAYER_DARK, "dark_knight.svg"}}},
          {PieceType::PAWN,   {{PlayerID::PLAYER_LIGHT, "light_pawn.svg"},   {PlayerID::PLAYER_DARK, "dark_pawn.svg"}}}
  };
  std::vector<std::string> fileNames = {
          "light_king.svg",
          "dark_king.svg",
          "light_rook.svg",
          "dark_rook.svg",
          "light_bishop.svg",
          "dark_bishop.svg",
          "light_knight.svg",
          "dark_knight.svg"
  };

  setChessPieceMap(chessPieceMap);
  std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> piecesContentMap;
  const std::string imageDir = "/chess_resources/images/";

  for (size_t i = 0; i < fileNames.size(); ++i) {
    try {
      std::string filePath = imageDir + fileNames[i];
      piecesContentMap[fileNames[i]] = Gdk::Pixbuf::create_from_file(filePath);
    } catch (const Glib::Error &ex) {
      std::cerr << "Error loading asset:" << ex.what() << std::endl;
    }
  }

  setPiecesContentMap(piecesContentMap);
}

void ChessImagesInfo::setChessPieceMap(std::map<PieceType, std::map<PlayerID, std::string>> chessPieceMap) {
  this->chessPieceMap = chessPieceMap;
}

void ChessImagesInfo::setPiecesContentMap(std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> piecesContentMap) {
  this->piecesContentMap = piecesContentMap;
}

Glib::RefPtr<Gdk::Pixbuf> ChessImagesInfo::getPieceImageContent(ChessPiece* chessPiece) {
  PlayerID playerId = chessPiece->getPlayerId();
  PieceType pieceType = chessPiece->getPieceType();

  std::string chessImagePath = chessPieceMap[pieceType][playerId];
  Glib::RefPtr<Gdk::Pixbuf> pixBuf = piecesContentMap[chessImagePath];
  return pixBuf;
}

