#pragma once

#include "Array.hpp"

#include "Figure.hpp"

class Octagon : public Figure {
public:
    Octagon();
    Octagon(const Octagon &other);
    Point geomCenter() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    operator double() const override;
    Octagon &operator=(Octagon &fig);
    Octagon &operator=(Octagon &&fig);
    bool operator==(const Octagon &fig) const;
    virtual Figure *clone() const override;
    ~Octagon();

private:
    Array points;
};