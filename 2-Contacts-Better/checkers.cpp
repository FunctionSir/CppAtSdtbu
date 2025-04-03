/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-03 20:36:52
 * @LastEditTime: 2025-04-03 20:38:29
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /2-Contacts-Better/checkers.cpp
 */
#include "checkers.hpp"

bool chk_email(string &email) {
    if (email != "" && email != "-" && email.find('@') >= email.size()) {
        return false;
    }
    return true;
}

bool chk_phone(string &phone) {
    for (auto ch : phone) {
        if (ch != '-' && ch != '+' && ch < '0' && ch > '9') {
            return false;
        }
    }
    return true;
}

bool chk_tel(string &tel) {
    for (auto ch : tel) {
        if (ch != '-' && ch < '0' && ch > '9') {
            return false;
        }
    }
    return true;
}
