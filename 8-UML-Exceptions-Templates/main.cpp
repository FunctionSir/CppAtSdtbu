/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-06-16 15:01:31
 * @LastEditTime: 2025-06-20 08:08:24
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /8-UML-Exceptions-Templates/main.cpp
 */
#include "comms.hpp"
#include "entries.hpp"
#include <algorithm>
#include <list>
#include <vector>
using namespace std;
int main(void) {
    vector<CommEntry> vec;
    list<FriendEntry> lst;
    vec.push_back(CommEntry("张三"));
    vec.push_back(CommEntry("李四"));
    vec.push_back(CommEntry("王五"));
    lst.push_back(FriendEntry("张三"));
    lst.push_back(FriendEntry("李四"));
    lst.push_back(FriendEntry("王五"));
    FindEntry(vec, "张三")->output();
    FindEntry(lst, "张三")->output();
    Comms c;
    c.AddBatch();
    c.Export("test.out");
    c.Import("test.out");
    c.PrintComms();
    // find_if + Lambda表达式查找第一个名字中含有"张"的人.
    auto it =
        find_if(vec.begin(), vec.end(), [](const auto &entry) { return entry.getName().find("张") != string::npos; });
    if (it != vec.end()) {
        it->output();
    } else {
        cout << "找不到满足条件的条目!" << endl;
    }
    return 0;
}
