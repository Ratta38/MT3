#include "Math.h"
#include <Novice.h>
#include <algorithm>
#include <assert.h>
#include <cmath>
Math::Math() {}

Vector3 Math::Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Math::Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 Math::Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

float Math::Dot(const Vector3& v1, const Vector3& v2) {
	float result = 0.0f;
	result += v1.x * v2.x;
	result += v1.y * v2.y;
	result += v1.z * v2.z;
	return result;
}

float Math::Length(const Vector3& v) {
	float result = 0.0f;
	result = sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	return result;
}

Vector3 Math::Normalize(const Vector3& v) {
	float length = 0.0f;
	Vector3 result;

	length = Length(v);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return result;
}

Matrix4x4 Math::Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.m[row][col] = m1.m[row][col] + m2.m[row][col];
		}
	}
	return result;
}

Matrix4x4 Math::Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.m[row][col] = m1.m[row][col] - m2.m[row][col];
		}
	}
	return result;
}

Matrix4x4 Math::Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {
	Matrix4x4 result = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 Math::MakePitchRotateMatrix(float radian) {
	Matrix4x4 result = {};
	result.m[0][0] = 1.0f;
	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = std::sinf(radian);
	result.m[2][1] = -std::sinf(radian);
	result.m[2][2] = std::cosf(radian);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Math::MakeYawRotateMatrix(float radian) {
	Matrix4x4 result = {};
	result.m[0][0] = std::cosf(radian);
	result.m[0][2] = -std::sinf(radian);
	result.m[1][1] = 1.0f;
	result.m[2][0] = std::sinf(radian);
	result.m[2][2] = std::cosf(radian);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Math::MakeRollRotateMatrix(float radian) {
	Matrix4x4 result = {};
	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[1][0] = -std::sinf(radian);
	result.m[1][1] = std::cosf(radian);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Math::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = Multiply(MakePitchRotateMatrix(rotate.x), Multiply(MakeYawRotateMatrix(rotate.y), MakeRollRotateMatrix(rotate.z)));

	result.m[0][0] *= scale.x;
	result.m[0][1] *= scale.x;
	result.m[0][2] *= scale.x;

	result.m[1][0] *= scale.y;
	result.m[1][1] *= scale.y;
	result.m[1][2] *= scale.y;

	result.m[2][0] *= scale.z;
	result.m[2][1] *= scale.z;
	result.m[2][2] *= scale.z;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

Matrix4x4 Math::Inverse(const Matrix4x4& matrix) {
	float a = {
	    1 / ((matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) +
	         (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2])

	         - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) - (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) -
	         (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2])

	         - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]) -
	         (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2])

	         + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) +
	         (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2])

	         + (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1]) +
	         (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2])

	         - (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) -
	         (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2])

	         - (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) -
	         (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0])

	         + (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) +
	         (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]))};

	Matrix4x4 inverseMatrix = {};
	inverseMatrix.m[0][0] =
	    ((matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) + (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2]) -
	     (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) - (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]));
	inverseMatrix.m[0][1] =
	    (-(matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1]) - (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2]) +
	     (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1]) + (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2]));
	inverseMatrix.m[0][2] =
	    ((matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1]) + (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2]) -
	     (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1]) - (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2]));

	inverseMatrix.m[0][3] =
	    (-(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1]) - (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2]) +
	     (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1]) + (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2]));

	inverseMatrix.m[1][0] =
	    (-(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2]) +
	     (matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]));

	inverseMatrix.m[1][1] =
	    ((matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2]) -
	     (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2]));

	inverseMatrix.m[1][2] =
	    (-(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2]) +
	     (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2]));

	inverseMatrix.m[1][3] =
	    ((matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2]) -
	     (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2]));

	inverseMatrix.m[2][0] =
	    ((matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1]) -
	     (matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]));

	inverseMatrix.m[2][1] =
	    (-(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1]) +
	     (matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1]));

	inverseMatrix.m[2][2] =
	    ((matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1]) -
	     (matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0]) - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1]));

	inverseMatrix.m[2][3] =
	    (-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0]) - (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1]) +
	     (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3]) + (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1]));

	inverseMatrix.m[3][0] =
	    (-(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]) - (matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]) +
	     (matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) + (matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]) + (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]));

	inverseMatrix.m[3][1] =
	    ((matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2]) + (matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1]) -
	     (matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0]) - (matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1]));

	inverseMatrix.m[3][2] =
	    (-(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2]) - (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1]) +
	     (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2]) + (matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1]));

	inverseMatrix.m[3][3] =
	    ((matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) + (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) + (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
	     (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) - (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) - (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]));

	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = a * inverseMatrix.m[i][j];
		}
	}

	return result;
}

