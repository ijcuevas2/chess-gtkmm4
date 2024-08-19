//
// Created by Ismael Cuevas on 8/18/24.
//

#ifndef INC_2024_08_11_05_01_24_GMT_TXT_STRINGUTILS_H
#define INC_2024_08_11_05_01_24_GMT_TXT_STRINGUTILS_H

#include <iostream>
#include <algorithm>
#include <string>

class StringUtils {
public:
    static std::vector<std::string> split(const std::string & input, char delimiter);
    static std::string trim(std::string str);
    static bool containsCharacter(std::string str, char ch);
};

#endif //INC_2024_08_11_05_01_24_GMT_TXT_STRINGUTILS_H
