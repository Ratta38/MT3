#include "Collision.h"
#include "Math.h"
#include <cmath>

bool Collision::IsCollision(const Sphere& s1, const Sphere& s2) { 
	float distanceX = s1.center.x - s2.center.x;
	float distanceY = s1.center.y - s2.center.y;
	float distanceZ = s1.center.z - s2.center.z;
	float distance = std::sqrtf(distanceX * distanceX + distanceY * distanceY + distanceZ * distanceZ);

	if (distance <= s1.radius + s2.radius) {
		return true;
	}
	return false;
}

bool Collision::IsCollision(const Sphere& sphere, const Plane& plane) { 
	float distance = Math::Dot(sphere.center, plane.normal) - plane.distance;

	if (std::abs(distance) <= sphere.radius) {
		return true;
	}
	return false;
}

bool Collision::IsCollision(const Segment& segment, const Plane& plane) { 
	float dot = Math::Dot(segment.diff, plane.normal);

	if (dot == 0) {
		return false;
	}

	float t = (plane.distance - Math::Dot(segment.origin, plane.normal)) / dot;
	if (0 <= t && t <= 1) {
		return true;
	}
	return false;
}