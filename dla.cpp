#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

#include <thread>
#include <chrono>

#include "random.hpp"
#include "walk.hpp"
#include "dla.hpp"

using namespace std;

extern const double PI;

DLA::DLA() : seedRadius(1), killRadius(3), stickDistance(0.25), stepLength(0.5), maxRadius(0), size(1) {
    double p[2] = {0, 0};
    vector<double> v(p, p + sizeof(p) / sizeof(double));
    aggregate.push_back(v);
    ringUp();
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

void DLA::push(double x, double y, int q) { // TODO
    double radius = sqrt(pow(x,2) + pow(y,2));
    double theta = atan2(y, x);

    int qx = neighborX(q);
    int qy = neighborY(q);
    int r = radius;

    bool edgeX = (abs(x) <= stickDistance);
    bool edgeY = (abs(y) <= stickDistance);

    double p[2] = {x, y};
    vector<double> v(p, p + sizeof(p) / sizeof(double));

    aggregate.push_back(v);

    cluster[r][q].push_back(v);

    if (edgeX) {
        cluster[r][qx].push_back(v);
    }
    if (edgeY) {
        cluster[r][qy].push_back(v);
    }

    if ((r != 0) && (radius - r <= stickDistance)) {
        cluster[r - 1][q].push_back(v);
        if (edgeX) {
            cluster[r - 1][qx].push_back(v);
        }
        if (edgeY) {
            cluster[r - 1][qy].push_back(v);
        }
    }
    else if (r + 1 - radius <= stickDistance) {
        if (r + 1 >= cluster.size()) {
            ringUp();
        }
        cluster[r + 1][q].push_back(v);
        if (edgeX) {
            cluster[r + 1][qx].push_back(v);
        }
        if (edgeY) {
            cluster[r + 1][qy].push_back(v);
        }
    }
    cout << size << endl; // TODO
    size++;
}

int DLA::quadrant(double theta) { // theta within [-PI, PI]
    if ((theta >= 0) && (theta < PI / 2)) {
        return 0; // quadrant 1
    }
    else if ((theta >= PI / 2) && (theta < PI)) {
        return 1; // quadrant 2
    }
    else if ((theta >= -PI / 2) && (theta < 0)) {
        return 3; // quadrant 4
    }
    else {
        return 2; // quadrant 3
    }
}

int DLA::neighborX(int q) {
    switch(q) {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
            return 3;
        case 3:
            return 2;
    }
    return -1;
}

int DLA::neighborY(int q) {
    switch(q) {
        case 0:
            return 3;
        case 1:
            return 2;
        case 2:
            return 1;
        case 3:
            return 0;
    }
    return -1;
}

int DLA::ring(double radius) {
    int r = radius;

    if (r >= cluster.size()) {
        ringUp();
    }

    return r;
}

void DLA::ringUp() {
    vector<double> origin(2,0); // (x,y)

    vector<vector<double>> v; // position vector
    v.push_back(origin);

    vector<vector<vector<double>>> q; // quadrant vector
    for (int i = 0; i < 4; i++) {
        q.push_back(v);
    }

    cluster.push_back(q); // ring vector
}

bool DLA::stick(double x, double y) { // TODO
    double radius = sqrt(pow(x,2) + pow(y,2));

    if (radius > maxRadius + stickDistance) {
        return false;
    }

    double theta = atan2(y, x);

    int r = ring(radius);
    int q = quadrant(theta);

    for (auto i = cluster[r][q].rbegin(); i != cluster[r][q].rend(); i++) {
        if (sqrt(pow(x - (*i)[0], 2) + pow(y - (*i)[1], 2)) <= stickDistance) {
            push(x, y, q);
            checkMax(radius);
            return true;
        }
    }

    return false;
}


bool DLA::kill(double x, double y) {
    double distance = sqrt(pow(x,2) + pow(y,2));

    return (distance > killRadius);
}

void DLA::checkMax(double radius) {
    maxRadius = radius > maxRadius ? radius : maxRadius;

    if (seedRadius < 0.5 * maxRadius) {
        seedRadius = 2 * maxRadius;
        killRadius = 5 * maxRadius;
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

void DLA::calcFractalDimension() {
    for (int i = 0; i < int(maxRadius) + 2; i++) {
        countR.push_back(0);
    }

    for (auto i : aggregate) {
        int distance = sqrt(pow(i[0], 2) + pow(i[1], 2));
        countR[distance + 1]++;
    }

    for (int i = 1; i < int(maxRadius) + 2; i++) {
        countR[i] += countR[i - 1];
    }

    for (auto i : countR) {
        cout << i << endl;
    }
}