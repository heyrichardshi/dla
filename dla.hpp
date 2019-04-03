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
    vector<vector<double>> aggregate;
    vector<vector<vector<vector<double>>>> cluster; // ring -> quadrant -> position -> x, y
    int size;
    vector<double> countR;
public:
    DLA();
    bool walk();
    bool stick(double x, double y);
    bool kill(double x, double y);
    void checkMax(double radius);
    int quadrant(double theta);
    int ring(double radius);
    int neighborX(int q);
    int neighborY(int q);
    void push(double x, double y, int q);
    void ringUp();
    void run(int N);
    void print(string filename);
    void calcFractalDimension();
};

#endif //DLA2_DLA_HPP
