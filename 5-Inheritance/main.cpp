#include "commentry.hpp"
#include <iostream>

int main(void) {
    FriendEntry x;
    x.input();
    x.output();
    FriendClassmateEntry y;
    y.input();
    cout << "家庭住址: " << y.getAddr() << endl;
    CommEntry *pce;
    pce = &y;
    pce->output();
}
