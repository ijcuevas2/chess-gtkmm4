//
// Created by Ismael Cuevas on 8/18/24.
//

#include "../../headers/Utils/StringUtils.h"

std::vector<std::string> StringUtils::split(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string StringUtils::trim(std::string str) {
  // Remove leading spaces
  while (!str.empty() && std::isspace(str.front())) {
    str.erase(str.begin());
  }

  // Remove trailing spaces
  while (!str.empty() && std::isspace(str.back())) {
    str.pop_back();
  }

  return str;
}

bool StringUtils::containsCharacter(std::string str, char ch) {
  return std::find(str.begin(), str.end(), ch) != str.end();
}

std::string StringUtils::getPieceTypeName(PieceType pieceType) {
  switch (pieceType) {
    case PieceType::BISHOP:
      return "Bishop";
    case PieceType::EMPTY_PIECE:
      return "Empty";
    case PieceType::KING:
      return "King";
    case PieceType::KNIGHT:
      return "Knight";
    case PieceType::PAWN:
      return "Pawn";
    case PieceType::QUEEN:
      return "Queen";
    case PieceType::ROOK:
      return "Rook";
  }
}
