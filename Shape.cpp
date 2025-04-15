#include "Shape.h"

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