Vector3 Math::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result = {0};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Vector3 Math::Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
	return result;
}

Matrix4x4 Math::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result = {};
	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 Math::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result = {};
	result.m[0][0] = (1 / aspectRatio) * (1 / tanf(fovY / 2));
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1 / tanf(fovY / 2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	result.m[3][3] = 0.0f;
	return result;
}

Matrix4x4 Math::MakeViewPortMatrix(float left, float top, float width, float height, float minD, float maxD) {
	Matrix4x4 result = {};
	result.m[0][0] = width / 2;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -(height / 2);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxD - minD;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minD;
	result.m[3][3] = 1.0f;
	return result;
}

Vector3 Math::Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};
	float dot = Math::Dot(v1, v2);
	float length = Math::Length(v2);
	float scale = dot / (std::powf(length, 2));

	result.x = scale * v2.x;
	result.y = scale * v2.y;
	result.z = scale * v2.z;
	return result;
}

Vector3 Math::ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 result = {};
	result = Add(segment.origin, Project(Subtract(point, segment.origin), segment.diff));
	return result;
}

Vector3 Math::Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;
	result.x = v1.x + (v2.x - v1.x) * t;
	result.y = v1.y + (v2.y - v1.y) * t;
	result.z = v1.z + (v2.z - v1.z) * t;

	return result;
}

Vector3 Math::Reflect(const Vector3& input, const Vector3& normal) {
	float dotValue = Dot(input, normal);
	Vector3 projection = Multiply(2.0f * dotValue, normal);
	return Subtract(input, projection);
}

Vector3 Math::Multiply(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;

	return result;
}

bool Math::CapsuleCollision(const Sphere& sphere, const Capsule& capsule) {
	Vector3 sphereToCapsuleOrigin = Subtract(sphere.center, capsule.segment.origin);
	Vector3 capsuleAxis = Subtract(capsule.segment.diff, capsule.segment.origin);

	// カプセル軸を正規化
	Vector3 capsuleDirection = Normalize(capsuleAxis);

	// 球の中心をカプセル軸に投影した割合（0〜1）
	float projectionRatio = Dot(sphereToCapsuleOrigin, capsuleDirection) / Length(capsuleAxis);
	projectionRatio = std::clamp(projectionRatio, 0.0f, 1.0f);

	// 線形補間により、カプセル軸上の最近接点を取得
	Vector3 closestPointOnCapsule = Add(Multiply(1.0f - projectionRatio, capsule.segment.origin), Multiply(projectionRatio, capsule.segment.diff));

	// 球の中心との距離を計算
	float centerDistance = Length(Subtract(sphere.center, closestPointOnCapsule));

	// 合計半径以下なら衝突していると判定
	return centerDistance < (sphere.radius + capsule.radius);
}

Matrix4x4 Math::MakeRotateAxisAngle(const Vector3& axis, float angle) {
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	float c = cosf(angle); // cosθ
	float s = sinf(angle); // sinθ
	float t = 1.0f - c;    // 1 - cosθ

	Matrix4x4 result{};

	result.m[0][0] = t * x * x + c;
	result.m[0][1] = t * x * y + s * z;
	result.m[0][2] = t * x * z - s * y;
	result.m[0][3] = 0.0f;

	result.m[1][0] = t * x * y - s * z;
	result.m[1][1] = t * y * y + c;
	result.m[1][2] = t * y * z + s * x;
	result.m[1][3] = 0.0f;

	result.m[2][0] = t * x * z + s * y;
	result.m[2][1] = t * y * z - s * x;
	result.m[2][2] = t * z * z + c;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

void Math::MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * 60, y + row * 20 + 20, "%6.03f", matrix.m[row][column]);
		}
	}
}

