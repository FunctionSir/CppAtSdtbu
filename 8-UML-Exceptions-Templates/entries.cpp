#include "entries.hpp"
#include <iostream>
#include <ostream>
void CommEntry::setName(string nm) {
    m_name = nm;
}
void CommEntry::setTel(string t) {
    for (auto ch : t) {
        if (!((ch >= '0' && ch <= '9') || ch == '-' || ch == '*' || ch == '_')) {
            throw InvalidPhoneException();
        }
    }
    m_tel = t;
}
void CommEntry::input(void) {
    // 此处鉴于是教学性质的实验, 故不做额外的如允许空格的输入或严格校验.
    // 但是生产环境中务必要进行相关的处理, 否则用户体验和程序鲁棒性都差.
    cout << "请输入姓名(不得包含空格): ";
    cin >> m_name;
    string tmp_tel;
    cout << "请输入电话(不得包含空格): ";
    cin >> tmp_tel;
    setTel(tmp_tel);
}
std::string CommEntry::getTel(void) const {
    return m_tel;
}
std::string CommEntry::getName(void) const {
    return m_name;
}
void CommEntry::output(void) {
    cout << "姓名: " << m_name << endl;
    cout << "电话: " << m_tel << endl;
}
void FriendEntry::input(void) {
    CommEntry::input();
    cout << "请输入地址(不包括空格): ";
    cin >> addr;
}
void FriendEntry::output(void) {
    CommEntry::output();
    cout << "地址: " << addr << endl;
}
ostream &CommEntry::output(ostream &os) {
    os << "姓名: " << m_name << endl;
    os << "电话: " << m_tel << endl;
    return os;
}
ostream &FriendEntry::output(ostream &os) {
    CommEntry::output();
    os << "地址: " << addr << endl;
    return os;
}
std::string FriendEntry::getAddr(void) {
    return addr;
}
void FriendEntry::setAddr(string a) {
    addr = a;
}
void ClassmateEntry::input(void) {
    CommEntry::input();
    cout << "请输入学校: ";
    cin >> school;
    cout << "请输入班级: ";
    cin >> stuclass;
    cout << "请输入家庭地址: ";
    cin >> addr;
}
void ClassmateEntry::output(void) {
    CommEntry::output();
    cout << "学校: " << school << endl;
    cout << "班级: " << stuclass << endl;
    cout << "家庭住址: " << addr << endl;
}
ostream &ClassmateEntry::output(ostream &os) {
    CommEntry::output();
    os << "学校: " << school << endl;
    os << "班级: " << stuclass << endl;
    os << "家庭住址: " << addr << endl;
    return os;
}
void ClassmateEntry::setAddr(string a) {
    addr = a;
}
void ClassmateEntry::setClass(string c) {
    stuclass = c;
}
void ClassmateEntry::setSchool(string s) {
    school = s;
}
void FriendClassmateEntry::input(void) {
    ClassmateEntry::input();
}
void FriendClassmateEntry::output(void) {
    ClassmateEntry::output();
}
ostream &FriendClassmateEntry::output(ostream &os) {
    return ClassmateEntry::output(os);
}
std::string ClassmateEntry::getAddr(void) {
    return addr;
}
std::string ClassmateEntry::getClass(void) {
    return stuclass;
}
std::string ClassmateEntry::getSchool(void) {
    return school;
}
CommEntry::CommEntry(void) {
    // cout << "CommEntry 构造!" << endl;
}
CommEntry::~CommEntry() {
    // cout << "Comm Entry 析构!" << endl;
}
FriendEntry::FriendEntry(void) {
    // cout << "Friend Entry 构造!" << endl;
}
FriendEntry::~FriendEntry(void) {
    // cout << "Friend Entry 析构!" << endl;
}
ClassmateEntry::ClassmateEntry(void) {
    // cout << "Classmate Entry 构造!" << endl;
}
ClassmateEntry::~ClassmateEntry() {
    // cout << "Classmate Entry 析构!" << endl;
}
FriendClassmateEntry::FriendClassmateEntry(void) {
    // cout << "Friend Classmate Entry 构造!" << endl;
}
FriendClassmateEntry::~FriendClassmateEntry() {
    // cout << "Friend Classmate Entry 析构!" << endl;
}
void EFriendEntry::input(void) {
    cout << "输入社交APP: ";
    cin >> social_app;
    cout << "输入网名: ";
    cin >> social_app_name;
    cout << "输入社交媒体账号: ";
    cin >> social_app_id;
}
void EFriendEntry::output(void) {
    cout << "社交APP: " << social_app << endl;
    cout << "网名: " << social_app_name << endl;
    cout << "社交账号: " << social_app_id << endl;
}
ostream &EFriendEntry::output(ostream &os) {
    os << "社交APP: " << social_app << endl;
    os << "网名: " << social_app_name << endl;
    os << "社交账号: " << social_app_id << endl;
    return os;
}
AbstractEntry::~AbstractEntry(void) {
    // cout << "Abstract Entry 析构!" << endl;
};
std::string EFriendEntry::getSocialAppName(void) {
    return social_app_name;
}
std::string EFriendEntry::getSocialAppId(void) {
    return social_app_id;
}
CommEntry::CommEntry(string n) {
    m_name = n;
}
FriendEntry::FriendEntry(string name) {
    setName(name);
}
const char *bad_pointer_cast::what(void) const noexcept {
    return error.c_str();
}
bad_pointer_cast::bad_pointer_cast(const char *s) {
    error = s;
}
bad_pointer_cast::bad_pointer_cast(string s) {
    error = s;
}
bad_pointer_cast::bad_pointer_cast() {
    error = "can not cast given pointer safely";
}
InvalidPhoneException::InvalidPhoneException(char *err) : out_of_range(err) {
}
InvalidPhoneException::InvalidPhoneException(string err) : out_of_range(err) {
}
InvalidPhoneException::InvalidPhoneException() : out_of_range("invalid phone number") {
}
