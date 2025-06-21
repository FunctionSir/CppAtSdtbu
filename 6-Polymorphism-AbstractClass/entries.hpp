/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-05-29 14:03:54
 * @LastEditTime: 2025-05-29 21:40:06
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /6-Polymorphism-AbstractClass/entries.hpp
 */
#ifndef __ENTRIES_HPP_INCLUDED__
#define __ENTRIES_HPP_INCLUDED__
#include <string>
using namespace std;
class AbstractEntry {
  public:
    virtual void input(void) = 0;
    virtual void output(void) = 0;
    // 析构函数不可纯虚, 但也不可不虚, 否则,
    // 会出现资源泄漏的问题.
    virtual ~AbstractEntry(void);
};

class EFriendEntry : public AbstractEntry {
  public:
    void input(void);
    void output(void);
    string getSocialAppName(void);
    string getSocialAppId(void);

  private:
    string social_app, social_app_name, social_app_id;
};

class CommEntry : public AbstractEntry {
  public:
    // 此处构造函数和析构函数均只用于实验测试.
    CommEntry(void);
    virtual void input(void);
    virtual void output(void);
    void setName(string nm);
    void setTel(string t);
    string getName(void);
    string getTel(void);
    ~CommEntry();

  private:
    string name, tel;
};

class FriendEntry : virtual public CommEntry {
  public:
    FriendEntry(void);
    virtual void input(void);
    virtual void output(void);
    void setAddr(string a);
    string getAddr(void);
    ~FriendEntry(void);

  private:
    // 这样其实挡不住直接靠xx.CommEntry::output()访问,
    // 但一定程度上可以防止如当前还没有实现子类的output时误用
    // 父类的output.
    using CommEntry::output;
    string addr;
};

class ClassmateEntry : virtual public CommEntry {
  public:
    ClassmateEntry(void);
    virtual void input(void);
    virtual void output(void);
    void setSchool(string s);
    void setClass(string c);
    void setAddr(string a);
    string getAddr(void);
    string getSchool(void);
    string getClass(void);
    ~ClassmateEntry();

  private:
    using CommEntry::output;
    string school, stuclass, addr;
};

class FriendClassmateEntry : public FriendEntry, public ClassmateEntry {
  public:
    FriendClassmateEntry(void);
    void input(void);
    void output(void);
    using ClassmateEntry::getAddr;
    using ClassmateEntry::getClass;
    using ClassmateEntry::getSchool;
    using ClassmateEntry::getTel;
    using ClassmateEntry::setAddr;
    using ClassmateEntry::setClass;
    using ClassmateEntry::setSchool;
    using ClassmateEntry::setTel;
    ~FriendClassmateEntry();
};

#endif
