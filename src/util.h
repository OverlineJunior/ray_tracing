#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double deg_to_rad(double degrees) {
	return degrees * PI / 180.0;
}

#endif
