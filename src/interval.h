#ifndef INTERVAL_H
#define INTERVAL_H

#include "util.h"

class Interval {
	public:
		double min;
		double max;

		Interval() : min(INF), max(-INF) {}
		Interval(double min, double max) : min(min), max(max) {}

		double size() const {
			return max - min;
		}

		bool contains(double x) const {
			return x >= min && x <= max;
		}

		bool surrounds(double x) const {
			return x > min && x < max;
		}

		double clamp(double x) const {
			if (x < min) return min;
			if (x > max) return max;
			return x;
		}

		static const Interval empty, universe;
};

inline const Interval Interval::empty = Interval(INF, -INF);
inline const Interval Interval::universe = Interval(-INF, INF);

#endif
