#pragma once

#include "Array.hpp"
#include "Figure.hpp"

class Hexagon : public Figure {
public:
    Hexagon();
    Hexagon(const Hexagon &other);
    Point geomCenter() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    operator double() const override;
    Hexagon &operator=(Hexagon &r_fig);
    Hexagon &operator=(Hexagon &&r_fig);
    bool operator==(const Hexagon &r_fig) const;
    virtual Figure *clone() const override;
    ~Hexagon();

private:
    Array<Point> points;
};