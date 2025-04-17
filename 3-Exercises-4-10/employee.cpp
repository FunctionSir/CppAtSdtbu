#include "employee.hpp"
#include <sstream>

employee::~employee() {
    total--;
}
int employee::count(void) {
    return total;
}
std::string employee::to_string(void) const {
    stringstream ss;
    ss << "ID: " << id << " 性别:" << (sex ? "男" : "女") << " 出生日期:" << birth_date.to_string() << " PIN: " << PIN;
    return ss.str();
}
void employee::from_string(string str) {
    stringstream ss(str);
    int y, m, d;
    ss >> id >> sex >> y >> m >> d >> PIN;
    birth_date = Date(y, m, d);
}
employee::employee(string Id, bool Sex, Date BirthDate, string Pin) {
    id = Id, sex = Sex, birth_date = BirthDate, PIN = Pin;
    total++;
};
