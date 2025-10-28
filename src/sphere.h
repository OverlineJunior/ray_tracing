#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
	public:
		Sphere(const Point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

		bool hit(const Ray& r, double min_dist, double max_dist, HitRecord& rec) const override {
			Vec3 oc = center - r.origin();
			auto a = r.direction().length_squared();
			auto h = dot(r.direction(), oc);
			auto c = oc.length_squared() - radius * radius;

			auto discriminant = h * h - a * c;
			if (discriminant < 0) {
				return false;
			}

			auto sqrt_d = sqrt(discriminant);

			// Find the nearest root that lies in the acceptable range.
			auto root = (h - sqrt_d) / a;
			if (root <= min_dist || root >= max_dist) {
				root = (h + sqrt_d) / a;
				if (root <= min_dist || root >= max_dist) {
					return false;
				}
			}

			rec.dist = root;
			rec.hit_pos = r.at(rec.dist);
			Vec3 outward_normal = (rec.hit_pos - center) / radius;
			rec.set_face_normal(r, outward_normal);

			return true;
		}

	private:
		Point3 center;
		double radius;
};

#endif
