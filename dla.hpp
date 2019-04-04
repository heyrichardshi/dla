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
    double maxRadius;
    int size;
    vector<vector<double>> aggregate;
    vector<vector<vector<vector<double>>>> cluster; // ring -> quadrant -> position -> x, y
    vector<double> countR;
public:
    DLA();
    void run(int N);
    bool walk();
    void push(double x, double y, int q);
    bool stick(double x, double y);
    bool kill(double x, double y);
    void checkMax(double radius);
    int quadrant(double theta);
    int neighborX(int q);
    int neighborY(int q);
    int ring(double radius);
    void ringUp();
    void print(string filename);
    void calcFractalDimension();
};

#endif //DLA2_DLA_HPP
