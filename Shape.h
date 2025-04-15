#pragma once
#include <Novice.h>
class Shape {
public:
	Shape();
	/// <summary>
	/// 三角形を描画する
	/// </summary>
	/// <param name="x1">描画する三角形の頂点1 X</param>
	/// <param name="y1">描画する三角形の頂点1 Y</param>
	/// <param name="x2">描画する三角形の頂点2 X</param>
	/// <param name="y2">描画する三角形の頂点2 Y</param>
	/// <param name="x3">描画する三角形の頂点3 X</param>
	/// <param name="y3">描画する三角形の頂点3 Y</param>
	/// <param name="color">描画する三角形の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color, FillMode fillMode);

	/// <summary>
	/// 四角形を描画する
	/// </summary>
	/// <param name="x">描画する四角形の左上座標 X</param>
	/// <param name="y">描画する四角形の左上座標 Y</param>
	/// <param name="w">描画する四角形の横幅</param>
	/// <param name="h">描画する四角形の縦幅</param>
	/// <param name="angle">描画する四角形の回転角</param>
	/// <param name="color">描画する四角形の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawBox(float x, float y, float w, float h, float angle, unsigned int color, FillMode fillMode);

	/// <summary>
	/// 楕円を描画する
	/// </summary>
	/// <param name="x">楕円の中心座標 X</param>
	/// <param name="y">楕円の中心座標 Y</param>
	/// <param name="radiusX">楕円の半径 X</param>
	/// <param name="radiusY">楕円の半径 Y</param>
	/// <param name="angle">楕円の回転角(rad)</param>
	/// <param name="color">楕円の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, unsigned int color, FillMode fillMode);

	/// <summary>
	/// 線を描画する
	/// </summary>
	/// <param name="x1">描画する線の始点座標</param>
	/// <param name="y1">描画する線の始点座標</param>
	/// <param name="x2">描画する線の終点座標</param>
	/// <param name="y2">描画する線の終点座標</param>
	/// <param name="color">描画する線の色</param>
	static void DrawLine(float x1, float y1, float x2, float y2, unsigned int color);

	/// <summary>
	/// 四角形描画
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標 X</param>
	/// <param name="y1">描画する四角形の左上座標 Y</param>
	/// <param name="x2">描画する四角形の右上座標 X</param>
	/// <param name="y2">描画する四角形の右上座標 Y</param>
	/// <param name="x3">描画する四角形の左下座標 X</param>
	/// <param name="y3">描画する四角形の左下座標 Y</param>
	/// <param name="x4">描画する四角形の右下座標 X</param>
	/// <param name="y4">描画する四角形の右下座標 Y</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	static void DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float srcX, float srcY, float srcW, float srcH, int textureHandle, unsigned int color);

	/// <summary>
	/// スプライトを描画する
	/// </summary>
	/// <param name="x">描画するスプライトの左上座標 X</param>
	/// <param name="y">描画するスプライトの左上座標 Y</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="scaleX">描画するスプライトの倍率 X</param>
	/// <param name="scaleY">描画するスプライトの倍率 Y</param>
	/// <param name="angle">描画するスプライトの回転角</param>
	/// <param name="color">描画するスプライトの色</param>
	static void DrawSprite(float x, float y, int textureHandle, float scaleX, float scaleY, float angle, unsigned int color);

	/// <summary>
	/// スプライトの指定矩形部分のみを描画する
	/// </summary>
	/// <param name="destX">描画するスプライトの左上座標 X</param>
	/// <param name="destY">描画するスプライトの左上座標 Y</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="scaleX">描画するスプライトの倍率 X</param>
	/// <param name="scaleY">描画するスプライトの倍率 Y</param>
	/// <param name="angle">描画するスプライトの回転角</param>
	/// <param name="color">描画するスプライトの色</param>
	static void DrawSpriteRect(float destX, float destY, float srcX, float srcY, float srcW, float srcH, int textureHandle, float scaleX, float scaleY, float angle, unsigned int color);
};
