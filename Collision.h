#pragma once
#include "AABB.h"
#include "Plane.h"
#include "Segment.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Capsule.h"
namespace Collision {

// 汎用テンプレート
template<typename T1, typename T2> bool Intersect(const T1& a, const T2& b) {
	static_assert(sizeof(T1) == 0, "IsCollision not implemented for these types.");
	return false;
}

bool Intersect(const Sphere& s1, const Sphere& s2);
bool Intersect(const Sphere& sphere, const Plane& plane);
bool Intersect(const Segment& segment, const Plane& plane);
bool Intersect(const Triangle& triangle, const Segment& segment);
bool Intersect(const AABB& aabb1, const AABB& aabb2);
bool Intersect(const AABB& aabb, const Sphere& sphere);
bool Intersect(const AABB& aabb, const Segment& segment);
bool Intersect(const Capsule& capsule, const Plane& plane);
}; // namespace Collision