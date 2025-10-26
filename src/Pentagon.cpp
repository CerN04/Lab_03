#include "Pentagon.hpp"

#include <iostream>

Pentagon::Pentagon() : points(5, Point{0.0, 0.0}) {}

Pentagon::Pentagon(const Pentagon &other) : points(other.points) {}

Point Pentagon::geomCenter() const {
    double cx = 0.0, cy = 0.0;
    double area = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        double x1 = points.GetItem(i).x;
        double y1 = points.GetItem(i).y;
        double x2 = points.GetItem((i + 1) % 5).x;
        double y2 = points.GetItem((i + 1) % 5).y;

        double f = (x1 * y2 - x2 * y1);
        area += f;
        cx += (x1 + x2) * f;
        cy += (y1 + y2) * f;
    }
    area /= 2.0;
    if (area == 0.0) {
        return Point{points.GetItem(0).x, points.GetItem(0).y};
    }
    cx /= (6.0 * area);
    cy /= (6.0 * area);
    return Point{cx, cy};
}

void Pentagon::print(std::ostream &os) const {
    for (int i = 0; i < points.GetSize(); ++i) {
        os << "Vertex " << i + 1 << ": " << points.GetItem(i).x << " " << points.GetItem(i).y << "\n";
    }
}

void Pentagon::read(std::istream &is) {
    Point p;
    for (int i = 0; i < points.GetSize(); ++i) {
        is >> p.x >> p.y;
        points.SetItem(i, p);
    }
}

Pentagon::operator double() const {
    double sm = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        sm += points.GetItem(i).x * points.GetItem((i + 1) % 5).y - points.GetItem((i + 1) % 5).x * points.GetItem(i).y;
    }
    return std::abs(sm) / 2;
}

Figure *Pentagon::clone() const { return new Pentagon(*this); }

Pentagon &Pentagon::operator=(Pentagon &f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points.SetItem(i, f.points.GetItem(i));
        }
    }
    return *this;
}

Pentagon &Pentagon::operator=(Pentagon &&f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points.SetItem(i, std::move(f.points.GetItem(i)));
        }
    }
    return *this;
}

bool Pentagon::operator==(const Pentagon &f) const {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        if (points.GetItem(i).x != f.points.GetItem(i).x || points.GetItem(i).y != f.points.GetItem(i).y) {
            return false;
        }
    }
    return true;
}

Pentagon::~Pentagon() {}
