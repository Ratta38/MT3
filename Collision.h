#pragma once
#include "Sphere.h"
#include "Plane.h"
#include "Segment.h"
#include "Triangle.h"
#include "AABB.h"
class Collision {
public:
	static bool IsCollision(const Sphere& s1, const Sphere& s2);
	static bool IsCollision(const Sphere& sphere, const Plane& plane);
	static bool IsCollision(const Segment& segment, const Plane& plane);
	static bool IsCollision(const Triangle& triangle, const Segment& segment);
	static bool IsCollision(const AABB& aabb1, const AABB& aabb2);
};
