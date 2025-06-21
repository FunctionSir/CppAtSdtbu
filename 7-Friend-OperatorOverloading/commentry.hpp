/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-06-12 10:49:02
 * @LastEditTime: 2025-06-12 16:59:44
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /7-Friend-OperatorOverloading/commentry.hpp
 */
#ifndef __COMMENTRY_HPP_INCLUDED__
#define __COMMENTRY_HPP_INCLUDED__
#include <istream>
#include <ostream>
#include <string>
#include <utility>
using namespace std;
class CommEntry {
  public:
    CommEntry();
    CommEntry(string name, string number);
    CommEntry(const CommEntry &old);
    CommEntry(CommEntry &&other);
    CommEntry &operator=(const CommEntry &&other) {
        if (this != &other) {
            m_name = std::move(other.m_name);
            m_number = std::move(other.m_number);
        }
        return *this;
    }
    friend istream &operator>>(istream &is, CommEntry &entry);
    friend ostream &operator<<(ostream &os, const CommEntry &entry);
    bool operator==(const CommEntry &b);

  private:
    string m_name, m_number;
};
istream &operator>>(istream &is, CommEntry &entry);
ostream &operator<<(ostream &os, const CommEntry &entry);
#endif
