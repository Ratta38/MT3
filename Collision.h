#pragma once
#include "Sphere.h"
#include "Plane.h"
class Collision {
public:
	static bool IsCollision(const Sphere& s1, const Sphere& s2);
	static bool IsCollision(const Sphere& sphere, const Plane& plane);
};
