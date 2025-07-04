#include "Collision.h"
#include "Math.h"
#include "MathOperator.h"
#include "Plane.h"
#include "Shape.h"
#include "Sphere.h"
#include "Vector3.h"
#include "WindowSize.h"
#include <Novice.h>
#include <imgui.h>
#undef min
#undef max
#include <algorithm>

const char kWindowTitle[] = "LE2B_23_ミハラ_ユウタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// カメラ
	Vector3 cameraTranslate = {0.0f, 10.0f, -6.5f};
	Vector3 cameraRotate = {1.0f, 0.0f, 0.0f};

	Vector3 a{0.2f, 1.0f, 0.0f};
	Vector3 b{2.4f, 3.1f, 1.2f};
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 f = a / 2.0f;
	Vector3 g = +b;
	Vector3 h = -b;
	Vector3 i = a += b;
	Vector3 j = a -= b;
	Vector3 k = a *= 3.0f;
	Vector3 l = a /= 2.0f;

	Vector3 rotate{0.4f, 1.43f, -0.8f};
	Matrix4x4 rotateXMatrix = Math::MakePitchRotateMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = Math::MakePitchRotateMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = Math::MakePitchRotateMatrix(rotate.z);
	Matrix4x4 rotateMatrixMul = rotateXMatrix * rotateYMatrix * rotateZMatrix;
	Matrix4x4 rotateMatrixAdd = rotateXMatrix + rotateYMatrix + rotateZMatrix;
	Matrix4x4 rotateMatrixSub = rotateXMatrix - rotateYMatrix - rotateZMatrix;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 worldMatrix = Math::MakeAffineMatrix({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
		Matrix4x4 cameraMatrix = Math::MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Math::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = Math::MakePerspectiveFovMatrix(0.45f, (1280.0f / 720.0f), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Math::Multiply(viewMatrix, projectionMatrix);
		// WVPMatrixを作る
		Matrix4x4 worldViewProjectionMatrix = Math::Multiply(worldMatrix, viewProjectionMatrix);
		// ViewportMatrixを作る
		Matrix4x4 viewportMatrix = Math::MakeViewPortMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);

#ifdef _DEBUG
		ImGui::Begin("Window");
		ImGui::Text("c:%f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d:%f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e:%f, %f, %f", e.x, e.y, e.z);
		ImGui::Text("f:%f, %f, %f", f.x, f.y, f.z);
		ImGui::Text("g:%f, %f, %f", g.x, g.y, g.z);
		ImGui::Text("h:%f, %f, %f", h.x, h.y, h.z);
		ImGui::Text("i:%f, %f, %f", i.x, i.y, i.z);
		ImGui::Text("j:%f, %f, %f", j.x, j.y, j.z);
		ImGui::Text("k:%f, %f, %f", k.x, k.y, k.z);
		ImGui::Text("l:%f, %f, %f", l.x, l.y, l.z);
		ImGui::Text(
		    "matrixMul:\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n", rotateMatrixMul.m[0][0], rotateMatrixMul.m[0][1], rotateMatrixMul.m[0][2], rotateMatrixMul.m[0][3], rotateMatrixMul.m[1][0],
		    rotateMatrixMul.m[1][1], rotateMatrixMul.m[1][2], rotateMatrixMul.m[1][3], rotateMatrixMul.m[2][0], rotateMatrixMul.m[2][1], rotateMatrixMul.m[2][2], rotateMatrixMul.m[2][3],
		    rotateMatrixMul.m[3][0], rotateMatrixMul.m[3][1], rotateMatrixMul.m[3][2], rotateMatrixMul.m[3][3]);
		ImGui::Text(
		    "matrixAdd:\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n", rotateMatrixAdd.m[0][0], rotateMatrixAdd.m[0][1], rotateMatrixAdd.m[0][2], rotateMatrixAdd.m[0][3], rotateMatrixAdd.m[1][0],
		    rotateMatrixAdd.m[1][1], rotateMatrixAdd.m[1][2], rotateMatrixAdd.m[1][3], rotateMatrixAdd.m[2][0], rotateMatrixAdd.m[2][1], rotateMatrixAdd.m[2][2], rotateMatrixAdd.m[2][3],
		    rotateMatrixAdd.m[3][0], rotateMatrixAdd.m[3][1], rotateMatrixAdd.m[3][2], rotateMatrixAdd.m[3][3]);
		ImGui::Text(
		    "matrixSub:\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n", rotateMatrixSub.m[0][0], rotateMatrixSub.m[0][1], rotateMatrixSub.m[0][2], rotateMatrixSub.m[0][3], rotateMatrixSub.m[1][0],
		    rotateMatrixSub.m[1][1], rotateMatrixSub.m[1][2], rotateMatrixSub.m[1][3], rotateMatrixSub.m[2][0], rotateMatrixSub.m[2][1], rotateMatrixSub.m[2][2], rotateMatrixSub.m[2][3],
		    rotateMatrixSub.m[3][0], rotateMatrixSub.m[3][1], rotateMatrixSub.m[3][2], rotateMatrixSub.m[3][3]);
		ImGui::End();

#endif // _DEBUG

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド
		Shape::DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
