/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-05-29 20:24:53
 * @LastEditTime: 2025-05-29 21:56:46
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /6-Polymorphism-AbstractClass/comms.hpp
 */
#ifndef __COMMS_HPP_INCLUDED__
#define __COMMS_HPP_INCLUDED__
#include "entries.hpp"
#include <vector>
class Comms {
  public:
    // 此处由于是教学性质的实验, 故未加校验, 但,
    // 在生产环境中, 诸如cnt或是输入的条目类型号,
    // 都是需要严格校验的. 特此说明.
    void NewComms(void);
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
#endif
