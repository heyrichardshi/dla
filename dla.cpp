#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

#include "random.hpp"
#include "walk.hpp"
#include "dla.hpp"

using namespace std;

extern const double PI;

DLA::DLA() : seedRadius(1), killRadius(3), stickDistance(0.25), stepLength(0.5), maxSize(0), size(0) {
    push(0, 0);
}

bool DLA::walk() {
    double radius = RandomDouble(seedRadius, killRadius);
    double theta = RandomDouble(0, 2 * PI);

    Walk walk(radius * cos(theta), radius * sin(theta), stepLength);

    while (true) {
        if (stick(walk.getX(), walk.getY())) {
            return true;
        }

        walk.step();

        if (kill(walk.getX(), walk.getY())) {
            return false;
        }
    }
}

void DLA::push(double x, double y) {
    double origin[2] = {x, y};
    vector<double> v(origin, origin + sizeof(origin) / sizeof(double));
    aggregate.push_back(v);
    size++;
}

bool DLA::stick(double x, double y) {
    double distance = sqrt(pow(x,2) + pow(y,2));

    if (distance > maxSize + stickDistance) {
        return false;
    }

    for (vector<vector<double>>::reverse_iterator i = aggregate.rbegin(); i != aggregate.rend(); i++) {
        distance = sqrt(pow(x - (*i)[0], 2) + pow(y - (*i)[1], 2));
        if (distance < stickDistance) {
            push(x, y);
            calcMaxSize();
            cout << size << ": " << x << " " << y << endl; // TODO: cout
            return true;
        }
    }

    return false;
}

bool DLA::kill(double x, double y) {
    double distance = sqrt(pow(x,2) + pow(y,2));

    return (distance > killRadius);
}

void DLA::calcMaxSize() {
    double x = aggregate[size - 1][0];
    double y = aggregate[size - 1][1];

    if (sqrt(pow(x, 2) + pow(y, 2)) < 0.5 * maxSize) {
        return;
    }

    for (auto i : aggregate) {
        double distance = sqrt(pow(x - i[0], 2) + pow(y - i[1], 2));
        maxSize = distance > maxSize ? distance : maxSize;
    }

    if (seedRadius < 0.5 * maxSize) {
        seedRadius = 2 * maxSize;
        killRadius = 5 * maxSize;
    }
}

int DLA::getSize() {
    return size;
}

void DLA::run(int N) {
    while (size != N + 1) {
        walk();
    }
}

void DLA::print(string filename) {
    ofstream file;
    file.open(filename);


    for (auto i : aggregate) {
        file << i[0] << " " << i[1] << endl;
    }
}