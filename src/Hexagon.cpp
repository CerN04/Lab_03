#include "Hexagon.hpp"

#include <iostream>

Hexagon::Hexagon() : points(6, Point{0.0, 0.0}) {}

Hexagon::Hexagon(const Hexagon &other) : points(other.points) {}

Point Hexagon::geomCenter() const {
    double cx = 0.0, cy = 0.0;
    double area = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        double x1 = points.GetItem(i).x;
        double y1 = points.GetItem(i).y;
        double x2 = points.GetItem((i + 1) % 6).x;
        double y2 = points.GetItem((i + 1) % 6).y;

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

void Hexagon::print(std::ostream &os) const {
    for (int i = 0; i < points.GetSize(); ++i) {
        os << "Vertex " << i + 1 << ": " << points.GetItem(i).x << " " << points.GetItem(i).y << "\n";
    }
}

void Hexagon::read(std::istream &is) {
    Point p;
    for (int i = 0; i < points.GetSize(); ++i) {
        is >> p.x >> p.y;
        points.SetItem(i, p);
    }
}

Hexagon::operator double() const {
    double sm = 0.0;
    for (size_t i = 0; i < points.GetSize(); ++i) {
        sm += points.GetItem(i).x * points.GetItem((i + 1) % 6).y - points.GetItem((i + 1) % 6).x * points.GetItem(i).y;
    }
    return std::abs(sm) / 2;
}

Figure *Hexagon::clone() const { return new Hexagon(*this); }

Hexagon &Hexagon::operator=(Hexagon &f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points.SetItem(i, f.points.GetItem(i));
        }
    }
    return *this;
}

Hexagon &Hexagon::operator=(Hexagon &&f) {
    if (this != &f) {
        for (size_t i = 0; i < points.GetSize(); ++i) {
            points.SetItem(i, std::move(f.points.GetItem(i)));
        }
    }
    return *this;
}

bool Hexagon::operator==(const Hexagon &f) const {
    for (size_t i = 0; i < points.GetSize(); ++i) {
        if (points.GetItem(i).x != f.points.GetItem(i).x || points.GetItem(i).y != f.points.GetItem(i).y) {
            return false;
        }
    }
    return true;
}

Hexagon::~Hexagon() {}
