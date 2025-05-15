/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-17 14:14:57
 * @LastEditTime: 2025-05-15 15:19:32
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /4-Classes-Combination/commentry.hpp
 */

#ifndef __INCLUDED_ENTRIES_HPP__
#define __INCLUDED_ENTRIES_HPP__

#include <array>
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

const string TYPE_PHONE = "手机";
const string TYPE_TEL = "电话";
const string TYPE_PHONE_WORK = "工作手机";
const string TYPE_TEL_OFFICE = "办公室电话";

class CommEntry {
  public:
    // Default constructor.
    CommEntry();
    CommEntry(string name, string phone);
    CommEntry(string name, string type, string number);
    CommEntry(string name, vector<pair<string, string>> &data);
    CommEntry(string name, vector<array<string, 2>> &data);
    // CSV format: name,type1,number1,type2,number2,...,typeN,numberN
    CommEntry(string csv);
    CommEntry(const CommEntry &origin);
    CommEntry(CommEntry &&old);
    CommEntry &operator=(const CommEntry &right);
    ~CommEntry();
    string set_name(string name);
    bool set_phone(size_t pos, string number);
    bool set_phone(size_t pos, string type, string number);
    void append(string type, string number);
    const string &get_name(void) const;
    const string *get_types(void) const;
    const string *get_numbers(void) const;
    const string &get_type(size_t pos) const;
    const string &get_number(size_t pos) const;
    string to_csv(void) const;
    size_t size() const;
    static size_t get_tot_entries_cnt(void);

  private:
    void new_arrays(size_t s);
    size_t m_SizeArrLen;
    string m_StrName;
    string *m_StrPtrTypes;
    string *m_StrPtrNumbers;
    static size_t m_SizeTotEntriesExists;
};
#endif
