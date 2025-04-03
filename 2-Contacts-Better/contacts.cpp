/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-03-18 17:56:27
 * @LastEditTime: 2025-04-03 21:35:36
 * @LastEditors: FunctionSir
 * @Description: Contacts related.
 * @FilePath: /2-Contacts-Better/contacts.cpp
 */
#include "contacts.hpp"
#include "checkers.hpp"
#include "entries.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>
using namespace contacts;

Contacts::Contacts() {
    Loaded = false;
}

Contacts::Contacts(string filePath) {
    load_from_file(filePath);
}

Contacts::~Contacts() {
    if (Loaded) {
        flush();
    }
}

bool Contacts::flush() {
    ofstream fileStream(FilePath);
    if (!fileStream.is_open()) {
        return false;
    }
    save_as(fileStream);
    return true;
}

bool Contacts::load_from_file(string filePath) {
    FilePath = filePath;
    ifstream fileStream;
    fileStream.open(filePath);
    if (!fileStream.is_open()) {
        Loaded = false;
        return false;
    }
    string tmp;
    while (getline(fileStream, tmp)) {
        entries::Entry newEntry;
        newEntry.from_ussv(tmp);
        add_new_entry(newEntry);
    }
    Loaded = true;
    fileStream.close();
    return true;
}

bool Contacts::is_loaded() const {
    return Loaded;
}

string Contacts::file_path() const {
    return FilePath;
}

