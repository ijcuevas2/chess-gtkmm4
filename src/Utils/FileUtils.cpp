//
// Created by Ismael Cuevas on 8/21/24.
//

#include "Utils/FileUtils.h"

std::string FileUtils::generateGMTFilename() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&in_time_t), "%Y-%m-%d_%H-%M-%S_GMT");
  std::string chessExtension = ".chess";
  std::string fileName = ss.str() + chessExtension;
  return fileName;
}

