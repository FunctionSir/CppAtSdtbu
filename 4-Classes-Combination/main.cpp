/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-17 14:12:55
 * @LastEditTime: 2025-05-15 15:15:37
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /4-Classes-Combination/main.cpp
 */
#include "commentry.hpp"
#include "comms.hpp"
#include <cstddef>
#include <iostream>
using namespace std;
void print_data(const CommEntry &entry) {
    cout << "姓名: " << entry.get_name() << endl;
    cout << "电话信息:" << endl;
    for (size_t i = 0; i < entry.size(); i++) {
        cout << "类型: " << entry.get_type(i) << " 号码: " << entry.get_number(i) << endl;
    }
}
int main(void) {
    cout << CommEntry::get_tot_entries_cnt();
    cout << "通讯录类演示程序" << endl;
    Comms comms("test.in");
    cout << "输出容量: " << comms.capacity() << endl;
    const Comms &inMutComms = comms;
    cout << "查询王五: " << endl;
    print_data(inMutComms.get(inMutComms.find("王五", Comms::FindBy::Name)));
    comms.push_back(CommEntry("光头强,伐木电话,13366768881"));
    cout << "查询光头强: " << endl;
    print_data(inMutComms.get(inMutComms.find("13366768881", Comms::FindBy::Number)));
    cout << "输出个数: " << comms.size() << endl;
    cout << "输出当前CommEntry总量: " << CommEntry::get_tot_entries_cnt() << endl;
    CommEntry x("TESTX"), y("TESTY"), z("TESTZ");
    cout << "输出当前CommEntry总量: " << CommEntry::get_tot_entries_cnt() << endl;
    comms.order();
    comms.save("test.out");
    Comms left;
    cout << "测试赋值:" << endl;
    left = comms;
    left.push_back(CommEntry("不存在"));
    cout << "验证赋值:" << endl;
    cout << (left.find("不存在", Comms::FindBy::Name) != left.size()) << endl;
    cout << (comms.find("不存在", Comms::FindBy::Name) != comms.size()) << endl;
    cout << "更多内容, 请阅读代码." << endl;
}
