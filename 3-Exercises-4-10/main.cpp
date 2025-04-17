/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-17 20:44:58
 * @LastEditTime: 2025-04-17 21:48:44
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /CppAtSdtbu/3-Exercises-4-10/main.cpp
 */

#include "date.hpp"
#include "employee.hpp"
#include <iostream>

using namespace std;

int employee::total(0);

int main(void) {
    cout << "员工类演示程序" << endl;
    employee e("001", false, Date(2000, 5, 1), "123456");
    cout << e.to_string() << endl;
    e.from_string("001 1 2001 01 03 012345");
    employee *tmp = new employee;
    cout << e.to_string() << endl;
    cout << "Total: " << employee::count() << endl;
    delete tmp;
    cout << "Total: " << employee::count() << endl;
}
