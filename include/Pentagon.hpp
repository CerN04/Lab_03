#pragma once

#include "Array.hpp"
#include "Figure.hpp"


class Pentagon : public Figure {
public:
    Pentagon();
    Pentagon(const Pentagon &other);
    Point geomCenter() const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
    operator double() const override;
    Pentagon &operator=(Pentagon &fig);
    Pentagon &operator=(Pentagon &&fig);
    bool operator==(const Pentagon &fig) const;
    virtual Figure *clone() const override;
    ~Pentagon();

private:
    Array<Point> points;
};