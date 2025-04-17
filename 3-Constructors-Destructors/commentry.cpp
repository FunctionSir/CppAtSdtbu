#include "commentry.hpp"
#include <algorithm>
#include <string>

void CommEntry::new_arrays(size_t s) {
    m_StrPtrTypes = new string[s];
    m_StrPtrNumbers = new string[s];
    m_SizeArrLen = s;
}

CommEntry::~CommEntry() {
    delete[] m_StrPtrTypes;
    delete[] m_StrPtrNumbers;
}

CommEntry::CommEntry(string name, string type, string phone) {
    m_StrName = name;
    new_arrays(1);
    m_StrPtrTypes[0] = type;
    m_StrPtrNumbers[0] = phone;
}

CommEntry::CommEntry(string name, string phone) {
    m_StrName = name;
    new_arrays(1);
    m_StrPtrTypes[0] = TYPE_PHONE;
    m_StrPtrNumbers[0] = phone;
}

CommEntry::CommEntry() {
    m_StrName = "";
    new_arrays(0);
}

CommEntry::CommEntry(string name, vector<pair<string, string>> &data) {
    m_StrName = name;
    new_arrays(data.size());
    size_t cur = 0;
    for (auto p : data) {
        m_StrPtrTypes[cur] = p.first;
        m_StrPtrNumbers[cur++] = p.second;
    }
}

CommEntry::CommEntry(string name, vector<array<string, 2>> &data) {
    m_StrName = name;
    new_arrays(data.size());
    size_t cur = 0;
    for (auto elem : data) {
        m_StrPtrTypes[cur] = elem[0];
        m_StrPtrNumbers[cur++] = elem[1];
    }
}

CommEntry::CommEntry(string csv) {
    // If only an empty string.
    if (csv.length() == 0) {
        m_StrName = "";
        new_arrays(1);
        return;
    }
    while (csv[0] == ',') {
        csv.erase(csv.begin());
    }
    while (csv[csv.length() - 1] == ',') {
        csv.pop_back();
    }
    auto pos = csv.begin() - 1;
    vector<string> parts;
    pos = find(pos + 1, csv.end(), ',');
    parts.push_back(csv.substr(0, size_t(pos - csv.begin())));
    auto oldpos = pos;
    if (pos != csv.end()) {
        do {
            pos = find(pos + 1, csv.end(), ',');
            parts.push_back(csv.substr(size_t(oldpos - csv.begin()) + 1, size_t(pos - oldpos) - 1));
            oldpos = pos;
        } while (pos != csv.end());
    }
    new_arrays((parts.size() - 1) / 2);
    m_StrName = parts[0];
    parts.erase(parts.begin());
    size_t cnt = 0, cur = 0;
    for (auto p : parts) {
        if (cnt % 2 == 0) {
            m_StrPtrTypes[cur] = p;
        } else {
            m_StrPtrNumbers[cur++] = p;
        }
        cnt++;
    }
}

size_t CommEntry::size() const {
    return m_SizeArrLen;
}

CommEntry::CommEntry(const CommEntry &origin) {
    m_StrName = origin.m_StrName;
    new_arrays(origin.m_SizeArrLen);
    for (size_t i = 0; i < origin.m_SizeArrLen; i++) {
        m_StrPtrTypes[i] = origin.m_StrPtrTypes[i];
        m_StrPtrNumbers[i] = origin.m_StrPtrNumbers[i];
    }
}

CommEntry::CommEntry(CommEntry &&old) {
    m_StrName = old.m_StrName;
    m_SizeArrLen = old.m_SizeArrLen;
    m_StrPtrTypes = old.m_StrPtrTypes;
    m_StrPtrNumbers = old.m_StrPtrNumbers;
    old.m_StrPtrTypes = NULL;
    old.m_StrPtrNumbers = NULL;
}

std::string CommEntry::set_name(string name) {
    string old_name = m_StrName;
    m_StrName = name;
    return old_name;
}

bool CommEntry::set_phone(size_t pos, string type, string number) {
    if (pos >= m_SizeArrLen) {
        return false;
    }
    m_StrPtrTypes[pos] = type;
    if (number != "") {
        m_StrPtrNumbers[pos] = number;
    }
    return true;
}

bool CommEntry::set_phone(size_t pos, string number) {
    if (pos >= m_SizeArrLen) {
        return false;
    }
    m_StrPtrNumbers[pos] = number;
    return true;
}

void CommEntry::append(string type, string number) {
    string *oldTypes = m_StrPtrTypes, *oldNums = m_StrPtrNumbers;
    new_arrays(m_SizeArrLen + 1);
    for (size_t i = 0; i < m_SizeArrLen - 1; i++) {
        m_StrPtrTypes[i] = oldTypes[i];
        m_StrPtrNumbers[i] = oldNums[i];
    }
    m_StrPtrTypes[m_SizeArrLen - 1] = type;
    m_StrPtrNumbers[m_SizeArrLen - 1] = number;
}

const std::string *CommEntry::get_numbers(void) const {
    return m_StrPtrNumbers;
}

const std::string *CommEntry::get_types(void) const {
    return m_StrPtrTypes;
}

const std::string &CommEntry::get_name(void) const {
    return m_StrName;
}
const std::string &CommEntry::get_type(size_t pos) const {
    return m_StrPtrTypes[pos];
}
const std::string &CommEntry::get_number(size_t pos) const {
    return m_StrPtrNumbers[pos];
}
CommEntry &CommEntry::operator=(const CommEntry &right) {
    m_StrName = right.m_StrName;
    new_arrays(right.m_SizeArrLen);
    for (size_t i = 0; i < right.m_SizeArrLen; i++) {
        m_StrPtrTypes[i] = right.m_StrPtrTypes[i];
        m_StrPtrNumbers[i] = right.m_StrPtrNumbers[i];
    }
    return *this;
}
