#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using Color = Vec3;

inline void write_color(std::ostream &out, Color pixel_color) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	int r_byte = int(255.999 * r);
	int g_byte = int(255.999 * g);
	int b_byte = int(255.999 * b);

	out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}

#endif
