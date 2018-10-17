#include <random>
#include <iostream>

#include "math/ray.h"
#include "sphere.h"
#include "scene.h"
#include "camera.h"
#include "ppm.h"

std::random_device rd;
std::mt19937 engine(rd());
std::uniform_real_distribution<float> dist(0, 1);

Vector3f random_point_in_unit_sphere() {
	Vector3f p;
	do {
		p = 2.0f * Vector3f(dist(engine), dist(engine), dist(engine)) -
			Vector3f(1, 1, 1);
	} while (p * p >= 1);
	return p;
}

Vector3f compute_color(const Scene &scene, const Rayf &ray) {
	RaycastHit hit;
	if (scene.raycast(ray, &hit)) {
		Vector3f hitPoint = ray.point(hit.distance);
		Vector3f newDirection = hit.normal + random_point_in_unit_sphere();
		Rayf newRay(hitPoint, newDirection);
		return 0.5f * compute_color(scene, newRay);
	}

	// background color
	float k = 0.5f * (ray.direction()[1] + 1);
	return (1 - k) * Vector3f(1, 1, 1) + k * Vector3f(0.5f, 0.7f, 1);
}

void render(const Scene &scene, const Camera &camera, Image &image) {
	size_t w = image.width(), h = image.height(), sampleCount = 16;

	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			Vector3f color;
			for (size_t s = 0; s < sampleCount; s++) {
				float u = float(j + dist(engine)) / w,
					  v = float(h - i - 1 - dist(engine)) / h;
				Rayf ray = camera.genRay(u, v);
				color += compute_color(scene, ray);
			}
			color /= sampleCount;
			// gamma approximation
			color = Vector3f(std::sqrt(color[0]), std::sqrt(color[1]),
							 std::sqrt(color[2]));
			image(i, j) = Pixel(255.99f * color[0], 255.99f * color[1],
								255.99f * color[2]);
		}
	}
}

int main() {
	Sphere sphere1({0, 0, -1}, 0.5f);
	Sphere sphere2({0, -100.5f, -1}, 100);

	Scene scene;
	scene.shapes.push_back(&sphere1);
	scene.shapes.push_back(&sphere2);

	Camera camera;
	Image image(640, 360);

	render(scene, camera, image);

	PPMWriter ppmWriter;
	ImageWriter *imgWriter = &ppmWriter;
	imgWriter->write("scene", image);
	return 0;
}
