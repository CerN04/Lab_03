#include "Pentagon.hpp"

#include <iostream>

Pentagon::Pentagon() : points(5, Point{0.0, 0.0}) {}

Pentagon::Pentagon(const Pentagon &other) : points(other.points) {}

Point Pentagon::geomCenter() const {
    double cx = 0.0, cy = 0.0;
    double area = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        double x1 = points[i].x;
        double y1 = points[i].y;
        double x2 = points[(i + 1) % 5].x;
        double y2 = points[(i + 1) % 5].y;

        double f = (x1 * y2 - x2 * y1);
        area += f;
        cx += (x1 + x2) * f;
        cy += (y1 + y2) * f;
    }
    area /= 2.0;
    if (area == 0.0) {
        return Point{points[0].x, points[0].y};
    }
    cx /= (6.0 * area);
    cy /= (6.0 * area);
    return Point{cx, cy};
}

void Pentagon::print(std::ostream &os) const {
    os << "Pentagon\n";
    for (int i = 0; i < points.GetSize(); ++i) {
        os << "Vertex " << i + 1 << ": " << points[i] << "\n";
    }
}

void Pentagon::read(std::istream &is) {
    Point p;
    for (int i = 0; i < points.GetSize(); ++i) {
        is >> p;
        points.SetItem(i, p);
    }
}

Pentagon::operator double() const {
    double sm = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        sm += points[i].x * points[(i + 1) % 5].y - points[(i + 1) % 5].x * points[i].y;
    }
    return std::abs(sm) / 2;
}

Figure *Pentagon::clone() const { return new Pentagon(*this); }

Pentagon &Pentagon::operator=(Pentagon &f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points.SetItem(i, f.points[i]);
        }
    }
    return *this;
}

Pentagon &Pentagon::operator=(Pentagon &&f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points.SetItem(i, std::move(f.points[i]));
        }
    }
    return *this;
}

bool Pentagon::operator==(const Pentagon &f) const {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        if (points[i].x != f.points[i].x || points[i].y != f.points[i].y) {
            return false;
        }
    }
    return true;
}

Pentagon::~Pentagon() {}
