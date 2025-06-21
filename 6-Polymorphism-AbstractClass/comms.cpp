/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-05-29 20:24:57
 * @LastEditTime: 2025-05-29 21:59:38
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /6-Polymorphism-AbstractClass/comms.cpp
 */
#include "comms.hpp"
#include "entries.hpp"
#include <cstddef>
#include <iostream>
void Comms::NewComms(void) {
    int cnt, t;
    AbstractEntry *newEntry;
    cout << "请输入条目个数: ";
    cin >> cnt;
    for (int i = 1; i <= cnt; i++) {
        cout << "=====  条目" << i << "  =====" << endl;
        cout << "输入条目类型(0: 普通; 1: 网友; 2: 朋友; 3: 同学; 4: 同学朋友): ";
        cin >> t;
        // 这里用个枚举更好, 但鉴于这是个教学目的实验,
        // 且相关知识已经在之前用过, 这里直接用数字了.
        switch (t) {
        case 0: {
            newEntry = new CommEntry;
            break;
        }
        case 1: {
            newEntry = new EFriendEntry;
            break;
        }
        case 2: {
            newEntry = new FriendEntry;
            break;
        }
        case 3: {
            newEntry = new ClassmateEntry;
            break;
        }
        case 4: {
            newEntry = new FriendClassmateEntry;
            break;
        }
        default: {
            cout << "错误类型, 请再次输入一次." << endl;
            i--;
            break;
        }
        }
        newEntry->input();
        entries.push_back(newEntry);
    }
}
void Comms::PrintComms(void) {
    for (size_t i = 0; i < entries.size(); i++) {
        cout << "=====  条目" << i + 1 << "  =====" << endl;
        entries[i]->output();
        cout << endl;
    }
}
Comms::~Comms() {
    for (auto x : entries) {
        delete x;
    }
}
void Comms::Find(void) {
    int t = -1, cnt = 0, idx = 0;
    string target;
    while (t != 0 && t != 1) {
        cout << "===== 查找 =====" << endl;
        cout << "查找方式(0: 靠名字找; 1: 靠号码找): ";
        cin >> t;
    }
    cout << "查找目标: ";
    cin >> target;
    string res;
    if (t == 0) {
        for (auto x : entries) {
            // 这里用到了RTTI.
            if (typeid(*x) == typeid(EFriendEntry)) {
                res = static_cast<EFriendEntry *>(x)->getSocialAppName();
            } else {
                res = static_cast<CommEntry *>(x)->getName();
            }
            if (res == target) {
                cnt++;
                cout << "===== 结果" << cnt << " [" << idx << "] =====" << endl;
                x->output();
                cout << endl;
            }
            idx++;
        }
    } else {
        for (auto x : entries) {
            if (typeid(*x) == typeid(EFriendEntry)) {
                res = static_cast<EFriendEntry *>(x)->getSocialAppId();
            } else {
                res = static_cast<CommEntry *>(x)->getTel();
            }
            if (res == target) {
                cnt++;
                cout << "===== 结果" << cnt << " [" << idx << "] =====" << endl;
                x->output();
                cout << endl;
            }
            idx++;
        }
    }
}
void Comms::Edit(void) {
    size_t idx;
    cout << "输入Index来修改条目. 不知道Index, 请先搜索(结果方括号中即是): ";
    cin >> idx;            // 这里在生产中需要进行检查(索引有效性)!
    entries[idx]->input(); // 这里生产中为了用户体验, 应该允许用户之修改部分, 但之前已经做过不少相关工作, 在此处略.
}
void Comms::SeparateDisplay(void) {
    vector<EFriendEntry *> efriends;
    vector<CommEntry *> traditional;
    EFriendEntry *tmp;
    for (auto ptr : entries) {
        tmp = dynamic_cast<EFriendEntry *>(ptr);
        tmp != nullptr ? efriends.push_back(tmp) : traditional.push_back(static_cast<CommEntry *>(ptr));
    }
    cout << "===== 网友 =====" << endl;
    for (auto x : efriends) {
        x->output();
    }
    cout << endl;
    cout << "===== 线下朋友 =====" << endl;
    for (auto x : traditional) {
        x->output();
    }
    cout << endl;
}
void Comms::ShowTypeInfo(void) {
    int cnt = 0;
    for (auto x : entries) {
        cnt++;
        cout << "条目" << cnt << "的类型是: " << typeid(*x).name() << endl;
    }
}
