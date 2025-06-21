/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-06-12 14:16:51
 * @LastEditTime: 2025-06-12 16:54:57
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /7-Friend-OperatorOverloading/main.cpp
 */

#include "comms.hpp"
using namespace std;
int main(void) {
    Comms comms("comms.log");
    cin >> comms;
    comms.NewEntry();
    comms.NewEntry();
    comms.ModEntry();
    comms.DelEntry();
    cout << comms;
    return 0;
}
