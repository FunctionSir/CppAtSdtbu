/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-03-18 17:56:27
 * @LastEditTime: 2025-03-20 15:07:35
 * @LastEditors: FunctionSir
 * @Description: Contacts related.
 * @FilePath: /CppAtSdtbu/1-Contacts/contacts.cpp
 */
#include "entries.cpp"
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>
#ifndef __CONTACTS_CPP_INCLUDED__
#define __CONTACTS_CPP_INCLUDED__
// Namespace of contacts.
namespace contacts {
using namespace std;
class Contacts { // Class Contacts
  public:
    Contacts() {
        Loaded = false;
    }

    Contacts(string filePath) {
        load_from_file(filePath);
    }

    // Flush before object destroyed.
    ~Contacts() {
        if (Loaded) {
            flush();
        }
    }

    bool flush() {
        ofstream fileStream(FilePath);
        if (!fileStream.is_open()) {
            return false;
        }
        save_as(fileStream);
        return true;
    }

    // Load from USSV file
    bool load_from_file(string filePath) {
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

    bool is_loaded() {
        return Loaded;
    }

    string file_path() {
        return FilePath;
    }

    // List all entries to stdout.
    void list_to_cout(bool asianStyle) {
        cout << "索引\t"
             << entries::Entry::get_csv_header(true, asianStyle, "\t", "\n");
        int curIndex = 0;
        for (auto e : Entries) {
            cout << curIndex << "\t" << e.to_csv(true, asianStyle, "\t", "\n");
            curIndex++;
        }
        cout << "条目总数: " << Entries.size() << endl;
    }

    // Export to CSV.
    void export_to_csv(bool useFullName, bool asianStyle, string separator,
                       ofstream &outStream) {
        outStream << entries::Entry::get_csv_header(useFullName, asianStyle,
                                                    separator, "\n");
        for (auto e : Entries) {
            outStream << e.to_csv(useFullName, asianStyle, separator, "\n");
        }
        cout << "导出的条目总数: " << Entries.size() << endl;
    }

    void save_as(ofstream &outStream) {
        for (auto e : Entries) {
            outStream << e.to_ussv("\n");
        }
        outStream.close();
    }

    // Add new entry from cin, interactive.
    void new_from_cin_interactive() {
        entries::Entry newEntry;
        newEntry.from_cin_interactive();
        add_new_entry(newEntry);
    }

    set<size_t> find_full(char by, string &target) {
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
                if ((flg ? Entries[i].get_asian_full_name()
                         : Entries[i].get_en_full_name()) == target) {
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

    set<size_t> find_part(char by, string &target) {
        set<size_t> result;
        bool flg = 0;
        switch (by) {
        case 'L':
            for (size_t i = 0; i < Entries.size(); i++) {
                if (Entries[i].LastName.find(target) <
                    Entries[i].LastName.length()) {
                    result.insert(i);
                }
            }
            return result;
        case 'F':
            for (size_t i = 0; i < Entries.size(); i++) {
                if (Entries[i].FirstName.find(target) <
                    Entries[i].FirstName.length()) {
                    result.insert(i);
                }
            }
            return result;
        case 'N':
            if (target.find(' ') >= target.size()) {
                flg = 1; // No space, an asian name.
            }
            for (size_t i = 0; i < Entries.size(); i++) {
                string tmp = (flg ? Entries[i].get_asian_full_name()
                                  : Entries[i].get_en_full_name());
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

    set<size_t> find_regex(char by, string &target) {
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
                string tmp = (flg ? Entries[i].get_asian_full_name()
                                  : Entries[i].get_en_full_name());
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

    void cout_by_res_set(set<size_t> &res, bool asianStyle) {
        cout << "索引\t"
             << entries::Entry::get_csv_header(true, asianStyle, "\t", "\n");
        for (auto i : res) {
            cout << i << "\t"
                 << Entries[i].to_csv(true, asianStyle, "\t", "\n");
        }
        cout << "条目总数: " << res.size() << endl;
    }

    void delete_entry(size_t index) {
        entries::Entry &targetEntry = Entries[index];
        ByFirstName[targetEntry.FirstName].erase(index);
        ByLastName[targetEntry.LastName].erase(index);
        ByPhone[targetEntry.Phone].erase(index);
        ByTel[targetEntry.Tel].erase(index);
        ByEmail[targetEntry.Email].erase(index);
        ByGroup[targetEntry.Group].erase(index);
        Entries.erase(Entries.begin() + long(index));
    }

    const entries::Entry &get_entry_const_ref(size_t index) {
        return Entries[index];
    }

    bool mod_entry(size_t index, char part, string &data) {
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
            if (!entries::Entry::chk_phone(data)) {
                return false;
            }
            ByPhone[Entries[index].Phone].erase(index);
            Entries[index].Phone = data;
            ByPhone[Entries[index].Phone].insert(index);
            break;
        case 'T':
            if (!entries::Entry::chk_tel(data)) {
                return false;
            }
            ByTel[Entries[index].Tel].erase(index);
            Entries[index].Tel = data;
            ByTel[Entries[index].Tel].insert(index);
            break;
        case 'E':
            if (!entries::Entry::chk_email(data)) {
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

    size_t size(void) {
        return Entries.size();
    }

  private:
    string FilePath;
    bool Loaded;
    vector<entries::Entry> Entries;
    map<string, set<size_t>> ByFirstName;
    map<string, set<size_t>> ByLastName;
    map<string, set<size_t>> ByPhone;
    map<string, set<size_t>> ByTel;
    map<string, set<size_t>> ByEmail;
    map<string, set<size_t>> ByGroup;
    void add_new_entry(entries::Entry &newEntry) {
        Entries.push_back(newEntry);
        ByFirstName[newEntry.FirstName].insert(Entries.size() - 1);
        ByLastName[newEntry.LastName].insert(Entries.size() - 1);
        ByPhone[newEntry.Phone].insert(Entries.size() - 1);
        ByTel[newEntry.Tel].insert(Entries.size() - 1);
        ByEmail[newEntry.Email].insert(Entries.size() - 1);
        ByGroup[newEntry.Group].insert(Entries.size() - 1);
    }
    void load_from_file(ifstream &fileStream) {
        string tmp;
        while (getline(fileStream, tmp)) {
            entries::Entry newEntry;
            newEntry.from_ussv(tmp);
            add_new_entry(newEntry);
        }
    }
};
} // namespace contacts
#endif
