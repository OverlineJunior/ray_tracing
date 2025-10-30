#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class Camera {
	public:
		double aspect_ratio = 1.0;
		int image_width = 100;
		int samples_per_pixel = 10;

		void render(const Hittable& world) {
			initialize();

			std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

			for (int j = 0; j < image_height; j++) {
				for (int i = 0; i < image_width; i++) {
					Color pixel_color(0, 0, 0);
					for (int s = 0; s < samples_per_pixel; s++) {
						Ray r = get_ray(i, j);
						pixel_color += ray_color(r, world);
					}

					write_color(std::cout, pixel_samples_scale * pixel_color);
				}
			}
        }

	private:
		int image_height;
		double pixel_samples_scale;
		Point3 center;
		Point3 pixel00_loc;
		Vec3 pixel_delta_u;
		Vec3 pixel_delta_v;

		void initialize() {
			image_height = int(image_width / aspect_ratio);
			image_height = image_height < 1 ? 1 : image_height;

			pixel_samples_scale = 1.0 / samples_per_pixel;

			center = Point3(0, 0, 0);

			auto focal_length = 1.0;
			auto viewport_height = 2.0;
			auto viewport_width = viewport_height * (double(image_width) / image_height);

			auto viewport_u = Vec3(viewport_width, 0, 0);
			auto viewport_v = Vec3(0, -viewport_height, 0);

			pixel_delta_u = viewport_u / image_width;
			pixel_delta_v = viewport_v / image_height;

			auto viewport_upper_left = center - Vec3(0, 0, focal_length) -
									 viewport_u / 2 - viewport_v / 2;
			pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
		}

		Ray get_ray(int i, int j) const {
			auto offset = sample_square();
			auto pixel_sample = pixel00_loc
				+ (i + offset.x()) * pixel_delta_u
				+ (j + offset.y()) * pixel_delta_v;

			auto ray_ori = center;
			auto ray_dir = pixel_sample - center;

			return Ray(ray_ori, ray_dir);
		}

		Vec3 sample_square() const {
			return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
		}

		Color ray_color(const Ray &r, const Hittable& world) const {
			HitRecord rec;
			if (world.hit(r, Interval(0, INF), rec)) {
				Vec3 dir = random_on_hemisphere(rec.normal);
				return 0.5 * ray_color(Ray(rec.hit_pos, dir), world);
			}

			Vec3 unit_dir = unit_vector(r.direction());
			auto a = 0.5 * (unit_dir.y() + 1.0);
			return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
        }
};

#endif
