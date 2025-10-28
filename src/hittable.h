#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class HitRecord {
	public:
		Point3 hit_pos;
		Vec3 normal;
		double dist;
		bool is_front_face;

		void set_face_normal(const Ray& r, const Vec3& outward_normal) {
			is_front_face = dot(r.direction(), outward_normal) < 0;
			normal = is_front_face ? outward_normal : -outward_normal;
		}
};

class Hittable {
	public:
		virtual ~Hittable() = default;

		virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

#endif
