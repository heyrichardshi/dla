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
    int size;
public:
    DLA();
    bool walk();
    bool stick(double x, double y);
    bool kill(double x, double y);
    void calcMaxSize();
    void push(double x, double y);
    int getSize();
    void run(int N);
    void print(string filename);
};

#endif //DLA2_DLA_HPP
