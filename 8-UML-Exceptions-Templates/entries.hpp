/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-05-29 14:03:54
 * @LastEditTime: 2025-06-17 11:49:31
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /8-UML-Exceptions-Templates/entries.hpp
 */
#ifndef __ENTRIES_HPP_INCLUDED__
#define __ENTRIES_HPP_INCLUDED__
#include <ostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
using namespace std;
class AbstractEntry {
  public:
    virtual void input(void) = 0;
    virtual void output(void) = 0;
    virtual ostream &output(ostream &os) = 0;
    // 析构函数不可纯虚, 但也不可不虚, 否则,
    // 会出现资源泄漏的问题.
    virtual ~AbstractEntry(void);
};

class EFriendEntry : public AbstractEntry {
  public:
    void input(void);
    void output(void);
    ostream &output(ostream &os);
    string getSocialAppName(void);
    string getSocialAppId(void);

  private:
    string social_app, social_app_name, social_app_id;
};

class CommEntry : public AbstractEntry {
  public:
    // 此处构造函数和析构函数均只用于实验测试.
    CommEntry(void);
    CommEntry(string name);
    virtual void input(void);
    virtual void output(void);
    virtual ostream &output(ostream &os);
    void setName(string nm);
    void setTel(string t);
    string getName(void) const;
    string getTel(void) const;
    ~CommEntry();

  private:
    string m_name, m_tel;
};

class FriendEntry : virtual public CommEntry {
  public:
    FriendEntry(void);
    FriendEntry(string name);
    virtual void input(void);
    virtual void output(void);
    virtual ostream &output(ostream &os);
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
    virtual ostream &output(ostream &os);
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
    ostream &output(ostream &os);
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

template <typename Container> AbstractEntry *FindEntry(const Container &cont, const string &name) {
    for (auto iter = cont.begin(); iter != cont.end(); iter++) {
        if (iter->getName() == name) {
            return const_cast<AbstractEntry *>(dynamic_cast<const AbstractEntry *>(&(*iter)));
        }
    }
    return nullptr;
}

// 自定义指针转换错误异常.
class bad_pointer_cast : public bad_cast {
  public:
    bad_pointer_cast();
    bad_pointer_cast(string err);
    bad_pointer_cast(const char *err);
    const char *what(void) const noexcept;

  private:
    string error;
};

// 自定义电话错误异常.
class InvalidPhoneException : public out_of_range {
  public:
    InvalidPhoneException();
    InvalidPhoneException(string err);
    InvalidPhoneException(char *err);
};

#endif
