#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

#include "random.hpp"
#include "walk.hpp"
#include "dla.hpp"

using namespace std;

extern const double PI;

DLA::DLA() : seedRadius(1), killRadius(3), stickDistance(0.25), stepLength(0.5), maxSize(0), size(0), furthestDistance(0) {
    push(0, 0);
    pushQ1(0, 0);
    pushQ2(0, 0);
    pushQ3(0, 0);
    pushQ4(0, 0);
    furthest[0] = 0;
    furthest[1] = 0;
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

void DLA::pushQ1(double x, double y) {
    double origin[2] = {x, y};
    vector<double> v(origin, origin + sizeof(origin) / sizeof(double));
    NE.push_back(v);
}

void DLA::pushQ2(double x, double y) {
    double origin[2] = {x, y};
    vector<double> v(origin, origin + sizeof(origin) / sizeof(double));
    NW.push_back(v);
}

void DLA::pushQ3(double x, double y) {
    double origin[2] = {x, y};
    vector<double> v(origin, origin + sizeof(origin) / sizeof(double));
    SW.push_back(v);
}

void DLA::pushQ4(double x, double y) {
    double origin[2] = {x, y};
    vector<double> v(origin, origin + sizeof(origin) / sizeof(double));
    SE.push_back(v);
}

int DLA::quadrant(double theta) { // theta within [-PI, PI]
    if ((theta >= 0) && (theta < PI / 2)) {
        return 1; // quadrant 1 (NE)
    }
    else if ((theta >= PI / 2) && (theta < PI)) {
        return 2; // quadrant 2 (NW)
    }
    else if ((theta >= -PI / 2) && (theta < 0)) {
        return 4; // quadrant 4 (SE)
    }
    else {
        return 3; // quadrant 3 (SW)
    }
}

bool DLA::stick(double x, double y) {
    double radius = sqrt(pow(x,2) + pow(y,2));

    if (radius > furthestDistance + stickDistance) {
        return false;
    }

    double theta = atan2(y, x);

    switch(quadrant(theta)) {
        case 1:
            for (vector<vector<double>>::reverse_iterator i = NE.rbegin(); i != NE.rend(); i++ ) {
        double distance = sqrt(pow(x - (*i)[0], 2) + pow(y - (*i)[1], 2));
        if (distance < stickDistance) {
            push(x, y);
            pushQ1(x, y);
            if (abs(x) <= stickDistance) {
                pushQ2(x, y);
            }
            if (abs(y) <= stickDistance) {
                pushQ4(x, y);
            }

            if (radius > furthestDistance) {
                furthest[0] = x;
                furthest[1] = y;
                furthestDistance = radius;
            }

            calcMaxSize();
            cout << size << endl; // TODO: cout
            return true;
        }
    }
            break;
        case 2:
            for (vector<vector<double>>::reverse_iterator i = NW.rbegin(); i != NW.rend(); i++ ) {
        double distance = sqrt(pow(x - (*i)[0], 2) + pow(y - (*i)[1], 2));
        if (distance < stickDistance) {
            push(x, y);
            pushQ2(x, y);
            if (abs(x) <= stickDistance) {
                pushQ1(x, y);
            }
            if (abs(y) <= stickDistance) {
                pushQ3(x, y);
            }

            if (radius > furthestDistance) {
                furthest[0] = x;
                furthest[1] = y;
                furthestDistance = radius;
            }

            calcMaxSize();
            cout << size << endl; // TODO: cout
            return true;
        }
    }
            break;
        case 3:
            for (vector<vector<double>>::reverse_iterator i = SW.rbegin(); i != SW.rend(); i++ ) {
        double distance = sqrt(pow(x - (*i)[0], 2) + pow(y - (*i)[1], 2));
        if (distance < stickDistance) {
            push(x, y);
            pushQ3(x, y);
            if (abs(x) <= stickDistance) {
                pushQ4(x, y);
            }
            if (abs(y) <= stickDistance) {
                pushQ2(x, y);
            }

            if (radius > furthestDistance) {
                furthest[0] = x;
                furthest[1] = y;
                furthestDistance = radius;
            }

            calcMaxSize();
            cout << size << endl; // TODO: cout
            return true;
        }
    }
            break;
        case 4:
            for (vector<vector<double>>::reverse_iterator i = SE.rbegin(); i != SE.rend(); i++ ) {
        double distance = sqrt(pow(x - (*i)[0], 2) + pow(y - (*i)[1], 2));
        if (distance < stickDistance) {
            push(x, y);
            pushQ4(x, y);
            if (abs(x) <= stickDistance) {
                pushQ3(x, y);
            }
            if (abs(y) <= stickDistance) {
                pushQ1(x, y);
            }

            if (radius > furthestDistance) {
                furthest[0] = x;
                furthest[1] = y;
                furthestDistance = radius;
            }

            calcMaxSize();
            cout << size << endl; // TODO: cout
            return true;
        }
    }
            break;
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


    for (vector<vector<double>>::reverse_iterator i = aggregate.rbegin(); i != aggregate.rend(); i++ ) {
        double distance = sqrt(pow(x - (*i)[0], 2) + pow(y - (*i)[1], 2));
        maxSize = distance > maxSize ? distance : maxSize;
    }

    if (seedRadius < 0.5 * maxSize) {
        seedRadius = 2 * maxSize;
        killRadius = 5 * maxSize;
    }
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