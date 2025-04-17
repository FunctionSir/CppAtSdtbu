/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-17 20:33:32
 * @LastEditTime: 2025-04-17 20:41:59
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /CppAtSdtbu/3-Example-4-2/main.cpp
 */
#include <iostream>
using namespace std;
class Point {
  public:
    Point(int xx = 0, int yy = 0) {
        X = xx;
        Y = yy;
    }
    Point(Point &p);
    int GetX() {
        return X;
    }
    int GetY() {
        return Y;
    }

  private:
    int X, Y;
};

Point::Point(Point &p) {
    X = p.X;
    Y = p.Y;
    cout << "copy constructor is called" << endl;
}

void fun1(Point p) {
    cout << p.GetX() << endl;
}

Point fun2() {
    Point A(1, 2);
    return A;
}

int main() {
    Point A(4, 5);
    Point B(A);

    cout << B.GetX() << endl;
    fun1(B);

    B = fun2();

    cout << B.GetX() << endl;
    return 0;
}
