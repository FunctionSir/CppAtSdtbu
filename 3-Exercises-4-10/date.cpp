/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-17 20:48:51
 * @LastEditTime: 2025-04-17 21:38:47
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /CppAtSdtbu/3-Exercises-4-10/date.cpp
 */

#include "date.hpp"
#include <stdexcept>

std::string Date::to_string(void) const {
    return std::to_string(year) + "-" + std::to_string(month) + std::to_string(day);
}

inline void Date::set(int y, int m, int d) {
    int maxDays[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 11};
    if (y < 0) {
        throw std::invalid_argument("Year should larger than 0!");
        return;
    }
    if (y > 0) {
        year = y;
    }
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        maxDays[2]++;
    }
    if (m < 0 || m > 12) {
        throw std::invalid_argument("Year should between 1 and 12!");
        return;
    }
    if (m != 0) {
        month = m;
    }
    if (d < 0 || d > maxDays[m]) {
        throw std::invalid_argument("Invalid day!");
        return;
    }
    if (d != 0) {
        day = d;
    }
}
Date::Date(int y, int m, int d) {
    int maxDays[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 11};
    if (y <= 0) {
        throw std::invalid_argument("Year should larger than 0!");
        return;
    }
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        maxDays[2]++;
    }
    if (m <= 0 || m > 12) {
        throw std::invalid_argument("Year should between 1 and 12!");
        return;
    }
    if (d <= 0 || d > maxDays[m]) {
        throw std::invalid_argument("Invalid day!");
        return;
    }
    year = y, month = m, day = d;
}
