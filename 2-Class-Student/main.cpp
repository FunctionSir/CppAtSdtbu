/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-04 00:30:08
 * @LastEditTime: 2025-04-04 00:51:40
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /2-Class-Student/main.cpp
 */
#include "student.hpp"
#include <iostream>
using namespace std;
int main(void) {
    Student s("2023215566", "张三");
    cout << s.GetId() << " " << s.GetName() << " " << s.GetScore() << endl;
    s.ChangeScore(99.95);
    cout << s.GetScore() << endl;
    s.ChangeScore(99.955);
    cout << s.GetScore() << endl;
    s.ChangeScore(99.9999);
    cout << s.GetScore() << endl;
    s.ChangeScore(100.0);
    cout << s.GetScore() << endl;
    s.ChangeScore(100);
    cout << s.GetScore() << endl;
    return 0;
}
