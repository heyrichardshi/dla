#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <ctime>

#include "dla.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    int N;
    string filename;

    if (argc == 3) {
        N = stoi(string(argv[1]));
        filename = string(argv[2]);
    }
    else {
        cout << "Format: ./dla [N] [filename]" << endl;
    }

    auto start = chrono::system_clock::now();

    DLA dla;
    dla.run(N);

    auto end = chrono::system_clock::now();

    dla.print(filename);

    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "finished computation at " << ctime(&end_time)
         << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

