//
// Created by Ismael Cuevas on 8/18/24.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ranges>
#include <string_view>

class StringUtils {
public:
    static std::vector<std::string> split(const std::string & input, char delimiter);
    static std::string trim(std::string str);
    static bool containsCharacter(std::string str, char ch);
};

#endif //STRINGUTILS_H
