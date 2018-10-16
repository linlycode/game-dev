#include <iostream>

#include "math/ray.h"
#include "sphere.h"
#include "ppm.h"

Vector3f compute_color(const Rayf &ray) {
	Sphere sphere({0, 0, -1}, 0.5f);
	RaycastHit hit;
	if (sphere.raycast(ray, &hit)) {
		return 0.5f * (hit.normal + Vector3f(1, 1, 1));
	}

	// background color
	float k = 0.5f * (ray.direction()[1] + 1);
	return (1 - k) * Vector3f(1, 1, 1) + k * Vector3f(0.5f, 0.7f, 1);
}

void render(Image &image) {
	size_t w = image.width(), h = image.height();

	Vector3f lowerLeft(-2, -1, -1), horizontal(4, 0, 0), vertical(0, 2, 0),
		origin;

	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			float u = float(j) / w, v = float(h - i - 1) / h;
			Vector3f direction = lowerLeft + u * horizontal + v * vertical;
			Rayf ray(origin, direction);

			Vector3f c = compute_color(ray);
			image(i, j) = Pixel(255.99f * c[0], 255.99f * c[1], 255.99f * c[2]);
		}
	}
}

int main() {
	Image image(640, 360);

	render(image);

	PPMWriter ppmWriter;
	ImageWriter *imgWriter = &ppmWriter;
	imgWriter->write("scene", image);
	return 0;
}
