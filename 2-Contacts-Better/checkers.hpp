/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-03 20:37:32
 * @LastEditTime: 2025-04-03 20:37:51
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /2-Contacts-Better/checkers.hpp
 */
#ifndef __CHECKERS_HPP_INCLUDED__
#define __CHECKERS_HPP_INCLUDED__
#include <string>
using namespace std;
// Check emails.
bool chk_email(string &email);
// Check phone numbers.
bool chk_phone(string &phone);
// Check tel numbers.
bool chk_tel(string &tel);
#endif
