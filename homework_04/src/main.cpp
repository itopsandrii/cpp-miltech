#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>


int main(int argc, char** argv) {
    // The program expects exactly one argument: a path to telemetry samples.
    if (argc != 2) {
        std::cerr << "usage: ugv_odometry <input_path>\n";
        return 1;
    }

    const int TICKS_PER_REV   = 1024;
    const double WHEEL_RADIUS = 0.3;
    const double WHEELBASE    = 1.0;

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "error can not open file" << argv[1] << std::endl; 
        return 1;
    }

    int prev_fl = 0, prev_fr = 0, prev_bl = 0, prev_br = 0;
    long long prev_timestamp = 0;

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        int fl, fr, bl, br;
        long long timestamp;

        std::istringstream ss(line);

        ss >> timestamp >> fl >> fr >> bl >> br;

        int delta_fl, delta_fr, delta_br, delta_bl;
        
        delta_fl = fl - prev_fl;
        delta_fr = fr - prev_fr;
        delta_bl = bl - prev_bl;
        delta_br = br - prev_br;

        prev_fl = fl;
        prev_fr = fr;
        prev_bl = bl;
        prev_br = br;

        row++;

        double dist_left, dist_right;

        dist_left = (( delta_fl + delta_bl ) / 2.0)*(2*M_PI*WHEEL_RADIUS) / TICKS_PER_REV;
        dist_right = (( delta_fr + delta_br ) /2.0)*(2*M_PI*WHEEL_RADIUS) / TICKS_PER_REV ;
    }
}