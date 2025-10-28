#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>
#include <memory>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
	public:
		std::vector<shared_ptr<Hittable>> objects;

		HittableList() {}
		HittableList(shared_ptr<Hittable> object) {
			add(object);
		}

		void clear() {
			objects.clear();
		}

		void add(shared_ptr<Hittable> object) {
			objects.push_back(object);
		}

		/// `HitRecord` is updated with the closest hit information.
		bool hit(const Ray& r, double min_dist, double max_dist, HitRecord& rec) const override {
			HitRecord temp_rec;
			bool hit_any = false;
			auto closest_dist = max_dist;

			for (const auto& obj : objects) {
				if (obj->hit(r, min_dist, closest_dist, temp_rec)) {
					hit_any = true;
					closest_dist = temp_rec.dist;
					rec = temp_rec;
				}
            }

			return hit_any;
		}
};

#endif
