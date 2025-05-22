#include "Shape.h"
#include "Math.h"
#include "Vector3.h"
#include <cmath>
#include <numbers>

Shape::Shape() {}

void Shape::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color, FillMode fillMode) {
	Novice::DrawTriangle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), static_cast<int>(x3), static_cast<int>(y3), color, fillMode);
}

void Shape::DrawBox(float x, float y, float w, float h, float angle, unsigned int color, FillMode fillMode) {
	Novice::DrawBox(static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h), angle, color, fillMode);
}

void Shape::DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, unsigned int color, FillMode fillMode) {
	Novice::DrawEllipse(static_cast<int>(x), static_cast<int>(y), static_cast<int>(radiusX), static_cast<int>(radiusY), angle, color, fillMode);
}

void Shape::DrawLine(float x1, float y1, float x2, float y2, unsigned int color) { Novice::DrawLine(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), color); }

void Shape::DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float srcX, float srcY, float srcW, float srcH, int textureHandle, unsigned int color) {
	Novice::DrawQuad(
	    static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), static_cast<int>(x3), static_cast<int>(y3), static_cast<int>(x4), static_cast<int>(y4),
	    static_cast<int>(srcX), static_cast<int>(srcY), static_cast<int>(srcW), static_cast<int>(srcH), textureHandle, color);
}

void Shape::DrawSprite(float x, float y, int textureHandle, float scaleX, float scaleY, float angle, unsigned int color) {
	Novice::DrawSprite(static_cast<int>(x), static_cast<int>(y), textureHandle, scaleX, scaleY, angle, color);
}

void Shape::DrawSpriteRect(float destX, float destY, float srcX, float srcY, float srcW, float srcH, int textureHandle, float scaleX, float scaleY, float angle, unsigned int color) {
	Novice::DrawSpriteRect(
	    static_cast<int>(destX), static_cast<int>(destY), static_cast<int>(srcX), static_cast<int>(srcY), static_cast<int>(srcW), static_cast<int>(srcH), textureHandle, scaleX, scaleY, angle, color);
}

void Shape::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;                                                   // Gridの半分の幅
	const uint32_t kSubdivision = 10;                                                    // 分割数
	const float kGridEvery = (kGridHalfWidth + 2.0f) / static_cast<float>(kSubdivision); // 1つ分の長さ

	Vector3 worldVerticles[2];
	Vector3 screenVerticles[2];
	Vector3 ndcVertex;

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		// スクリーン座標系まで変換をかける
		// 変換した座標を使って表示、色は灰色(0xAAAAAAFF)、原点は黒ぐらいが良いが、何でもいい
		worldVerticles[0] = {xIndex * kGridEvery - kGridHalfWidth, 0.0f, kGridHalfWidth};
		worldVerticles[1] = {xIndex * kGridEvery - kGridHalfWidth, 0.0f, -kGridHalfWidth};

		for (uint32_t i = 0; i < 2; ++i) {
			ndcVertex = Math::Transform(worldVerticles[i], viewProjectionMatrix);
			screenVerticles[i] = Math::Transform(ndcVertex, viewportMatrix);
		}

		if (xIndex * kGridEvery - kGridHalfWidth == 0.0f) {
			DrawLine(screenVerticles[0].x, screenVerticles[0].y, screenVerticles[1].x, screenVerticles[1].y, 0x000000FF);
		} else {
			DrawLine(screenVerticles[0].x, screenVerticles[0].y, screenVerticles[1].x, screenVerticles[1].y, 0xAAAAAAFF);
		}
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		worldVerticles[0] = {kGridHalfWidth, 0.0f, zIndex * kGridEvery - kGridHalfWidth};
		worldVerticles[1] = {-kGridHalfWidth, 0.0f, zIndex * kGridEvery - kGridHalfWidth};

		for (uint32_t i = 0; i < 2; ++i) {
			ndcVertex = Math::Transform(worldVerticles[i], viewProjectionMatrix);
			screenVerticles[i] = Math::Transform(ndcVertex, viewportMatrix);
		}

		if (zIndex * kGridEvery - kGridHalfWidth == 0.0f) {
			DrawLine(screenVerticles[0].x, screenVerticles[0].y, screenVerticles[1].x, screenVerticles[1].y, 0x000000FF);
		} else {
			DrawLine(screenVerticles[0].x, screenVerticles[0].y, screenVerticles[1].x, screenVerticles[1].y, 0xAAAAAAFF);
		}
	}
}

void Shape::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 16;                                                                       // 分割数
	const float kLonEvery = 2.0f * static_cast<float>(std::numbers::pi) / static_cast<float>(kSubdivision); // 軽度分割1つ文の角度
	const float kLatEvery = static_cast<float>(std::numbers::pi) / static_cast<float>(kSubdivision);        // 緯度分割1つ文の角度
	// 緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -static_cast<float>(std::numbers::pi) / 2.0f + kLatEvery * latIndex; // 現在の緯度
		// 経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度
			// world座標系でのa,b,cを求める
			Vector3 a, b, c;
			a = {sphere.radius * std::cosf(lat) * std::cosf(lon), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon)};

			a = Math::Add(a, sphere.center);

			b = {sphere.radius * std::cosf(lat + kLatEvery) * std::cosf(lon), sphere.radius * std::sinf(lat + kLatEvery), sphere.radius * std::cosf(lat + kLatEvery) * std::sinf(lon)};

			b = Math::Add(b, sphere.center);

			c = {sphere.radius * std::cosf(lat) * std::cosf(lon + kLonEvery), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery)};

			c = Math::Add(c, sphere.center);

			// a,b,cをScreen座標系で参照...
			a = Math::Transform(a, viewProjectionMatrix);
			a = Math::Transform(a, viewportMatrix);
			b = Math::Transform(b, viewProjectionMatrix);
			b = Math::Transform(b, viewportMatrix);
			c = Math::Transform(c, viewProjectionMatrix);
			c = Math::Transform(c, viewportMatrix);

			// ab,bcで線を引く
			DrawLine(a.x, a.y, b.x, b.y, color);
			DrawLine(c.x, c.y, a.x, a.y, color);
		}
	}
}

void Shape::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) { 
	Vector3 center = Math::Multiply(plane.distance, plane.normal); 
	Vector3 perpendiculars[4];
	perpendiculars[0] = Math::Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = {-perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z};
	perpendiculars[2] = Math::Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = {-perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z};

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Math::Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Math::Add(center, extend);
		points[index] = Math::Transform(Math::Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	DrawLine(points[0].x, points[0].y, points[2].x, points[2].y, color);
	DrawLine(points[1].x, points[1].y, points[3].x, points[3].y, color);
	DrawLine(points[2].x, points[2].y, points[1].x, points[1].y, color);
	DrawLine(points[3].x, points[3].y, points[0].x, points[0].y, color);
}

Vector3 Shape::Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return {-vector.y, vector.x, 0.0f};
	}
	return {0.0f, -vector.z, vector.y};
}
