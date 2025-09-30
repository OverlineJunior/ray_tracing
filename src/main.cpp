#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

double hit_sphere(const Point3& center, double radius, const Ray& r) {
  Vec3 oc = center - r.origin();
  auto a = r.direction().length_squared();
  auto h = dot(r.direction(), oc);
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = h * h - a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (h - sqrt(discriminant)) / a;
  }
}

Color ray_color(const Ray &r) {
  // Grande em cima.
  double sphere3 = hit_sphere(Point3(1, 0.6, -1), 0.5, r);
  if (sphere3 > 0.0) {
    Vec3 normal = unit_vector(r.at(sphere3) - Vec3(1, 0.6, -1));
    return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  // Grande um pouco à direita.
  double sphere1 = hit_sphere(Point3(0.3, 0, -1.3), 0.5, r);
  if (sphere1 > 0.0) {
    Vec3 normal = unit_vector(r.at(sphere1) - Vec3(0.3, 0, -1.3));
    return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  double t = hit_sphere(Point3(0, 0, -1), 0.5, r);
  if (t > 0.0) {
    Vec3 normal = unit_vector(r.at(t) - Vec3(0, 0, -1));
    return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  // Pequena um pouco à esquerda.
  double sphere2 = hit_sphere(Point3(0, 0, -0.3), 0.2, r);
  if (sphere2 > 0.0) {
    Vec3 normal = unit_vector(r.at(sphere2) - Vec3(0, 0, -0.3));
    return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  double ground = hit_sphere(Point3(0, -100.5, -1), 100, r);
  if (ground > 0.0) {
    Vec3 normal = unit_vector(r.at(ground) - Vec3(0, -100.5, -1));
    return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  Vec3 unit_dir = unit_vector(r.direction());
	auto a = 0.5 * (unit_dir.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
  // Camera //

  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width) / image_height);

  auto camera_center = Point3(0, 2, -1);

  auto lookat = Point3(0, 0, -1);
  auto vup = Vec3(0, 0, 1);

  Vec3 w = unit_vector(camera_center - lookat);
  Vec3 u = unit_vector(cross(vup, w));
  Vec3 v = cross(w, u);

  // vetores da viewport
  auto viewport_u = -viewport_width * u;
  auto viewport_v = viewport_height * -v;

  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  auto viewport_upper_left = camera_center - w - viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Render //

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    for (int i = 0; i < image_width; i++) {
      auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_dir = pixel_center - camera_center;
			auto r = Ray(camera_center, ray_dir);

			Color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
}
