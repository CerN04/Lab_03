#pragma once

#include"Figure.hpp"

#include <stdexcept>

class ArrayFigure {
private:
    size_t size;
    Figure **data;
    size_t capacity;

public:
    ArrayFigure();
    ArrayFigure(const size_t &n, Figure *t = nullptr);
    ArrayFigure(const ArrayFigure &other);
    ArrayFigure(ArrayFigure &&other) noexcept;
    ~ArrayFigure() noexcept;

    ArrayFigure &operator=(const ArrayFigure &other);
    ArrayFigure &operator=(ArrayFigure &&other) noexcept;

    void Resize(size_t new_size);
    Figure *operator[](size_t i);
    const Figure* operator[](size_t i) const;
    void SetItem(size_t index, Figure *value);
    void DeleteItem(size_t index);
    void PushItem(Figure *t);
    void PopItem();
    Figure *Back() const;
    size_t GetSize() const;
};