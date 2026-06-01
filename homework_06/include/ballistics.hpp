#pragma once

#include <string>

struct BallisticsInput {
  double drone_x;
  double drone_y;
  double drone_z;
  double target_x;
  double target_y;
  double attack_speed;
  double acceleration_path;
  std::string ammo_name;
};

struct DropSolution {
  double fire_x;
  double fire_y;
};

DropSolution compute_drop_solution(const BallisticsInput& input);