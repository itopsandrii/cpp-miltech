#include "ballistics.hpp"

#include <exception>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <input_file>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "error: cannot open file: " << argv[1] << "\n";
    return 1;
  }

  BallisticsInput input;
  file >> input.drone_x >> input.drone_y >> input.drone_z >> input.target_x >> input.target_y >> input.attack_speed >>
    input.acceleration_path >> input.ammo_name;

  if (!file) {
    std::cerr << "error: invalid input format\n";
    return 1;
  }

  try {
    DropSolution solution = compute_drop_solution(input);
    std::cout << solution.fire_x << " " << solution.fire_y << "\n";
  }
  catch (const std::exception& e) {
    std::cerr << "error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
