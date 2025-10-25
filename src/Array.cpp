#include "Array.hpp"
#include "Figure.hpp"

template <typename T> Array<T>::Array() : size(0), data(nullptr), capacity(0) {}

template <typename T> Array<T>::Array(const size_t &n, T t) : size(n), capacity(n) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = t;
    }
}

template <typename T> Array<T>::Array(const std::initializer_list<T> &t) : size(t.size()), capacity(t.size()) {
    data = new T[capacity];
    std::copy(t.begin(), t.end(), data);
}

template <typename T> Array<T>::Array(const Array<T> &other) : size(other.size), capacity(other.capacity) {
    data = new T[capacity];
    std::copy(other.data, other.data + size, data);
}

template <typename T>
Array<T>::Array(Array<T> &&other) noexcept : size(other.size), data(other.data), capacity(other.capacity) {
    other.size = 0;
    other.data = nullptr;
    other.capacity = 0;
}

template <typename T> Array<T>::~Array() noexcept { delete[] data; }

template <typename T> void Array<T>::Resize(size_t new_size) {
    if (new_size == size) {
        return;
    }
    if (new_size > capacity) {
        size_t new_capacity = std::max(new_size, capacity * 2);
        T *new_data = new T[new_capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    size = new_size;
}

template <typename T> T Array<T>::GetItem(size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

template <typename T> T &Array<T>::GetItemRef(size_t i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

template <typename T> void Array<T>::SetItem(size_t index, T value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

template <typename T> void Array<T>::DeleteItem(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

template <typename T> void Array<T>::PushItem(T t) {
    if (size >= capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        T *new_data = new T[new_capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    data[size++] = t;
}

template <typename T> T Array<T>::Back() const {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return data[size - 1];
}

template <typename T> void Array<T>::PopItem() {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    size--;
}

template <typename T> size_t Array<T>::GetSize() const { return size; }

template class Array<Point>;