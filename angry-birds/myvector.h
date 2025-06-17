#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include<iostream>
using namespace std;
template<typename T>
class Dynamic_array {
private:
    T* data;
    int capacity;
    int length;

public:
    Dynamic_array() {
        data = new T[10];
        capacity = 10;
        length = 0;
    }

    ~Dynamic_array() {
        if(data)
        delete[] data;
    }

    void push(const T& item) {
        if (length == capacity) {
            grow();
        }
        data[length++] = item;
    }

    void grow() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < length; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

    T& operator[](int index) {
        if (index < 0 || index >= length) {
            std::cerr << "Index out of bounds!\n";
            exit(-1);
        }
        return data[index];
    }

    int size() const {
        return length;
    }

    void clear() {
        length = 0;
    }
};

#endif DYNAMIC_ARRAY_H