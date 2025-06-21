/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-06-12 10:49:13
 * @LastEditTime: 2025-06-12 15:02:51
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /7-Friend-OperatorOverloading/commentry.cpp
 */
#include "commentry.hpp"
using namespace std;
istream &operator>>(istream &is, CommEntry &entry) {
    is >> entry.m_name >> entry.m_number;
    return is;
}
std::ostream &operator<<(ostream &os, const CommEntry &entry) {
    os << "姓名: " << entry.m_name << " 电话: " << entry.m_number;
    return os;
}
bool CommEntry::operator==(const CommEntry &b) {
    return m_name == b.m_name && m_number == b.m_number;
}
CommEntry::CommEntry(CommEntry &&other) {
    m_name = std::move(other.m_name);
    m_number = std::move(other.m_number);
    other.m_name = "";
    other.m_number = "";
}
CommEntry::CommEntry(string name, string number) {
    m_name = name, m_number = number;
}
CommEntry::CommEntry() {
    m_name = m_number = "";
}
CommEntry::CommEntry(const CommEntry &old) {
    m_name = old.m_name;
    m_number = old.m_number;
}
