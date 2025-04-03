/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-03 20:57:29
 * @LastEditTime: 2025-04-04 00:09:42
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /2-Class-Stack/stack.hpp
 */
#ifndef __STACK_HPP_INCLUDED__
#define __STACK_HPP_INCLUDED__
#include <cstddef>
#include <stdexcept>
#include <vector>
template <typename T> class Stack {
  public:
    Stack<T>(size_t size) {
        priv_data = new T[size];
        priv_size = size;
        priv_top = 0;
    }

    Stack<T>(std::vector<T> &vec) {
        priv_data = new T[vec.size()];
        priv_size = vec.size();
        priv_top = 0;
        for (auto x : vec) {
            push(x);
        }
    }

    Stack<T>(std::vector<T> &vec, size_t size) {
        if (vec.size() > size) {
            throw std::out_of_range("size of vector is larger than size specified");
            return;
        }
        priv_data = new T[size];
        priv_size = size;
        priv_top = 0;
        for (auto x : vec) {
            push(x);
        }
    }

    ~Stack<T>(void) {
        delete[] priv_data;
    }

    void push(T x) {
        if (is_full()) {
            throw std::out_of_range("the stack is full");
            return;
        }
        priv_data[priv_top++] = x;
    }

    size_t size(void) const {
        return priv_top;
    }

    size_t capacity(void) const {
        return priv_size;
    }

    bool is_full(void) const {
        return priv_top == priv_size;
    }

    bool is_empty(void) const {
        return priv_top == 0;
    }

    void pop(void) {
        if (is_empty()) {
            throw std::out_of_range("the stack is empty");
            return;
        }
        priv_top--;
    }

    T top(void) {
        T tmp; // If stack is empty, this will be returned.
        if (is_empty()) {
            throw std::out_of_range("the stack is empty");
            return tmp;
        }
        return priv_data[priv_top - 1];
    }

  private:
    T *priv_data;
    std::size_t priv_size;
    std::size_t priv_top;
};
#endif
