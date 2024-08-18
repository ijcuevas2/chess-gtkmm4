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

