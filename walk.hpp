#ifndef RANDOM_WALK_WALK_HPP
#define RANDOM_WALK_WALK_HPP

#include <cmath>
#include <vector>

#include "random.hpp"

using namespace std;

const double PI = 3.141592653589793238463;

class Walk {    // 3-space
    double _x;   // _x coordinate
    double _y;   // _y coordinate
    double _a;   // step size

public:
    Walk(double x, double y, double a);
    Walk();
    void step();
    double getX();
    double getY();
};

Walk::Walk(double x, double y, double a) : _x(x), _y(y), _a(a) {}

Walk::Walk() : Walk(0, 0, 1) {}

void Walk::step() {
    double theta = RandomDouble(0, 2 * PI);

    _x += _a * cos(theta);
    _y += _a * sin(theta);
}

double Walk::getX() {
    return _x;
}

double Walk::getY() {
    return _y;
}

#endif //RANDOM_WALK_WALK_HPP
