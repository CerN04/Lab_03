#include "Array.hpp"

#include <stdexcept>

#include "Figure.hpp"

template <typename T> Array<T *>::Array() : size(0), data(nullptr), capacity(0) {}

template <typename T> Array<T *>::~Array() noexcept {
    for (size_t i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
}

template <typename T> Array<T *>::Array(const size_t &n, T *t) : size(n), capacity(n) {
    data = new T *[capacity];
    for (size_t i = 0; i < size; ++i) {
        if (t != nullptr) {
            data[i] = t->clone();
        } else {
            data[i] = nullptr;
        }
    }
}

template <typename T> T *Array<T *>::GetItem(size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

template <typename T> void Array<T *>::SetItem(size_t index, T *value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete data[index];
    data[index] = value;
}

template <typename T> void Array<T *>::DeleteItem(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete data[index];
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

template <typename T> void Array<T *>::PushItem(T *t) {
    if (size >= capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        T **new_data = new T *[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        for (size_t i = size; i < new_capacity; ++i) {
            new_data[i] = nullptr;
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    data[size++] = t;
}

template <typename T> size_t Array<T *>::GetSize() const { return size; }

template class Array<Figure *>;