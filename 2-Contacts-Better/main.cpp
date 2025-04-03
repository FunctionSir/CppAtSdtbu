/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-03-18 17:55:22
 * @LastEditTime: 2025-04-03 20:42:03
 * @LastEditors: FunctionSir
 * @Description: Contacts management.
 * @FilePath: /2-Contacts-Better/main.cpp
 */
#include "checkers.hpp"
#include "contacts.hpp"
#include "entries.hpp"
#include <csignal>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
using namespace std;
using namespace contacts;
using namespace entries;

Contacts *book;

const string DEFAULT_FILE = "data.ussv";

const bool ASIAN_STYLE = true;

string _; // Act as a blackhole.

inline void panic(string msg) {
    cerr << endl << "panic: " << msg << endl;
    exit(1);
}

// Cross-platform clear screen.
inline void clear_screen(void) {
#ifdef _WIN32 // For MS Windows.
    system("cls");
#else // For Linux, Mac, xBSD, UNIX and other.
    system("clear");
#endif
}

inline void create_if_not_exists(string path) {
    if (path == "") {
        panic("empty path provided");
    }
    if (!filesystem::exists(path)) {
        ofstream tmp(path);
        if (!tmp.is_open()) {
            panic("can not create file \"" + path + "\"");
        }
    }
}

inline char getOp(char &op) {
    cerr << ">>> ";
    if (cin >> op) {
        op = (char)toupper(op);
        return op;
    }
    panic("can not get operation");
    return EOF;
}

inline char showMenu(string &path_from_args) {
    static bool checkedPathFromArg = false;
    char op;
    if (!checkedPathFromArg) {
        if (path_from_args != "" && filesystem::exists(path_from_args)) {
            book = new Contacts;
            if (!book->load_from_file(path_from_args)) {
                delete book;
                book = NULL;
            }
        }
        checkedPathFromArg = true;
    }
    string path;
    if (book == NULL) {
    PRINT_PRE_OPEN_MENU:
        cerr << "=== [ 通讯录管理工具菜单 ] ===" << endl
             << "[O]pen 打开/新建文件" << endl
             << "[D]efault 使用默认文件" << endl
             << "[W]ipe 清屏" << endl
             << "[E]xit 退出" << endl;
    GET_INPUT:
        getOp(op);
        switch (op) {
        case 'O':
            getline(cin, _);
            cerr << "请输入路径: ";
            getline(cin, path);
            create_if_not_exists(path);
            book = new Contacts;
            book->load_from_file(path);
            break;
        case 'D':
            create_if_not_exists(DEFAULT_FILE);
            book = new Contacts;
            book->load_from_file(DEFAULT_FILE);
            break;
        case 'W':
            clear_screen();
            goto PRINT_PRE_OPEN_MENU;
        case 'E':
            cerr << "Goodbye!" << endl;
            exit(0);
        default:
            cerr << "无法识别您的命令! 请重试." << endl;
            goto GET_INPUT;
        }
        clear_screen();
    }
    if (!book->is_loaded()) {
        delete book;
        book = NULL;
        goto PRINT_PRE_OPEN_MENU;
    }
    cerr << "=== [ 通讯录管理工具菜单 ] ===" << endl
         << "当前文件: " << book->file_path() << endl
         << "[N]ew 新建通讯录条目" << endl
         << "[M]od 修改通讯录条目" << endl
         << "[D]el 删除通讯录条目" << endl
         << "[F]ind 查找通讯录条目" << endl
         << "[L]ist 列出所有条目" << endl
         << "[W]ipe 清屏" << endl
         << "[S]ave 立即保存文件(但不关闭)" << endl
         << "[E]xport 导出该通讯录" << endl
         << "[C]lose 关闭本通讯录" << endl
         << "Tips: 通过查找可以得知您想要的记录的索引." << endl
         << "Tips: 这些索引适用于您想要修改或是删除时." << endl;
    return getOp(op);
}

