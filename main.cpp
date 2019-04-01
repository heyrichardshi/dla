#include <iostream>
#include <fstream>
#include <cmath>

#include "dla.cpp"

using namespace std;

int main() {

    int N = 5000;
    DLA dla;
    dla.run(N);

    dla.print("5k.txt");
}

