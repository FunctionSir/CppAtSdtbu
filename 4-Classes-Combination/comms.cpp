/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-05-14 21:51:46
 * @LastEditTime: 2025-05-15 15:20:33
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /4-Classes-Combination/comms.cpp
 */

#include "comms.hpp"
#include "commentry.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>

void Comms::push_back(const CommEntry &entry) {
    if (m_count + 1 > m_max_count) {
        CommEntry *new_arr = new CommEntry[m_max_count + 1];
        if (new_arr == nullptr) {
            throw runtime_error("can not create new array");
        }
        comms_copy(new_arr, m_entries, m_count);
        delete[] m_entries;
        m_entries = new_arr;
        m_max_count++;
    }
    m_entries[m_count++] = entry;
}

Comms::~Comms() {
    delete[] m_entries;
}

Comms::Comms(size_t cnt) {
    m_entries = new CommEntry[cnt];
    if (m_entries == nullptr) {
        throw runtime_error("can not create new array");
    }
    m_max_count = cnt;
    m_count = 0;
}

Comms::Comms() {
    m_entries = nullptr;
    m_max_count = 0;
    m_count = 0;
}

void Comms::comms_copy(CommEntry *dst, CommEntry *src, size_t cnt) {
    for (size_t i = 0; i < cnt; i++) {
        dst[i] = src[i];
    }
}

size_t Comms::find(string target, FindBy findBy) const {
    switch (findBy) {
    case FindBy::Name: {
        for (size_t i = 0; i < m_count; i++) {
            if (m_entries[i].get_name() == target) {
                return i;
            }
        }
        break;
    }
    case FindBy::Number: {
        for (size_t i = 0; i < m_count; i++) {
            for (size_t j = 0; j < m_entries[i].size(); j++) {
                if (m_entries[i].get_number(j) == target) {
                    return i;
                }
            }
        }
        break;
    }
    default:
        throw out_of_range("unknown method");
    }
    return m_count;
}

const CommEntry &Comms::get(size_t pos) const {
    if (pos >= m_count) {
        throw out_of_range("pos out of range");
    }
    return m_entries[pos];
}

CommEntry &Comms::get_mut(size_t pos) {
    if (pos >= m_count) {
        throw out_of_range("pos out of range");
    }
    return m_entries[pos];
}

void Comms::shrink(void) {
    if (m_max_count == m_count) {
        return;
    }
    CommEntry *tmp = new CommEntry[m_count];
    if (tmp == nullptr) {
        throw runtime_error("can not create new array");
    }
    comms_copy(tmp, m_entries, m_count);
    delete[] m_entries;
    m_entries = tmp;
    m_max_count = m_count;
}

size_t Comms::capacity(void) {
    return m_max_count;
}

size_t Comms::size(void) {
    return m_count;
}

void Comms::reserve(size_t cap) {
    if (cap < m_count) {
        throw out_of_range("new capacity too small");
    }
    CommEntry *tmp = new CommEntry[cap];
    if (tmp == nullptr) {
        throw out_of_range("can not create new array");
    }
    m_max_count = cap;
    m_entries = tmp;
}

void Comms::erase(size_t pos) {
    m_count--;
    for (size_t i = pos; i < m_count; i++) {
        m_entries[i] = m_entries[i + 1];
    }
}
bool Comms::cmp_asc(const CommEntry &a, const CommEntry &b) {
    return a.get_name() < b.get_name();
}
bool Comms::cmp_desc(const CommEntry &a, const CommEntry &b) {
    return a.get_name() > b.get_name();
}

void Comms::order(bool desc) {
    sort(m_entries, m_entries + m_count, desc ? cmp_desc : cmp_asc);
}

void Comms::save(string path) {
    ofstream ofs(path);
    if (!ofs.is_open()) {
        throw runtime_error("can not open specified file");
    }
    ofs << m_max_count << endl;
    ofs << m_count << endl;
    for (size_t i = 0; i < m_count; i++) {
        ofs << m_entries[i].to_csv() << endl;
    }
    ofs.close();
}

void Comms::load(string path) {
    if (m_entries != nullptr) {
        delete[] m_entries;
    }
    string tmp;
    ifstream ifs(path);
    if (!ifs.is_open()) {
        throw runtime_error("can not open specified file");
    }
    ifs >> m_max_count >> m_count;
    m_entries = new CommEntry[m_max_count];
    if (m_entries == nullptr) {
        throw runtime_error("can not create new array");
    }
    getline(ifs, tmp);
    for (size_t i = 0; i < m_count; i++) {
        getline(ifs, tmp);
        m_entries[i] = CommEntry(tmp);
    }
}

Comms::Comms(string path) {
    m_entries = nullptr;
    load(path);
}
Comms::Comms(const Comms &origin) {
    comms_obj_copy(this, origin);
}
Comms &Comms::operator=(const Comms &origin) {
    comms_obj_copy(this, origin);
    return *this;
}
void Comms::comms_obj_copy(Comms *dest, const Comms &origin) {
    dest->m_max_count = origin.m_max_count;
    dest->m_count = origin.m_count;
    dest->m_entries = new CommEntry[dest->m_max_count];
    comms_copy(dest->m_entries, origin.m_entries, dest->m_count);
}
