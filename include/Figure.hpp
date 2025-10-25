#pragma once

#include <ostream>

struct Point {
    double x;
    double y;
};

inline std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

class Figure {
public:
    Figure() = default;
    virtual Point geomCenter() const = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;
    virtual operator double() const = 0;
    virtual Figure *clone() const = 0;
    virtual ~Figure() = default;
};

inline std::ostream &operator<<(std::ostream &os, const Figure &fig) {
    fig.print(os);
    return os;
}

inline std::istream &operator>>(std::istream &is, Figure &fig) {
    fig.read(is);
    return is;
}
