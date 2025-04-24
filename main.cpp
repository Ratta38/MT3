#include "Math.h"
#include "Shape.h"
#include "Vector3.h"
#include "WindowSize.h"
#include "Sphere.h"
#include <Novice.h>
#include <imgui.h>

const char kWindowTitle[] = "LE2B_23_ミハラ_ユウタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraTranslate = {0.0f, 1.9f, -6.49f};
	Vector3 cameraRotate = {0.26f, 0.0f, 0.0f};

	Sphere sphere;
	sphere.center = {0.0f, 0.0f, 0.0f};
	sphere.radius = 1.0f;

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
		// WVPMatrixを作る
		Matrix4x4 worldViewProjectionMatrix = Math::Multiply(worldMatrix, Math::Multiply(viewMatrix, projectionMatrix));
		// ViewportMatrixを作る
		Matrix4x4 viewportMatrix = Math::MakeViewPortMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);

#ifdef _DEBUG
		// カメラ座標
		ImGui::DragFloat3("cameraPosition", &cameraTranslate.x, 0.01f);
		// カメラ角度
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		// 球体の座標
		ImGui::DragFloat3("SpherePosition", &sphere.center.x, 0.01f);
		// 球体の半径
		ImGui::DragFloat("SphereSize", &sphere.radius, 0.01f);
#endif // _DEBUG

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Shape::DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		Shape::DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, BLACK);

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
