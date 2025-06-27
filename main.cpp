#include "Collision.h"
#include "Math.h"
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

	Vector3 translates[3] = {
	    {0.2f, 1.0f, 0.0f},
	    {0.4f, 0.0f, 0.0f},
	    {0.3f, 0.0f, 0.0f},
	};

	Vector3 rotates[3] = {
	    {0.0f, 0.0f, -6.0f},
	    {0.0f, 0.0f, -1.4f},
	    {0.0f, 0.0f, 0.0f },
	};

	Vector3 scales[3] = {
	    {1.0f, 1.0f, 1.0f},
	    {1.0f, 1.0f, 1.0f},
	    {1.0f, 1.0f, 1.0f},
	};

	// 肩、肘、手の行列
	Matrix4x4 joints[3]{};

	// sphere
	Sphere sphere[3]{};
	for (uint32_t i = 0; i < 3; ++i) {
		sphere[i].radius = 0.1f;
	}

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

		// アフィン変換
		for (uint32_t i = 0; i < 3; ++i) {
			joints[i] = Math::MakeAffineMatrix(scales[i], rotates[i], translates[i]);
		}

		// 階層構造
		joints[1] = Math::Multiply(joints[1], joints[0]);
		joints[2] = Math::Multiply(joints[2], joints[1]);

		// 球に代入
		for (uint32_t i = 0; i < 3; ++i) {
			sphere[i].center.x = joints[i].m[3][0];
			sphere[i].center.y = joints[i].m[3][1];
			sphere[i].center.z = joints[i].m[3][2];
		}

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
		ImGui::DragFloat3("camera.translate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("camera.rotate", &cameraRotate.x, 0.01f);

		ImGui::DragFloat3("translate[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("rotate[0]", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("scale[0]", &scales[0].x, 0.01f);

		ImGui::DragFloat3("translate[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("rotate[1]", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("scale[1]", &scales[1].x, 0.01f);

		ImGui::DragFloat3("translate[2]", &translates[2].x, 0.01f);
		ImGui::DragFloat3("rotate[2]", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("scale[2]", &scales[2].x, 0.01f);

#endif // _DEBUG

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド
		Shape::DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		// 球の描画
		Shape::DrawSphere(sphere[0], worldViewProjectionMatrix, viewportMatrix, RED);
		Shape::DrawSphere(sphere[1], worldViewProjectionMatrix, viewportMatrix, GREEN);
		Shape::DrawSphere(sphere[2], worldViewProjectionMatrix, viewportMatrix, BLUE);

		Sphere drawSpheres[3]{};
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 screenPos = Math::Transform(sphere[i].center, worldViewProjectionMatrix);
			drawSpheres[i].center = Math::Transform(screenPos, viewportMatrix);
		}

		// 線の描画
		Shape::DrawLine(drawSpheres[0].center.x, drawSpheres[0].center.y, drawSpheres[1].center.x, drawSpheres[1].center.y, WHITE);
		Shape::DrawLine(drawSpheres[1].center.x, drawSpheres[1].center.y, drawSpheres[2].center.x, drawSpheres[2].center.y, WHITE);

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
