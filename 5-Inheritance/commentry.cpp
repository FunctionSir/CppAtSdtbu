#include "commentry.hpp"
#include <iostream>
void CommEntry::setName(string nm) {
    name = nm;
}
void CommEntry::setTel(string t) {
    tel = t;
}
void CommEntry::input(void) {
    // 此处鉴于是教学性质的实验, 故不做额外的如允许空格的输入或严格校验.
    // 但是生产环境中务必要进行相关的处理, 否则用户体验和程序鲁棒性都差.
    cout << "请输入姓名(不得包含空格): ";
    cin >> name;
    cout << "请输入电话(不得包含空格): ";
    cin >> tel;
}
std::string CommEntry::getTel(void) {
    return tel;
}
std::string CommEntry::getName(void) {
    return name;
}
void CommEntry::output(void) {
    cout << "姓名: " << name << endl;
    cout << "电话: " << tel << endl;
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
    cout << "CommEntry 构造!" << endl;
}
CommEntry::~CommEntry() {
    cout << "Comm Entry 析构!" << endl;
}
FriendEntry::FriendEntry(void) {
    cout << "Friend Entry 构造!" << endl;
}
FriendEntry::~FriendEntry(void) {
    cout << "Friend Entry 析构!" << endl;
}
ClassmateEntry::ClassmateEntry(void) {
    cout << "Classmate Entry 构造!" << endl;
}
ClassmateEntry::~ClassmateEntry() {
    cout << "Classmate Entry 析构!" << endl;
}
FriendClassmateEntry::FriendClassmateEntry(void) {
    cout << "Friend Classmate Entry 构造!" << endl;
}
FriendClassmateEntry::~FriendClassmateEntry() {
    cout << "Friend Classmate Entry 析构!" << endl;
}
