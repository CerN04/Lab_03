#pragma once

#include"Figure.hpp"

#include <stdexcept>

class Array {
private:
    size_t size;
    Point *data;
    size_t capacity;

public:
    Array();
    Array(const size_t &n, Point t = Point{});
    Array(const std::initializer_list<Point> &t);

    Array(const Array &other);
    Array(Array &&other) noexcept;
    ~Array() noexcept;

    void Resize(size_t new_size);
    Point operator[](size_t i) const;
    void SetItem(size_t index, Point value);
    void DeleteItem(size_t index);
    void PushItem(Point t);
    void PopItem();
    Point Back() const;
    size_t GetSize() const;
};