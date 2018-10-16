#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "math/ray.h"

class Shape;
class RaycastHit;

struct Scene {
	std::vector<Shape *> shapes;

	bool raycast(const Rayf &ray, RaycastHit *hit) const;
};

#endif
