/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-05-29 20:24:53
 * @LastEditTime: 2025-06-17 11:47:36
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /8-UML-Exceptions-Templates/comms.hpp
 */
#ifndef __COMMS_HPP_INCLUDED__
#define __COMMS_HPP_INCLUDED__
#include "entries.hpp"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;
class Comms {
  public:
    // 此处由于是教学性质的实验, 故未加校验, 但,
    // 在生产环境中, 诸如cnt或是输入的条目类型号,
    // 都是需要严格校验的. 特此说明.
    // AddBatch默认不清空之前的条目.
    void AddBatch(void);
    // 同理, 为了方便起见, 这里的导入导出功能都是
    // 只为了实验, 并没有特别考虑各种复杂情况.
    // 只是实现了读入CommEntry和保存CommEntry.
    // Import默认不清空之前的条目.
    void Import(string path);
    void Export(string path);
    void Clear(void);
    void PrintComms(void);
    void Find(void);
    void Edit(void);
    void SeparateDisplay(void);
    void ShowTypeInfo(void);
    ~Comms();

  private:
    // 鉴于相关知识在之前已用过多次, 这里
    // 为方便起见使用vector.
    vector<AbstractEntry *> entries;
};

template <typename T> class GenericComms {
    void NewGenericComms(void) {
        int cnt;
        T newEntry;
        cout << "请输入条目个数: ";
        cin >> cnt;
        for (int i = 1; i <= cnt; i++) {
            cout << "=====  条目" << i << "  =====" << endl;
            newEntry.input();
            entries.push_back(newEntry);
        }
    }
    template <typename U> friend ostream &operator<<(ostream &os, GenericComms<U> comms);

  private:
    vector<T> entries;
};

template <typename T> ostream &operator<<(ostream &os, const GenericComms<T> &comms) {
    for (const auto &x : comms.entries) {
        os << x.output();
    }
    return os;
}
#endif
