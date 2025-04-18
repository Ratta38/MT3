#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
class Math {
public:
	Math();

	/// <summary>
	/// X軸周りの回転行列
	/// </summary>
	/// <param name="theta">角度X</param>
	/// <returns>X軸周りの回転行列</returns>
	static Matrix4x4 MakePitchRotateMatrix(float radian);

	/// <summary>
	/// Y軸周りの回転行列
	/// </summary>
	/// <param name="theta">角度Y</param>
	/// <returns>Y軸周りの回転行列</returns>
	static Matrix4x4 MakeYawRotateMatrix(float radian);

	/// <summary>
	/// Z軸周りの回転行列
	/// </summary>
	/// <param name="theta">角度Z</param>
	/// <returns>Z軸周りの回転行列</returns>
	static Matrix4x4 MakeRollRotateMatrix(float radian);

	/// <summary>
	/// 行列同士の積を求める
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns></returns>
	static Matrix4x4 Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

	/// <summary>
	/// 行列の値を表示
	/// </summary>
	/// <param name="x">座標 X</param>
	/// <param name="y">座標 Y</param>
	/// <param name="matrix">行列</param>
	/// <param name="label">関数名</param>
	static void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);
public:
	static const int kColumnWidth = 60;
	static const int kRowHeight = 20;
};
