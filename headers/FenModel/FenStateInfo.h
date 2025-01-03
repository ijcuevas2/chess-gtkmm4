//
// Created by Ismael Cuevas on 1/2/25.
//

#ifndef CHESS_FENSTATEINFO_H
#define CHESS_FENSTATEINFO_H

#include <string>
#include <vector>
#include "../Utils/StringUtils.h"

class FenStateInfo {
private:
    std::string coreStr;
    std::string origStr;
    std::string boardConfigStr;
    std::string turnPlayerStr;
    std::string castlingStr;
    std::string enPassantSquareStr;
    std::string halfTurnClockStr;
    std::string turnCounterStr;
    std::string srcBoardSpace;
    std::string tgtBoardSpace;
public:
    FenStateInfo(std::string str) {
      char delimiter = ' ';
      std::vector<std::string> fenSplitArr = StringUtils::split(str, delimiter);
      boardConfigStr = fenSplitArr[0];
      turnPlayerStr = fenSplitArr[1];
      castlingStr = fenSplitArr[2];
      enPassantSquareStr = fenSplitArr[3];
      halfTurnClockStr = fenSplitArr[4];
      turnCounterStr = fenSplitArr[5];
      srcBoardSpace = fenSplitArr[6];
      tgtBoardSpace = fenSplitArr[7];
      assignValueToCoreString();
    }

    const std::string & getBoardConfigStr() const;
    const std::string & getTurnPlayerStr() const;
    const std::string & getCastlingStr() const;
    const std::string & getEnPassantSquareStr() const;
    const std::string & getHalfTurnClockStr() const;
    const std::string & getTurnCounterStr() const;
    const std::string & getSrcBoardSpace() const;
    const std::string & getTgtBoardSpace() const;
    const std::string & getCoreString() const;
    void assignValueToCoreString();
};

#endif //CHESS_FENSTATEINFO_H
