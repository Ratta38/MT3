#pragma once
#include "Math.h"
#include "Matrix4x4.h"
#include "Vector3.h"

inline Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Math::Add(v1, v2); }
inline Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Math::Subtract(v1, v2); }
inline Vector3 operator*(float s, const Vector3& v) { return Math::Multiply(s, v); }
inline Vector3 operator*(const Vector3& v, float s) { return s * v; }
inline Vector3 operator/(const Vector3& v, float s) { return Math::Multiply(1.0f / s, v); }

inline Vector3 operator-(const Vector3& v) { return {-v.x, -v.y, -v.z}; }
inline Vector3 operator+(const Vector3& v) { return v; }

inline Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Math::Add(m1, m2); }
inline Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Math::Subtract(m1, m2); }
inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Math::Multiply(m1, m2); }