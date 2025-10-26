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
    Point GetItem(size_t i) const;
    Point &GetItemRef(size_t i);
    void SetItem(size_t index, Point value);
    void DeleteItem(size_t index);
    void PushItem(Point t);
    void PopItem();
    Point Back() const;
    size_t GetSize() const;
};

class ArrayF {
private:
    size_t size;
    Figure **data;
    size_t capacity;

public:
    ArrayF();
    ArrayF(const size_t &n, Figure *t = nullptr);
    ArrayF(const ArrayF &other);
    ArrayF(ArrayF &&other) noexcept;
    ~ArrayF() noexcept;

    ArrayF &operator=(const ArrayF &other);
    ArrayF &operator=(ArrayF &&other) noexcept;

    void Resize(size_t new_size);
    Figure *GetItem(size_t i) const;
    void SetItem(size_t index, Figure *value);
    void DeleteItem(size_t index);
    void PushItem(Figure *t);
    void PopItem();
    Figure *Back() const;
    size_t GetSize() const;
};