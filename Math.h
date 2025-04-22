#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
class Math {
public:
	Math();

	/// <summary>
	/// 行列同士の積を求める
	/// </summary>
	/// <param name="matrix1">行列1</param>
	/// <param name="matrix2">行列2</param>
	/// <returns></returns>
	static Matrix4x4 Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

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
	/// アフィン行列
	/// </summary>
	/// <param name="scale">大きさ</param>
	/// <param name="rotate">角度</param>
	/// <param name="translate">座標</param>
	/// <returns>アフィン行列</returns>
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="matrix">行列</param>
	/// <returns>逆行列</returns>
	static Matrix4x4 Inverse(const Matrix4x4& matrix);

	/// <summary>
	/// スクリーン座標系へ変換
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <param name="matrix">行列</param>
	/// <returns>変換後の座標</returns>
	static Vector3 Transform(Vector3& vector, Matrix4x4& matrix);

	/// <summary>
	/// クロス積を求める関数
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	/// <returns>クロス積</returns>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 正射影行列
	/// </summary>
	/// <param name="left">左端</param>
	/// <param name="right">右端</param>
	/// <param name="top">上端</param>
	/// <param name="bottom">下端</param>
	/// <param name="nearClip">近平面への距離</param>
	/// <param name="farClip">遠平面への距離</param>
	/// <returns>正規化デバイス座標系</returns>
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	/// <summary>
	/// 透視投影行列（同次クリップへの変換）
	/// </summary>
	/// <param name="fovY">画角Y</param>
	/// <param name="aspectRatio">アスペクト比</param>
	/// <param name="nearClip">近平面への距離</param>
	/// <param name="farClip">遠平面への距離</param>
	/// <returns>正規化デバイス座標系</returns>
	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	/// <summary>
	/// ビューポート変換（スクリーン座標系への変換）
	/// </summary>
	/// <param name="left">左</param>
	/// <param name="top">上</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <param name="minD">最小深度値</param>
	/// <param name="maxD">最大深度値</param>
	/// <returns>スクリーン座標系</returns>
	static Matrix4x4 MakeViewPortMatrix(float left, float top, float width, float height, float minD, float maxD);

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
