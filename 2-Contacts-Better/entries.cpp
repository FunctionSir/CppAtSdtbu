/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-03-18 17:57:00
 * @LastEditTime: 2025-04-03 20:42:53
 * @LastEditors: FunctionSir
 * @Description: Entries related.
 * @FilePath: /2-Contacts-Better/entries.cpp
 */
#include "entries.hpp"
#include "checkers.hpp"
#include <iostream>
#include <sstream>
using namespace entries;
void Entry::set_attributes(string firstName, string lastName, string phone, string tel, string email, string note) {
    FirstName = firstName, LastName = lastName;
    Phone = phone, Tel = tel, Email = email;
    Note = note;
}

void Entry::from_cin_interactive(void) {
    cerr << "Tips: 您可以使用\"-\"符号来作为\"占位符\"." << endl;
    cerr << "请输入姓(不要包含空格): " << endl << ">>> ";
    cin >> LastName;
    cerr << "请输入名(不要包含空格): " << endl << ">>> ";
    cin >> FirstName;
INPUT_PHONE:
    cerr << "请输入电话号(不要包含空格): " << endl << ">>> ";
    cin >> Phone;
    if (!chk_phone(Phone)) {
        cerr << "您输入的手机号有问题, 请重新输入." << endl;
        goto INPUT_PHONE;
    }
INPUT_TEL:
    cerr << "请输入座机号(不要包含空格): " << endl << ">>> ";
    cin >> Tel;
    if (!chk_phone(Tel)) {
        cerr << "您输入的座机号有问题, 请重新输入." << endl;
        goto INPUT_TEL;
    }
INPUT_EMAIL:
    cerr << "请输入邮箱(不要包含空格): " << endl << ">>> ";
    cin >> Email;
    if (!chk_email(Email)) {
        cerr << "您输入的邮箱有问题, 请重新输入." << endl;
        goto INPUT_EMAIL;
    }
    cerr << "请输入所在组(不要包含空格): " << endl << ">>> ";
    cin >> Group;
    cerr << "请输入备注(可以包含空格): " << endl << ">>> ";
    string _;
    getline(cin, _); // To skip last "Enter".
    getline(cin, Note);
}

void Entry::from_ussv(string &ussv) {
    int partCnt = 0;
    istringstream isstream(ussv);
    int tmpCh;
    string tmpStr;
    while (tmpCh = isstream.get(), tmpCh != '\n' && tmpCh != EOF) {
        if (tmpCh == 31) {
            set_attribute_by_part_id(Part(partCnt), tmpStr);
            partCnt++;
            tmpStr = "";
            continue;
        }
        tmpStr += (char)tmpCh;
    }
    set_attribute_by_part_id(Part(partCnt), tmpStr);
}

string Entry::get_en_full_name(void) const {
    return FirstName + " " + LastName;
}

string Entry::get_asian_full_name(void) const {
    return LastName + FirstName;
}

string Entry::to_ussv(string end) {
    return FirstName + "\x1f" + LastName + "\x1f" + Phone + "\x1f" + Tel + "\x1f" + Email + "\x1f" + Group + "\x1f" +
           Note + end;
}

string Entry::to_csv(bool useFullName, bool asianStyleName, string separator, string end) const {
    string tmp = separator + Phone + separator + Tel + separator + Email + separator + Group + separator + Note + end;
    if (useFullName) {
        if (asianStyleName) {
            return get_asian_full_name() + tmp;
        }
        return get_en_full_name() + tmp;
    } else {
        if (asianStyleName) {
            return LastName + separator + FirstName + tmp;
        }
        return FirstName + separator + LastName + tmp;
    }
}

void Entry::set_attribute_by_part_id(Part part, string &data) {
    switch (part) {
    case PartFirstName:
        FirstName = data;
        break;
    case PartLastName:
        LastName = data;
        break;
    case PartPhone:
        Phone = data;
    case PartTel:
        Tel = data;
    case PartEmail:
        Email = data;
    case PartGroup:
        Group = data;
    case PartNote:
        Note = data;
    };
}

string Entry::get_csv_header(bool useFullName, bool asianStyleName, string separator, string end) {
    string tmp =
        separator + "手机" + separator + "座机" + separator + "电邮" + separator + "所在组" + separator + "备注" + end;
    if (useFullName) {
        return "姓名" + tmp;
    }
    if (asianStyleName) {
        return "姓" + separator + "名" + tmp;
    } else {
        return "名" + separator + "姓" + tmp;
    }
}
