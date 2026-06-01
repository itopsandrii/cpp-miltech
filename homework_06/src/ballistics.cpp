#include "ballistics.hpp"

#include <cmath>
#include <stdexcept>

DropSolution compute_drop_solution(const BallisticsInput &input) {
    double m = 0.0;
    double d = 0.0;
    double l = 0.0;

    if (input.ammo_name == "VOG-17") {
        m = 0.35;
        d = 0.07;
        l = 0.0;
    } else if (input.ammo_name == "M67") {
        m = 0.6;
        d = 0.10;
        l = 0.0;
    } else if (input.ammo_name == "RKG-3") {
        m = 1.2;
        d = 0.10;
        l = 0.0;
    } else if (input.ammo_name == "GLIDING-VOG") {
        m = 0.45;
        d = 0.10;
        l = 1.0;
    } else if (input.ammo_name == "GLIDING-RKG") {
        m = 1.4;
        d = 0.10;
        l = 1.0;
    } else {
        throw std::invalid_argument("unknown ammo: " + input.ammo_name);
    }
    const double g = 9.81;
    const double pi = 3.14159265358979323846;

    double v0 = input.attack_speed;
    double z0 = input.drone_z;

    double a_eq = d * g * m - 2.0 * d * d * l * v0;
    double b_eq = -3.0 * g * m * m + 3.0 * d * l * m * v0;
    double c_eq = 6.0 * m * m * z0;

    double p = -(b_eq * b_eq) / (3.0 * a_eq * a_eq);
    double q = 2.0 * b_eq * b_eq * b_eq / (27.0 * a_eq * a_eq * a_eq) + c_eq / a_eq;

    double cos_arg = 3.0 * q / (2.0 * p) * std::sqrt(-3.0 / p);

    if (cos_arg > 1.0) {
        cos_arg = 1.0;
    }
    if (cos_arg < -1.0) {
        cos_arg = -1.0;
    }

    double phi = std::acos(cos_arg);

    double t = 2.0 * std::sqrt(-p / 3.0) * std::cos((phi + 4.0 * pi) / 3.0) - b_eq / (3.0 * a_eq);

    if (t <= 0.0) {
        throw std::runtime_error("no valid flight time");
    }
        double t2 = t * t;
    double t3 = t2 * t;
    double t4 = t3 * t;
    double t5 = t4 * t;

    double d2 = d * d;
    double d3 = d2 * d;
    double d4 = d3 * d;
    double m2 = m * m;
    double m3 = m2 * m;
    double m4 = m3 * m;
    double l2 = l * l;
    double l3 = l2 * l;
    double l4 = l3 * l;
    double l2p1 = 1.0 + l2;

    double term1 = v0 * t;
    double term2 = -t2 * d * v0 / (2.0 * m);
    double term3 = t3 * (6.0 * d * g * l * m - 6.0 * d2 * (l2 - 1.0) * v0) / (36.0 * m2);
    double term4 = t4 *
                   (-6.0 * d2 * g * l * (1.0 + l2 + l4) * m + 3.0 * d3 * l2 * l2p1 * v0 +
                    6.0 * d3 * l4 * l2p1 * v0) /
                   (36.0 * l2p1 * l2p1 * m3);
    double term5 = t5 * (3.0 * d3 * g * l3 * m - 3.0 * d4 * l2 * l2p1 * v0) / (36.0 * l2p1 * m4);

    double h = term1 + term2 + term3 + term4 + term5;

    double dx = input.target_x - input.drone_x;
    double dy = input.target_y - input.drone_y;
    double distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= 0.0) {
        throw std::invalid_argument("target coincides with drone position");
    }

    double ratio = (distance - h) / distance;
    double fire_x = input.drone_x + dx * ratio;
    double fire_y = input.drone_y + dy * ratio;

    return DropSolution{fire_x, fire_y};
}

    