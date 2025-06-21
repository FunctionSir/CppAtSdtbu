// 仅供测试.
#include "comms.hpp"
using namespace std;
int main(void) {
    Comms comms;
    comms.NewComms();
    comms.PrintComms();
    comms.Find();
    comms.Edit();
    comms.SeparateDisplay();
    comms.ShowTypeInfo();
    return 0;
}