Matrix4x4 Math::DirectionToDirection(const Vector3& from, const Vector3& to) {
	float cosTheta = Dot(from, to);

	// 同じ方向の場合
	if (cosTheta >= 1.0f) {
		return Math::MakeIdentity4x4();
	}

	// 真逆の場合
	if (cosTheta <= -1.0f) {
		// fromに直交する軸を適当に選ぶ
		Vector3 ortho = (fabsf(from.x) > fabsf(from.z)) ? Vector3{-from.y, from.x, 0.0f} : Vector3{0.0f, -from.z, from.y};
		Vector3 axis = Normalize(ortho);

		// 180度回転
		float x = axis.x, y = axis.y, z = axis.z;
		float sinTheta = 0.0f;
		float tVal = 1.0f - cosTheta;

		Matrix4x4 result{};
		result.m[0][0] = tVal * x * x + cosTheta;
		result.m[0][1] = tVal * x * y + sinTheta * z;
		result.m[0][2] = tVal * x * z - sinTheta * y;

		result.m[1][0] = tVal * x * y - sinTheta * z;
		result.m[1][1] = tVal * y * y + cosTheta;
		result.m[1][2] = tVal * y * z + sinTheta * x;

		result.m[2][0] = tVal * x * z + sinTheta * y;
		result.m[2][1] = tVal * y * z - sinTheta * x;
		result.m[2][2] = tVal * z * z + cosTheta;

		result.m[3][3] = 1.0f;
		return result;
	}

	// 通常
	Vector3 axis = Normalize(Cross(from, to));
	float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);
	float x = axis.x, y = axis.y, z = axis.z;
	float tVal = 1.0f - cosTheta;

	Matrix4x4 result{};
	result.m[0][0] = tVal * x * x + cosTheta;
	result.m[0][1] = tVal * x * y + sinTheta * z;
	result.m[0][2] = tVal * x * z - sinTheta * y;

	result.m[1][0] = tVal * x * y - sinTheta * z;
	result.m[1][1] = tVal * y * y + cosTheta;
	result.m[1][2] = tVal * y * z + sinTheta * x;

	result.m[2][0] = tVal * x * z + sinTheta * y;
	result.m[2][1] = tVal * y * z - sinTheta * x;
	result.m[2][2] = tVal * z * z + cosTheta;

	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 Math::MakeIdentity4x4() {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; ++i) {
		result.m[i][i] = 1;
	}
	return result;
}

Quaternion Math::Multiply(const Quaternion& lhs, const Quaternion& rhs) {
	return Quaternion(
	    lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y, lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x, lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w,
	    lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
}

Quaternion Math::IdentityQuaternion() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

Quaternion Math::Conjugate(const Quaternion& quaternion) { return Quaternion(-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w); }

float Math::Norm(const Quaternion& quaternion) {
	Quaternion q = quaternion;

	return std::sqrtf(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}

Quaternion Math::Normalize(const Quaternion& quaternion) {
	Quaternion q = quaternion;

	float n = Norm(q);

	if (n == 0.0f)
		return IdentityQuaternion(); // ゼロ除算防止

	return Quaternion(q.x / n, q.y / n, q.z / n, q.w / n);
}

Quaternion Math::Inverse(const Quaternion& quaternion) {
	Quaternion q = quaternion;

	float normSq = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;

	if (normSq == 0.0f)
		return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); // ゼロ除算防止

	Quaternion conj = Conjugate(q);

	return Quaternion(conj.x / normSq, conj.y / normSq, conj.z / normSq, conj.w / normSq);
}

void Math::QuaternionPrint(int x, int y, Quaternion quaternion, const char* label) {
	Novice::ScreenPrintf(x, y, "%6.02f", quaternion.x);
	Novice::ScreenPrintf(x + 60, y, "%6.02f", quaternion.y);
	Novice::ScreenPrintf(x + 120, y, "%6.02f", quaternion.z);
	Novice::ScreenPrintf(x + 180, y, "%6.02f", quaternion.w);
	Novice::ScreenPrintf(x + 240, y, label);
}
