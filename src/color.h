#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"
#include <iostream>

using Color = Vec3;

inline void write_color(std::ostream &out, Color pixel_color) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	static const Interval intensity(0.0, 0.999);
	int r_byte = int(256 * intensity.clamp(r));
	int g_byte = int(256 * intensity.clamp(g));
	int b_byte = int(256 * intensity.clamp(b));

	out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}

#endif
