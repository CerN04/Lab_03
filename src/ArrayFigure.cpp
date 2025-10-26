#include "ArrayFigure.hpp"

#include <stdexcept>

#include "Figure.hpp"

ArrayFigure::ArrayFigure() : size(0), data(nullptr), capacity(0) {}

ArrayFigure::~ArrayFigure() noexcept {
    for (size_t i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
}

ArrayFigure::ArrayFigure(const size_t &n, Figure *t) : size(n), capacity(n) {
    data = new Figure *[capacity];
    for (size_t i = 0; i < size; ++i) {
        if (t != nullptr) {
            data[i] = t->clone();
        } else {
            data[i] = nullptr;
        }
    }
}



ArrayFigure::ArrayFigure(const ArrayFigure &other) : size(other.size), capacity(other.capacity) {
    data = new Figure *[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i]->clone();
    }
}

ArrayFigure::ArrayFigure(ArrayFigure &&other) noexcept : size(other.size), data(other.data), capacity(other.capacity) {
    other.size = 0;
    other.data = nullptr;
    other.capacity = 0;
}

ArrayFigure &ArrayFigure::operator=(const ArrayFigure &other) {
    if (this == &other) {
        return *this;
    }
    for (size_t i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;

    size = other.size;
    capacity = other.capacity;
    data = new Figure *[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i]->clone();
    }
    return *this;
}

ArrayFigure &ArrayFigure::operator=(ArrayFigure &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    for (size_t i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;

    size = other.size;
    capacity = other.capacity;
    data = other.data;

    other.size = 0;
    other.data = nullptr;
    other.capacity = 0;
    return *this;
}

void ArrayFigure::Resize(size_t new_size) {
    if (new_size == size) {
        return;
    }
    if (new_size > capacity) {
        size_t new_capacity = std::max(new_size, capacity * 2);
        Figure **new_data = new Figure *[new_capacity];
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
    if (new_size < size) {
        for (size_t i = new_size; i < size; ++i) {
            delete data[i];
        }
    }
    size = new_size;
}

Figure *ArrayFigure::operator[](size_t i) {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

const Figure *ArrayFigure::operator[](size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

void ArrayFigure::SetItem(size_t index, Figure *value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete data[index];
    data[index] = value;
}

void ArrayFigure::DeleteItem(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete data[index];
    for (size_t i = index; i + 1 < size; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

void ArrayFigure::PushItem(Figure *t) {
    if (size >= capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        Figure **new_data = new Figure *[new_capacity];
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

void ArrayFigure::PopItem() {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    delete data[size - 1];
    size--;
}

Figure *ArrayFigure::Back() const {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    return data[size - 1];
}

size_t ArrayFigure::GetSize() const { return size; }