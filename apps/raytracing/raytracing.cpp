#include <random>
#include <iostream>

#include "math/ray.h"
#include "sphere.h"
#include "scene.h"
#include "camera.h"
#include "ppm.h"

Vector3f compute_color(const Scene &scene, const Rayf &ray) {
	RaycastHit hit;
	if (scene.raycast(ray, &hit)) {
		return 0.5f * (hit.normal + Vector3f(1, 1, 1));
	}

	// background color
	float k = 0.5f * (ray.direction()[1] + 1);
	return (1 - k) * Vector3f(1, 1, 1) + k * Vector3f(0.5f, 0.7f, 1);
}

void render(const Scene &scene, const Camera &camera, Image &image) {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_real_distribution<float> dist(0, 1);

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
