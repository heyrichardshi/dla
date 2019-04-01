#ifndef DLA2_DLA_HPP
#define DLA2_DLA_HPP

#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

#include "random.hpp"
#include "walk.hpp"

using namespace std;

extern const double PI;

class DLA {
    double seedRadius;
    double killRadius;
    double stepLength;
    double stickDistance;
    double maxSize;
    vector<vector<double>> aggregate;
    double furthest[2];
    double furthestDistance;
    vector<vector<double>> NE;
    vector<vector<double>> NW;
    vector<vector<double>> SW;
    vector<vector<double>> SE;
    int size;
public:
    DLA();
    bool walk();
    bool stick(double x, double y);
    bool kill(double x, double y);
    void calcMaxSize();
    int quadrant(double theta);
    void push(double x, double y);
    void pushQ1(double x, double y);
    void pushQ2(double x, double y);
    void pushQ3(double x, double y);
    void pushQ4(double x, double y);
    void run(int N);
    void print(string filename);
};

#endif //DLA2_DLA_HPP
