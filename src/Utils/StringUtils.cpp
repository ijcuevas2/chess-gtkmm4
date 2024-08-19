//
// Created by Ismael Cuevas on 8/18/24.
//

#include "../../headers/Utils/StringUtils.h"
#include <ranges>
#include <string_view>

std::vector<std::string> StringUtils::split(const std::string & input, char delimiter) {
  std::vector<std::string> result;

  auto range = input | std::ranges::views::split(delimiter);
  for (const auto & word : range) {
    result.emplace_back(word.begin(), word.end());
  }

  return result;
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