void Contacts::list_to_cout(char sortBy, bool desc, bool asianStyle) const {
    vector<pair<int, entries::Entry>> entries_with_index;
    cout << "索引\t" << entries::Entry::get_csv_header(true, asianStyle, "\t", "\n");
    int curIndex = 0;
    for (auto e : Entries) {
        entries_with_index.push_back({curIndex, e});
        curIndex++;
    }
    switch (sortBy) {
    case 'L':
        if (!desc) {
            for (auto i : ByLastName) {
                cout << "[ " << i.first << " ]" << "\n";
                for (auto j : i.second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        } else {
            for (auto i = ByLastName.rbegin(); i != ByLastName.rend(); i++) {
                cout << "[ " << i->first << " ]" << "\n";
                for (auto j : i->second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        }
        break;
    case 'F':
        if (!desc) {
            for (auto i : ByFirstName) {
                cout << "[ " << i.first << " ]" << "\n";
                for (auto j : i.second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        } else {
            for (auto i = ByFirstName.rbegin(); i != ByFirstName.rend(); i++) {
                cout << "[ " << i->first << " ]" << "\n";
                for (auto j : i->second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        }
        break;
    case 'P':
        if (!desc) {
            for (auto i : ByPhone) {
                for (auto j : i.second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        } else {
            for (auto i = ByPhone.rbegin(); i != ByPhone.rend(); i++) {
                for (auto j : i->second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        }
        break;
    case 'T':
        if (!desc) {
            for (auto i : ByTel) {
                for (auto j : i.second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        } else {
            for (auto i = ByTel.rbegin(); i != ByTel.rend(); i++) {
                for (auto j : i->second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        }
        break;
    case 'E':
        if (!desc) {
            for (auto i : ByEmail) {
                for (auto j : i.second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        } else {
            for (auto i = ByEmail.rbegin(); i != ByEmail.rend(); i++) {
                for (auto j : i->second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        }
        break;
    case 'G':
        if (!desc) {
            for (auto i : ByGroup) {
                cout << "[ " << i.first << " ]" << "\n";
                for (auto j : i.second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        } else {
            for (auto i = ByGroup.rbegin(); i != ByGroup.rend(); i++) {
                cout << "[ " << i->first << " ]" << "\n";
                for (auto j : i->second) {
                    cout << entries_with_index[j].first << "\t"
                         << entries_with_index[j].second.to_csv(true, asianStyle, "\t", "\n");
                }
            }
        }
    }
    cout << "条目总数: " << Entries.size() << endl;
}

void Contacts::export_to_csv(bool useFullName, bool asianStyle, string separator, ofstream &outStream) {
    outStream << entries::Entry::get_csv_header(useFullName, asianStyle, separator, "\n");
    for (auto e : Entries) {
        outStream << e.to_csv(useFullName, asianStyle, separator, "\n");
    }
    cout << "导出的条目总数: " << Entries.size() << endl;
}

void Contacts::save_as(ofstream &outStream) {
    for (auto e : Entries) {
        outStream << e.to_ussv("\n");
    }
    outStream.close();
}

void Contacts::new_from_cin_interactive() {
    if (size() + 1 >= numeric_limits<size_t>::max()) {
        cerr << "此电话本已经无法容纳更多条目! 请考虑使用第二个文件或删除不必要的条目!";
        return;
    }
    entries::Entry newEntry;
    newEntry.from_cin_interactive();
    add_new_entry(newEntry);
}

// This is not declared as a const func, but it should be a const func!
set<size_t> Contacts::find_full(char by, string &target) {
    set<size_t> result;
    bool flg = 0;
    switch (by) {
    case 'L':
        return ByLastName[target];
    case 'F':
        return ByFirstName[target];
    case 'N':
        if (target.find(' ') >= target.size()) {
            flg = 1; // No space, an asian name.
        }
        for (size_t i = 0; i < Entries.size(); i++) {
            if ((flg ? Entries[i].get_asian_full_name() : Entries[i].get_en_full_name()) == target) {
                result.insert(i);
            }
        }
        return result;
    case 'P':
        return ByPhone[target];
        break;
    case 'T':
        return ByTel[target];
    case 'E':
        return ByEmail[target];
    case 'G':
        return ByGroup[target];
    default:
        return result;
    }
}

set<size_t> Contacts::find_part(char by, string &target) const {
    set<size_t> result;
    bool flg = 0;
    switch (by) {
    case 'L':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (Entries[i].LastName.find(target) < Entries[i].LastName.length()) {
                result.insert(i);
            }
        }
        return result;
    case 'F':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (Entries[i].FirstName.find(target) < Entries[i].FirstName.length()) {
                result.insert(i);
            }
        }
        return result;
    case 'N':
        if (target.find(' ') >= target.size()) {
            flg = 1; // No space, an asian name.
        }
        for (size_t i = 0; i < Entries.size(); i++) {
            string tmp = (flg ? Entries[i].get_asian_full_name() : Entries[i].get_en_full_name());
            if (tmp.find(target) < tmp.length()) {
                result.insert(i);
            }
        }
        return result;
    case 'P':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (Entries[i].Phone.find(target) < Entries[i].Phone.length()) {
                result.insert(i);
            }
        }
        return result;
    case 'T':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (Entries[i].Tel.find(target) < Entries[i].Tel.length()) {
                result.insert(i);
            }
        }
        return result;
    case 'E':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (Entries[i].Email.find(target) < Entries[i].Email.length()) {
                result.insert(i);
            }
        }
        return result;
    case 'G':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (Entries[i].Group.find(target) < Entries[i].Group.length()) {
                result.insert(i);
            }
        }
        return result;
    default:
        return result;
    }
}

set<size_t> Contacts::find_regex(char by, string &target) const {
    regex pattern(target);
    set<size_t> result;
    bool flg = 0;
    switch (by) {
    case 'L':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (regex_match(Entries[i].LastName, pattern)) {
                result.insert(i);
            }
        }
        return result;
    case 'F':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (regex_match(Entries[i].FirstName, pattern)) {
                result.insert(i);
            }
        }
        return result;
    case 'N':
        if (target.find(' ') >= target.size()) {
            flg = 1; // No space, an asian name.
        }
        for (size_t i = 0; i < Entries.size(); i++) {
            string tmp = (flg ? Entries[i].get_asian_full_name() : Entries[i].get_en_full_name());
            if (regex_match(tmp, pattern)) {
                result.insert(i);
            }
        }
        return result;
    case 'P':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (regex_match(Entries[i].Phone, pattern)) {
                result.insert(i);
            }
        }
        return result;
    case 'T':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (regex_match(Entries[i].Tel, pattern)) {
                result.insert(i);
            }
        }
        return result;
    case 'E':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (regex_match(Entries[i].Email, pattern)) {
                result.insert(i);
            }
        }
        return result;
    case 'G':
        for (size_t i = 0; i < Entries.size(); i++) {
            if (regex_match(Entries[i].Group, pattern)) {
                result.insert(i);
            }
        }
        return result;
    default:
        return result;
    }
}

void Contacts::cout_by_res_set(set<size_t> &res, bool asianStyle) {
    cout << "索引\t" << entries::Entry::get_csv_header(true, asianStyle, "\t", "\n");
    for (auto i : res) {
        cout << i << "\t" << Entries[i].to_csv(true, asianStyle, "\t", "\n");
    }
    cout << "条目总数: " << res.size() << endl;
}

void Contacts::delete_entry(size_t index) {
    entries::Entry &targetEntry = Entries[index];
    ByFirstName[targetEntry.FirstName].erase(index);
    ByLastName[targetEntry.LastName].erase(index);
    ByPhone[targetEntry.Phone].erase(index);
    ByTel[targetEntry.Tel].erase(index);
    ByEmail[targetEntry.Email].erase(index);
    ByGroup[targetEntry.Group].erase(index);
    Entries.erase(Entries.begin() + long(index));
}

bool Contacts::mod_entry(size_t index, char part, string &data) {
    switch (part) {
    case 'F':
        ByFirstName[Entries[index].FirstName].erase(index);
        Entries[index].FirstName = data;
        ByFirstName[Entries[index].FirstName].insert(index);
        break;
    case 'L':
        ByLastName[Entries[index].LastName].erase(index);
        Entries[index].LastName = data;
        ByLastName[Entries[index].LastName].insert(index);
        break;
    case 'P':
        if (!chk_phone(data)) {
            return false;
        }
        ByPhone[Entries[index].Phone].erase(index);
        Entries[index].Phone = data;
        ByPhone[Entries[index].Phone].insert(index);
        break;
    case 'T':
        if (!chk_tel(data)) {
            return false;
        }
        ByTel[Entries[index].Tel].erase(index);
        Entries[index].Tel = data;
        ByTel[Entries[index].Tel].insert(index);
        break;
    case 'E':
        if (!chk_email(data)) {
            return false;
        }
        ByEmail[Entries[index].Email].erase(index);
        Entries[index].Email = data;
        ByEmail[Entries[index].Email].insert(index);
        break;
    case 'G':
        ByGroup[Entries[index].Group].erase(index);
        Entries[index].Group = data;
        ByGroup[Entries[index].Group].insert(index);
        break;
    case 'N':
        Entries[index].Note = data;
    default:
        return false;
    }
    return true;
}

size_t Contacts::size(void) const {
    return Entries.size();
}

const entries::Entry &Contacts::get_entry_const_ref(size_t index) const {
    return Entries[index];
}

const vector<entries::Entry> &Contacts::get_entries_vec_const_ref(void) const {
    return Entries;
}

void Contacts::add_new_entry(entries::Entry &newEntry) {
    Entries.push_back(newEntry);
    ByFirstName[newEntry.FirstName].insert(Entries.size() - 1);
    ByLastName[newEntry.LastName].insert(Entries.size() - 1);
    ByPhone[newEntry.Phone].insert(Entries.size() - 1);
    ByTel[newEntry.Tel].insert(Entries.size() - 1);
    ByEmail[newEntry.Email].insert(Entries.size() - 1);
    ByGroup[newEntry.Group].insert(Entries.size() - 1);
}

void Contacts::load_from_ifstream(ifstream &fileStream) {
    string tmp;
    while (getline(fileStream, tmp)) {
        entries::Entry newEntry;
        newEntry.from_ussv(tmp);
        add_new_entry(newEntry);
    }
}

size_t Contacts::get_index_by_full_name_interactive(bool asianStyle) const {
    string fullName;
GET_NAME:
    cerr << "请输入姓名(部分或全部, 使用如#12这种语法直接输入索引, 输入!来取消)." << endl << ">>> ";
    getline(cin, fullName);
    if (fullName.size() == 0) {
        cerr << "您的输入有误, 请再试一次." << endl;
        goto GET_NAME;
    }
    if (fullName == "!") {
        cerr << "操作已取消." << endl;
        return size() + 1;
    }
    if (fullName[0] == '#') {
        auto tmpS = fullName.substr(1, fullName.length() - 1);
        stringstream tmpSStream(tmpS);
        int tmp = -1;
        tmpSStream >> tmp;
        if (tmp < 0 || size_t(tmp) >= size()) {
            cerr << "错误: 索引不合法." << endl;
            goto GET_NAME;
        }
        return size_t(tmp);
    }
    auto res = find_part('N', fullName);
    if (res.size() == 0) {
        cerr << "找不到任何这样的通讯录条目." << endl;
        goto GET_NAME;
    }
    if (res.size() == 1) {
        return *res.begin();
    }
    cerr << "有多个匹配的项, 如下:" << endl;
    cerr << "索引\t" << entries::Entry::get_csv_header(true, asianStyle, "\t") << endl;
    for (auto i : res) {
        cerr << i << "\t" << get_entry_const_ref(i).to_csv(true, asianStyle, "\t") << endl;
    }
    int tmp;
GET_INDEX:
    cerr << "请输入要操作的项的索引(输入负值来取消)." << endl << ">>> ";
    cin >> tmp;
    if (tmp < 0) {
        cerr << "操作已取消." << endl;
        return size() + 1;
    }
    if (!res.count(size_t(tmp))) {
        cerr << "错误: 索引不合法." << endl;
        goto GET_INDEX;
    }
    return size_t(tmp);
}
