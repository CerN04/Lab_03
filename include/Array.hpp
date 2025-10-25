#pragma once

#include <stdexcept>

template <typename T> class Array {
private:
    size_t size;
    T *data;
    size_t capacity;

public:
    Array();
    Array(const size_t &n, T t = T{});
    Array(const std::initializer_list<T> &t);

    Array(const Array &other);
    Array(Array &&other) noexcept;
    ~Array() noexcept;

    void Resize(size_t new_size);
    T GetItem(size_t i) const;
    T &GetItemRef(size_t i);
    void SetItem(size_t index, T value);
    void DeleteItem(size_t index);
    void PushItem(T t);
    void PopItem();
    T Back() const;
    size_t GetSize() const;
};

template <typename T> class Array<T *> {
private:
    size_t size;
    T **data;
    size_t capacity;

public:
    Array();
    Array(const size_t &n, T *t = nullptr);
    ~Array() noexcept;

    T *GetItem(size_t i) const;
    void SetItem(size_t index, T *value);
    void DeleteItem(size_t index);
    void PushItem(T *t);
    size_t GetSize() const;
};