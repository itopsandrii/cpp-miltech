#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


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

    std::string line;
    while (std::getline(file, line)) {
        
    }
}
