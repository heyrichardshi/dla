#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <ctime>

#include "dla.hpp"
#include "walk.hpp"

using namespace std;

int main() {
    auto start = chrono::system_clock::now();

    int N = 5000;
    DLA dla;
    dla.run(N);

    auto end = chrono::system_clock::now();

    dla.print("5k.txt");

    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "finished computation at " << ctime(&end_time)
         << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
