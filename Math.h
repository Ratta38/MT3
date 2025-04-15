#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
class Math {
public:
	Math();

	/// <summary>
	/// ベクトルの加算
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	/// <returns>加算結果</returns>
	static Vector3 Add(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// ベクトルの減算
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	/// <returns>減算結果</returns>
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// ベクトルのスカラー倍
	/// </summary>
	/// <param name="scalar">スカラー</param>
	/// <param name="v">ベクトル</param>
	/// <returns>スカラー倍した値</returns>
	static Vector3 Multiply(float scalar, const Vector3& v);

	/// <summary>
	/// ベクトルの内積
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	/// <returns>内積</returns>
	static float Dot(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// ベクトルの長さ
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>長さ</returns>
	static float Length(const Vector3& v);

	/// <summary>
	/// ベクトルの正規化
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>正規化した値</returns>
	static Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// 3次元ベクトルの数値表示
	/// </summary>
	/// <param name="x">座標 X</param>
	/// <param name="y">座標 Y</param>
	/// <param name="vector">ベクトル</param>
	/// <param name="label">使用した関数名</param>
	static void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

public:
	static const int kColumnWidth = 60;
};
