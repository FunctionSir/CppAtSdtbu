/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-17 20:48:42
 * @LastEditTime: 2025-04-17 21:40:59
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /CppAtSdtbu/3-Exercises-4-10/date.hpp
 */

#ifndef __DATE_HPP_INCLUDED__
#define __DATE_HPP_INCLUDED__

#include <string>

class Date {
  public:
    Date(int y = 1970, int m = 1, int d = 1);
    void set(int y = 0, int m = 0, int d = 0);
    std::string to_string(void) const;

  private:
    int year, month, day;
};

#endif
