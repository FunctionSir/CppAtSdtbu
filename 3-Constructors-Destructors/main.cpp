/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-17 14:12:55
 * @LastEditTime: 2025-04-17 20:12:42
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /3-Constructors-Destructors/main.cpp
 */
#include "commentry.hpp"
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
void print_data(CommEntry &entry) {
    cout << "姓名: " << entry.get_name() << endl;
    cout << "电话信息:" << endl;
    for (size_t i = 0; i < entry.size(); i++) {
        cout << "类型: " << entry.get_type(i) << " 号码: " << entry.get_number(i) << endl;
    }
    cout << endl;
}
int main(void) {
    cout << "通讯录条目类演示程序" << endl;
    cout << "缺省构造函数:" << endl;
    CommEntry a;
    print_data(a);
    cout << "参数化构造函数:" << endl;
    CommEntry b("张三,手机,13766332277,工作手机,12277663333,电话,0543-6555333,工作电话,0543-8822312");
    print_data(b);
    CommEntry c("李四", "13766663333");
    print_data(c);
    vector<pair<string, string>> tmp;
    tmp.push_back({"家庭电话", "0543-2222111"});
    tmp.push_back({"工作电话", "0543-1111111"});
    CommEntry d("王五", tmp);
    print_data(d);
    cout << "拷贝构造函数:" << endl;
    CommEntry e(b);
    print_data(e);
    cout << "重载赋值运算符:" << endl;
    a = b;
    print_data(a);
    cout << "更多内容, 请阅读代码." << endl;
}
