#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
class Math {
public:
	Math();

	/// <summary>
	/// 行列同士の加算
	/// </summary>
	/// <param name="m1">行列1</param>
	/// <param name="m2">行列2</param>
	/// <returns>加算結果</returns>
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 行列同士の減算
	/// </summary>
	/// <param name="m1">行列1</param>
	/// <param name="m2">行列2</param>
	/// <returns>減算結果</returns>
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 転置行列
	/// </summary>
	/// <param name="m">行列</param>
	/// <returns>転置行列</returns>
	static Matrix4x4 Transpose(const Matrix4x4& m);

	/// <summary>
	/// 単位行列の作成
	/// </summary>
	/// <returns>単位行列</returns>
	static Matrix4x4 MakeIdentity4x4();

	/// <summary>
	/// 行列の値を表示
	/// </summary>
	/// <param name="x">座標 X</param>
	/// <param name="y">座標 Y</param>
	/// <param name="matrix">行列</param>
	/// <param name="label">関数名</param>
	static void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

	/// <summary>
	/// 行列同士の積を求める
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns></returns>
	static Matrix4x4 Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="matrix">行列</param>
	/// <returns>逆行列</returns>
	static Matrix4x4 Inverse(const Matrix4x4& matrix);

public:
	static const int kColumnWidth = 60;

private:
	static const int kRowHeight = 20;
};
