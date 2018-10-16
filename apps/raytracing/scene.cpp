#include "shape.h"
#include "scene.h"

bool Scene::raycast(const Rayf &ray, RaycastHit *raycastHit) const {
	RaycastHit hit;
	for (auto shape : shapes) {
		RaycastHit h;
		if (shape->raycast(ray, &h)) {
			if (h.distance < hit.distance || hit.distance < 0) {
				hit = h;
			}
		}
	}

	if (hit.distance > 0) {
		if (raycastHit) {
			*raycastHit = hit;
		}
		return true;
	}
	return false;
}
