#include "Stack.h"
#include "Move.h"
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
Stack<T>::Stack(int size) : capacity(size), top(-1) {
    arr = new T[capacity];
}

template <typename T>
Stack<T>::Stack(const Stack& other) : capacity(other.capacity), top(other.top) {
    arr = new T[capacity];
    for (int i = 0; i <= top; i++) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }

    delete[] arr;

    capacity = other.capacity;
    top = other.top;
    arr = new T[capacity];

    for (int i = 0; i <= top; ++i) {
        arr[i] = other.arr[i];
    }

    return *this;
}

template <typename T>
Stack<T>::~Stack() {
    delete[] arr;
}

template <typename T>
void Stack<T>::push(T element) {
    if(isFull()) { throw overflow_error("Stack is full");}
     top++;
    arr[top] = element;
}

template <typename T>
T Stack<T>::pop() {
    if(isEmpty()) { throw underflow_error("Stack is ");}
    else { return arr[top--]; }
}

template <typename T>
T Stack<T>::peek() const {
    if(isEmpty()) {throw out_of_range("Stack is empty");}
    else return arr[top];
}

template <typename T>
bool Stack<T>::isEmpty() const {
    if (top == -1)
      return true;
    else return false;
}

template <typename T>
bool Stack<T>::isFull() const {
    if(top==capacity-1)
      {
      return true;
      }
      else return false;
}

template <typename T>
void Stack<T>::display() const {
    for (int i = top; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template class Stack<int>;
template class Stack<char>;
template class Stack<double>;
template class Stack<Move>;