inline void find_menu(void) {
    char findBy, method;
    string target;
    cerr << "=== [ 通讯录条目搜索菜单 ] ===" << endl
         << "选择搜索依据:" << endl
         << "[L] 姓氏" << endl
         << "[F] 名字" << endl
         << "[N] 全名(慢)" << endl
         << "[P] 手机号" << endl
         << "[T] 座机号" << endl
         << "[E] 电子邮件地址" << endl
         << "[G] 组号" << endl;
GET_OP:
    getOp(findBy);
    string tmp = "LFNPTEG";
    if (tmp.find(findBy) >= tmp.length()) {
        cerr << "您的输入有问题, 请重新输入." << endl;
        goto GET_OP;
    }
    cerr << "请输入查找字符串(普通文本或正则表达式, 不含空格): ";
    cin >> target;
    cerr << "选择匹配方式:" << endl
         << "[F] 完全匹配(快, 对全名除外)" << endl
         << "[P] 部分匹配" << endl
         << "[R] 正则表达式" << endl;
GET_METHOD:
    getOp(method);
    set<size_t> res;
    switch (method) {
    case 'F':
        res = book->find_full(findBy, target);
        break;
    case 'P':
        res = book->find_part(findBy, target);
        break;
    case 'R':
        res = book->find_regex(findBy, target);
        break;
    default:
        cerr << "您的输入有问题, 请重新输入." << endl;
        goto GET_METHOD;
    }
    book->cout_by_res_set(res, ASIAN_STYLE);
}

inline void mod_menu(void) {
    getline(cin, _);
    size_t targetIndex = book->get_index_by_full_name_interactive(ASIAN_STYLE);
    if (targetIndex == book->size() + 1) {
        return;
    }
    const Entry &ref = book->get_entry_const_ref(targetIndex);
    cerr << "=== [ 通讯录条目修改菜单 ] ===" << endl
         << "选中条目的索引: " << targetIndex << endl
         << "[F] 修改名字" << endl
         << "[L] 修改姓氏" << endl
         << "[P] 修改手机号" << endl
         << "[T] 修改座机号" << endl
         << "[E] 修改电邮" << endl
         << "[G] 修改所在组" << endl
         << "[N] 修改备注" << endl;
    char op;
    string target;
    getOp(op);
    switch (op) {
    case 'F':
        cout << "原名字: " << ref.FirstName << endl;
        cerr << "输入新名字: ";
        getline(cin, _);
        getline(cin, target);
        book->mod_entry(targetIndex, op, target);
        break;
    case 'L':
        cout << "原姓氏: " << ref.LastName << endl;
        cerr << "输入新姓氏: ";
        getline(cin, _);
        getline(cin, target);
        book->mod_entry(targetIndex, op, target);
        break;
    case 'P':
        cout << "原手机号: " << ref.Phone << endl;
    NEW_PHONE:
        cerr << "输入新手机号: ";
        getline(cin, _);
        getline(cin, target);
        if (!chk_phone(target)) {
            cerr << "您的输入有问题, 请重新输入.";
            goto NEW_PHONE;
        }
        book->mod_entry(targetIndex, op, target);
        break;
    case 'T':
        cout << "原座机号: " << ref.Tel << endl;
    NEW_TEL:
        cerr << "输入新座机号: ";
        getline(cin, _);
        getline(cin, target);
        if (!chk_tel(target)) {
            cerr << "您的输入有问题, 请重新输入.";
            goto NEW_TEL;
        }
        book->mod_entry(targetIndex, op, target);
        break;
    case 'E':
        cout << "原电邮: " << ref.Email << endl;
    NEW_EMAIL:
        cerr << "输入新电邮: ";
        getline(cin, _);
        getline(cin, target);
        if (!chk_email(target)) {
            cerr << "您的输入有问题, 请重新输入.";
            goto NEW_EMAIL;
        }
        book->mod_entry(targetIndex, op, target);
        break;
    case 'G':
        cout << "原所在组: " << ref.Group << endl;
        cerr << "输入新所在组: ";
        getline(cin, _);
        getline(cin, target);
        book->mod_entry(targetIndex, op, target);
        break;
    case 'N':
        cout << "原备注: " << ref.Note << endl;
        cerr << "输入新备注: ";
        getline(cin, _);
        getline(cin, target);
        book->mod_entry(targetIndex, op, target);
        break;
    }
}

