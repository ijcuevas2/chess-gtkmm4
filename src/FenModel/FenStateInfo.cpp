//
// Created by Ismael Cuevas on 1/2/25.
//

#include "FenModel/FenStateInfo.h"

const std::string & FenStateInfo::getBoardConfigStr() const {
  return boardConfigStr;
}

const std::string & FenStateInfo::getTurnPlayerStr() const {
  return turnPlayerStr;
}

const std::string & FenStateInfo::getCastlingStr() const {
  return castlingStr;
}

const std::string & FenStateInfo::getEnPassantSquareStr() const {
  return enPassantSquareStr;
}

const std::string & FenStateInfo::getHalfTurnClockStr() const {
  return halfTurnClockStr;
}

const std::string & FenStateInfo::getTurnCounterStr() const {
  return turnCounterStr;
}

const std::string & FenStateInfo::getSrcBoardSpace() const {
  return srcBoardSpace;
}

const std::string & FenStateInfo::getTgtBoardSpace() const {
  return tgtBoardSpace;
}

const std::string & FenStateInfo::getCoreString() const {
  return coreStr;
}

void FenStateInfo::assignValueToCoreString() {
  std::stringstream ss;
  ss << getBoardConfigStr() << " ";
  coreStr = ss.str();
}

