/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-04 00:14:11
 * @LastEditTime: 2025-04-04 00:51:10
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /2-Class-Student/student.cpp
 */
#include "student.hpp"
#include <cmath>
#include <stdexcept>

Student::Student(string id, string name, double score) {
    ChangeId(id);
    ChangeName(name);
    ChangeScore(score);
}

void Student::ChangeId(string id) {
    if (id == "") {
        throw invalid_argument("id is empty");
        return;
    }
    priv_id = id;
}

void Student::ChangeName(string name) {
    if (name == "") {
        throw invalid_argument("name is empty");
        return;
    }
    priv_name = name;
}

void Student::ChangeScore(double score) {
    if (score < 0) {
        throw invalid_argument("score is negative");
        return;
    }
    if (score > 100) {
        throw invalid_argument("score larger than 100");
        return;
    }
    priv_score = static_cast<short>(round(score * 100));
}

void Student::ChangeScore(int score) {
    if (score < 0) {
        throw invalid_argument("score is negative");
        return;
    }
    if (score > 100) {
        throw invalid_argument("score larger than 100");
        return;
    }
    priv_score = static_cast<short>(score * 100);
}

std::string Student::GetId(void) {
    return priv_id;
}

std::string Student::GetName(void) {
    return priv_name;
}

double Student::GetScore(void) {
    return priv_score / 100.0;
}
