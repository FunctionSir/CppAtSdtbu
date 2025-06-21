/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-06-12 11:41:43
 * @LastEditTime: 2025-06-12 16:40:55
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /7-Friend-OperatorOverloading/comms.hpp
 */
#ifndef __COMMS_HPP_INCLUDED__
#define __COMMS_HPP_INCLUDED__
#include "commentry.hpp"
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
using namespace std;
class Comms;
class Logger {
  public:
    Logger();
    Logger(string path);
    void SetLogger(string path);
    void LogChange(Comms &c, size_t idx, string type);
    void LogChange(CommEntry &ce, size_t idx, string type);
    void LogRaw(string s);
    ~Logger();

  private:
    int m_cnt;
    string m_path;
    ofstream m_ofs;
};
class Comms {
  public:
    friend class Logger;
    friend istream &operator>>(istream &is, Comms &comms);
    friend ostream &operator<<(ostream &os, const Comms &comms);
    Comms();
    Comms(string loggerPath);
    void NewEntry(void);
    void ModEntry();
    void DelEntry();

  private:
    vector<CommEntry> m_entries;
    Logger m_logger;
};
istream &operator>>(istream &is, Comms &comms);
ostream &operator<<(ostream &os, const Comms &comms);
#endif
