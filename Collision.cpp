#include "Collision.h"
#include "Math.h"
#include <algorithm>
#include <cmath>

bool Collision::Intersect(const Sphere& s1, const Sphere& s2) {
	float distanceX = s1.center.x - s2.center.x;
	float distanceY = s1.center.y - s2.center.y;
	float distanceZ = s1.center.z - s2.center.z;
	float distance = std::sqrtf(distanceX * distanceX + distanceY * distanceY + distanceZ * distanceZ);

	if (distance <= s1.radius + s2.radius) {
		return true;
	}
	return false;
}

bool Collision::Intersect(const Sphere& sphere, const Plane& plane) {
	float distance = Math::Dot(sphere.center, plane.normal) - plane.distance;

	if (std::abs(distance) <= sphere.radius) {
		return true;
	}
	return false;
}

bool Collision::Intersect(const Segment& segment, const Plane& plane) {
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

bool Collision::Intersect(const Triangle& triangle, const Segment& segment) {

	Vector3 v0 = triangle.vertices[0];
	Vector3 v1 = triangle.vertices[1];
	Vector3 v2 = triangle.vertices[2];

	Vector3 v01 = Math::Subtract(v1, v0);
	Vector3 v12 = Math::Subtract(v2, v1);
	Vector3 v20 = Math::Subtract(v0, v2);

	Plane plane = {};
	plane.normal = Math::Normalize(Math::Cross(v01, v12));
	plane.distance = Math::Dot(v0, plane.normal);

	float dot = Math::Dot(segment.diff, plane.normal);

	if (dot == 0) {
		return false;
	}

	float t = (plane.distance - Math::Dot(segment.origin, plane.normal)) / dot;
	if (0 <= t && t <= 1) {
		Vector3 p = Math::Add(segment.origin, Math::Multiply(t, segment.diff));

		Vector3 v0p = Math::Subtract(p, v0);
		Vector3 v1p = Math::Subtract(p, v1);
		Vector3 v2p = Math::Subtract(p, v2);

		// 各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
		Vector3 cross01 = Math::Cross(v01, v1p);
		Vector3 cross12 = Math::Cross(v12, v2p);
		Vector3 cross20 = Math::Cross(v20, v0p);

		// すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
		if (Math::Dot(cross01, plane.normal) >= 0.0f && Math::Dot(cross12, plane.normal) >= 0.0f && Math::Dot(cross20, plane.normal) >= 0.0f) {
			// 衝突
			return true;
		}
	}

	// 衝突なし
	return false;
}

bool Collision::Intersect(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && // x軸
	    (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) && // y軸
	    (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) { // z軸
		// 衝突
		return true;
	}

	// 衝突なし
	return false;
}

bool Collision::Intersect(const AABB& aabb, const Sphere& sphere) {
	// 最近接点を求める
	Vector3 closestPoint{std::clamp(sphere.center.x, aabb.min.x, aabb.max.x), std::clamp(sphere.center.y, aabb.min.y, aabb.max.y), std::clamp(sphere.center.z, aabb.min.z, aabb.max.z)};

	// 最近接点との距離を求める
	float distance = Math::Length(Math::Subtract(closestPoint, sphere.center));

	// 距離が半径よりも小さければ衝突
	if (distance <= sphere.radius) {
		// 衝突
		return true;
	}

	// 衝突なし
	return false;
}

bool Collision::Intersect(const AABB& aabb, const Segment& segment) {
	// 各軸の衝突点　近い方
	Vector3 tNear = {
	    (aabb.min.x - segment.origin.x) / segment.diff.x,
	    (aabb.min.y - segment.origin.y) / segment.diff.y,
	    (aabb.min.z - segment.origin.z) / segment.diff.z,
	};

	// 各軸の衝突点　遠い方
	Vector3 tFar = {
	    (aabb.max.x - segment.origin.x) / segment.diff.x,
	    (aabb.max.y - segment.origin.y) / segment.diff.y,
	    (aabb.max.z - segment.origin.z) / segment.diff.z,
	};

	// 入れ替え
	if (tNear.x > tFar.x) {
		std::swap(tNear.x, tFar.x);
	}
	if (tNear.y > tFar.y) {
		std::swap(tNear.y, tFar.y);
	}
	if (tNear.z > tFar.z) {
		std::swap(tNear.z, tFar.z);
	}

	// AABBとの衝突点(貫通点)のtが小さい方
	float tmin = std::max(std::max(tNear.x, tNear.y), tNear.z);
	// AABBとの衝突点(貫通点)のtが小さい方
	float tmax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tmin <= tmax && tmin <= 1.0f && tmax >= 0.0f) {
		// 衝突
		return true;
	}

	return false;
}
