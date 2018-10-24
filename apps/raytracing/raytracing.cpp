#include "math/ray.h"
#include "random.h"
#include "sphere.h"
#include "scene.h"
#include "camera.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"
#include "ppm.h"

Vector3f compute_color(const Scene &scene, const Rayf &ray, size_t depth) {
	RaycastHit hit;
	if (scene.raycast(ray, &hit)) {
		Rayf scattered;
		Vector3f attenuation;
		if (depth < 50 &&
			hit.material->scatter(ray, hit, attenuation, scattered)) {
			return attenuation.pointwise(
				compute_color(scene, scattered, depth + 1));
		}
		return Vector3f(0, 0, 0);
	}

	// background color
	float k = 0.5f * (ray.direction()[1] + 1);
	return (1 - k) * Vector3f(1, 1, 1) + k * Vector3f(0.5f, 0.7f, 1);
}

void render(const Scene &scene, const Camera &camera, Image &image) {
	RandomNumberGenerator<float> randGen(0, 1);
	size_t w = image.width(), h = image.height(), sampleCount = 16;

	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			Vector3f color;
			for (size_t s = 0; s < sampleCount; s++) {
				float u = float(j + randGen()) / w,
					  v = float(h - i - 1 - randGen()) / h;
				Rayf ray = camera.genRay(u, v);
				color += compute_color(scene, ray, 0);
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
	Lambertian lamb1({0.8f, 0.3f, 0.3f});
	Lambertian lamb2({0.8f, 0.8f, 0});
	Metal metal1({0.8f, 0.6f, 0.2f}, 0.2f);
	Dielectric diele1(1.5f);

	Sphere sphere1({0, 0, -1}, 0.5f, lamb1);
	Sphere sphere2({0, -100.5f, -1}, 100, lamb2);
	Sphere sphere3({1, 0, -1}, 0.5f, metal1);
	Sphere sphere4({-1, 0, -1}, 0.5f, diele1);

	Scene scene;
	scene.shapes.push_back(&sphere1);
	scene.shapes.push_back(&sphere2);
	scene.shapes.push_back(&sphere3);
	scene.shapes.push_back(&sphere4);

	Camera camera;
	Image image(640, 360);

	render(scene, camera, image);

	PPMWriter ppmWriter;
	ImageWriter *imgWriter = &ppmWriter;
	imgWriter->write("scene", image);
	return 0;
}
