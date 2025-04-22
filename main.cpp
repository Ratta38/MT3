#include "Math.h"
#include "Shape.h"
#include "Vector3.h"
#include "WindowSize.h"
#include <Novice.h>

const char kWindowTitle[] = "LE2B_23_ミハラ_ユウタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// クロス積
	Vector3 v1{1.2f, -3.9f, 2.5f};
	Vector3 v2{2.8f, 0.4f, -1.3f};
	Vector3 cross = Math::Cross(v1, v2);

	// 三角形
	Vector3 rotate{};
	Vector3 translate{};
	Vector3 kLocalVertices[3] = {
	    -0.5f, -0.5f, 0.0f, // 左下
	    0.0f,  0.5f,  0.0f, // 上
	    0.5f,  -0.5f, 0.0f  // 右下
	};

	// カメラ
	Vector3 cameraPosition{0.0f, 0.0f, -5.0f};

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

		// WSキーで前後に、ADキーで左右に三角形を動かす。Y回転をさせる。
		if (keys[DIK_W]) {
			translate.z += 0.03f;
		}
		if (keys[DIK_S]) {
			translate.z -= 0.03f;
		}
		if (keys[DIK_A]) {
			translate.x -= 0.03f;
		}
		if (keys[DIK_D]) {
			translate.x += 0.03f;
		}

		// 回転処理
		rotate.y += 0.03f;

		Matrix4x4 worldMatrix = Math::MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = Math::MakeAffineMatrix({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, cameraPosition);
		Matrix4x4 viewMatrix = Math::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = Math::MakePerspectiveFovMatrix(0.45f, static_cast<float>(WindowSize::width) / static_cast<float>(WindowSize::height), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Math::Multiply(worldMatrix, Math::Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewprotMatrix = Math::MakeViewPortMatrix(0, 0, static_cast<float>(WindowSize::width), static_cast<float>(WindowSize::height), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Math::Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Math::Transform(ndcVertex, viewprotMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// クロス積
		Math::VectorScreenPrintf(0, 0, cross, "Cross");

		// 三角形
		Shape::DrawTriangle(screenVertices[0].x, screenVertices[0].y, screenVertices[1].x, screenVertices[1].y, screenVertices[2].x, screenVertices[2].y, RED, kFillModeSolid);

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
