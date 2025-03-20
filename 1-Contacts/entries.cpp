/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-03-18 17:57:00
 * @LastEditTime: 2025-03-20 15:26:07
 * @LastEditors: FunctionSir
 * @Description: Entries related.
 * @FilePath: /CppAtSdtbu/1-Contacts/entries.cpp
 */
#include <iostream>
#include <sstream>
#include <string>
#ifndef __ENTRIES_CPP_INCLUDED__
#define __ENTRIES_CPP_INCLUDED__
namespace entries {
using namespace std;
class Entry {
  public:
    string FirstName, LastName;
    string Phone, Tel, Email;
    string Group, Note;

    void set_attributes(string firstName = "", string lastName = "",
                        string phone = "", string tel = "", string email = "",
                        string note = "") {
        FirstName = firstName, LastName = lastName;
        Phone = phone, Tel = tel, Email = email;
        Note = note;
    }

    // Build entry from cin, interactive.
    void from_cin_interactive(void) {
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

    // Build entry from USSV line.
    void from_ussv(string &ussv) {
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

    string get_en_full_name(void) {
        return FirstName + " " + LastName;
    }

    string get_asian_full_name(void) {
        return LastName + FirstName;
    }

    string to_ussv(string end = "") {
        return FirstName + "\x1f" + LastName + "\x1f" + Phone + "\x1f" + Tel +
               "\x1f" + Email + "\x1f" + Group + "\x1f" + Note + end;
    }

    string to_csv(bool useFullName = false, bool asianStyleName = false,
                  string separator = ",", string end = "") {
        string tmp = separator + Phone + separator + Tel + separator + Email +
                     separator + Group + separator + Note + end;
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

    static const string get_csv_header(bool useFullName = false,
                                       bool asianStyleName = false,
                                       string separator = ",",
                                       string end = "") {
        string tmp = separator + "手机" + separator + "座机" + separator +
                     "电邮" + separator + "所在组" + separator + "备注" + end;
        if (useFullName) {
            return "姓名" + tmp;
        }
        if (asianStyleName) {
            return "姓" + separator + "名" + tmp;
        } else {
            return "名" + separator + "姓" + tmp;
        }
    }

    static const bool chk_email(string &email) {
        if (email != "" && email != "-" && email.find('@') >= email.size()) {
            return false;
        }
        return true;
    }

    static const bool chk_phone(string &phone) {
        for (auto ch : phone) {
            if (ch != '-' && ch != '+' && ch < '0' && ch > '9') {
                return false;
            }
        }
        return true;
    }

    static const bool chk_tel(string &tel) {
        for (auto ch : tel) {
            if (ch != '-' && ch < '0' && ch > '9') {
                return false;
            }
        }
        return true;
    }

  private:
    enum Part {
        PartFirstName,
        PartLastName,
        PartPhone,
        PartTel,
        PartEmail,
        PartGroup,
        PartNote
    };

    void set_attribute_by_part_id(Part part, string &data) {
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
};
} // namespace entries
#endif
