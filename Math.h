#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
class Math {
public:
	Math();

	/// <summary>
	/// 平行移動行列
	/// </summary>
	/// <param name="translate">座標</param>
	/// <returns>平行移動行列</returns>
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// 拡大縮小行列
	/// </summary>
	/// <param name="scale">大きさ</param>
	/// <returns>拡大縮小行列</returns>
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// スクリーン座標系へ変換
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <param name="matrix">行列</param>
	/// <returns>変換後の座標</returns>
	static Vector3 Transform(Vector3& vector, Matrix4x4& matrix);

	/// <summary>
	/// 3次元ベクトルの数値表示
	/// </summary>
	/// <param name="x">座標 X</param>
	/// <param name="y">座標 Y</param>
	/// <param name="vector">ベクトル</param>
	/// <param name="label">使用した関数名</param>
	static void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);


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
