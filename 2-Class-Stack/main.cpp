/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-03 22:01:21
 * @LastEditTime: 2025-04-04 00:08:19
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /2-Class-Stack/main.cpp
 */
#include "stack.hpp"
#include <iostream>
#include <vector>
using namespace std;
int main(void) {
    Stack<int> x(2);
    Stack<vector<int>> y(2);
    vector<int> tmpVec({1, 2, 3});
    Stack<int> z(tmpVec, 3);
    x.push(1);
    x.push(2);
    cout << x.top() << endl;
    x.pop();
    cout << x.top() << endl;
    x.pop();
    y.push({1, 2, 3});
    y.push({4, 5, 6});
    for (auto elem : y.top()) {
        cout << elem << " ";
    }
    cout << endl;
    y.pop();
    for (auto elem : y.top()) {
        cout << elem << " ";
    }
    cout << endl;
    y.pop();
    cout << z.top() << endl;
    z.pop();
    cout << z.top() << endl;
    z.pop();
    cout << z.top() << endl;
    z.pop();
}
