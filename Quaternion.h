#pragma once
#include <cmath>

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;

	Quaternion Normalized() const {
		float lenSq = x * x + y * y + z * z + w * w;

		// ゼロ除算防止
		if (lenSq < 1e-8f) {
			// 単位クォータニオンを返す
			return Quaternion{0.0f, 0.0f, 0.0f, 1.0f};
		}

		float invLen = 1.0f / std::sqrt(lenSq);

		return Quaternion{x * invLen, y * invLen, z * invLen, w * invLen};
	}
};
