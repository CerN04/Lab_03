#include "Array.hpp"
#include "Figure.hpp"

Array::Array() : size(0), data(nullptr), capacity(0) {}

Array::Array(const size_t &n, Point t) : size(n), capacity(n) {
    data = new Point[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = t;
    }
}

Array::Array(const std::initializer_list<Point> &t) : size(t.size()), capacity(t.size()) {
    data = new Point[capacity];
    std::copy(t.begin(), t.end(), data);
}

Array::Array(const Array &other) : size(other.size), capacity(other.capacity) {
    data = new Point[capacity];
    std::copy(other.data, other.data + size, data);
}

Array::Array(Array &&other) noexcept : size(other.size), data(other.data), capacity(other.capacity) {
    other.size = 0;
    other.data = nullptr;
    other.capacity = 0;
}
Array::~Array() noexcept { delete[] data; }

void Array::Resize(size_t new_size) {
    if (new_size == size) {
        return;
    }
    if (new_size > capacity) {
        size_t new_capacity = std::max(new_size, capacity * 2);
        Point *new_data = new Point[new_capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    size = new_size;
}

Point Array::GetItem(size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

Point &Array::GetItemRef(size_t i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

void Array::SetItem(size_t index, Point value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

void Array::DeleteItem(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

void Array::PushItem(Point t) {
    if (size >= capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        Point *new_data = new Point[new_capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    data[size++] = t;
}

Point Array::Back() const {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return data[size - 1];
}

void Array::PopItem() {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    size--;
}

size_t Array::GetSize() const { return size; }