inline void export_menu(void) {
    string target;
    cerr << "输入目标文件: ";
    getline(cin, target);
    if (filesystem::exists(target)) {
        cerr << "文件已存在! 继续会覆盖或删除原有文件! 是否要继续?" << endl;
        cerr << "要继续, 输入\"YES\"(全大写), 否则输入其他不含空格的字符串: ";
        string tmp;
        cin >> tmp;
        if (tmp != "YES") {
            cerr << "操作已取消." << endl;
            return;
        }
    }
    ofstream outStream(target);
    if (!outStream.is_open()) {
        cerr << "无法打开目标文件! 请检查权限等." << endl;
        return;
    }
    cerr << "=== [ 通讯录导出菜单 ] ===" << endl
         << "导出到文件: " << target << endl
         << "[C] 导出为CSV电子表格格式" << endl
         << "[T] 导出为TSV电子表格格式(更推荐)" << endl
         << "[U] 导出为此程序的专有格式USSV(相当于另存为)" << endl
         << "[E] 取消导出" << endl;
    char op;
GET_OP:
    getOp(op);
    switch (op) {
    case 'C':
        book->export_to_csv(true, ASIAN_STYLE, ",", outStream);
        break;
    case 'T':
        book->export_to_csv(true, ASIAN_STYLE, "\t", outStream);
        break;
    case 'U':
        book->save_as(outStream);
        break;
    case 'E':
        filesystem::remove(target); // Clean gened file.
        cerr << "操作已取消." << endl;
        return;
    default:
        cerr << "您的输入有问题, 请重试.";
        goto GET_OP;
    }
}

inline void list_menu(void) {
    char sortBy;
    char order;
    cerr << "=== [ 通讯录条目列出菜单 ] ===" << endl
         << "选择排序依据:" << endl
         << "[L] 姓氏" << endl
         << "[F] 名字" << endl
         << "[P] 手机号" << endl
         << "[T] 座机号" << endl
         << "[E] 电子邮件地址" << endl
         << "[G] 组号" << endl;
GET_OP:
    getOp(sortBy);
    string tmp = "LFPTEG";
    if (tmp.find(sortBy) >= tmp.length()) {
        cerr << "您的输入有问题, 请重新输入." << endl;
        goto GET_OP;
    }
GET_ASC_DESC:
    cerr << "选择升序降序:" << endl << "[A] 升序" << endl << "[D] 降序" << endl;
    getOp(order);
    if (order != 'A' && order != 'D') {
        cerr << "您的输入有问题, 请重新输入." << endl;
        goto GET_ASC_DESC;
    }
    book->list_to_cout(sortBy, order == 'D', ASIAN_STYLE);
}

inline void del_menu(void) {
    string fullName;
    getline(cin, _);
    size_t tmp = book->get_index_by_full_name_interactive(ASIAN_STYLE);
    if (tmp == book->size() + 1) {
        return;
    }
    book->delete_entry(size_t(tmp));
}

// Handel SIGINT to avoid data loss caused by pressed Ctrl+C accidently.
void sigint_handler(int) {
    cerr << endl << "收到了终止信号!" << endl;
    if (book != NULL) {
        book->flush();
        cerr << "已为您自动保存了您先前的修改." << endl;
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, sigint_handler);
    string path_from_args = "";
    if (argc >= 2) {
        path_from_args = argv[1];
    }
    char cont;
    while (true) {
        switch (showMenu(path_from_args)) {
        case 'N':
        NEW_ENTRY:
            book->new_from_cin_interactive();
            cerr << "继续新增么?" << endl << "[Y] 继续" << endl << "[N] 结束" << endl;
        GET_OP:
            getOp(cont);
            switch (cont) {
            case 'Y':
                goto NEW_ENTRY;
            case 'N':
                break;
            default:
                cerr << "您的输入有问题, 请重新输入." << endl;
                goto GET_OP;
            }
            break;
        case 'F':
            find_menu();
            break;
        case 'M':
            mod_menu();
            break;
        case 'D':
            del_menu();
            break;
        case 'L':
            list_menu();
            break;
        case 'W':
            clear_screen();
            break;
        case 'S':
            book->flush();
            break;
        case 'E':
            getline(cin, _);
            export_menu();
            break;
        case 'C':
            delete book;
            book = NULL;
            break;
        default:
            cerr << "无效命令, 请重试." << endl;
        }
    }
}
