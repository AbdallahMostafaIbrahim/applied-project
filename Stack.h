#pragma once

template <typename T>
class Stack
{
private:
    T *arr;
    int top = -1;
    int capacity;

public:
    Stack(int size);
    Stack(const Stack &other);
    Stack &operator=(const Stack &other);
    ~Stack();

    void push(T element);
    T pop();
    T peek() const;
    bool isEmpty() const;
    bool isFull() const;
    void display() const;
};
