#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
class Math {
public:
	Math();

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
