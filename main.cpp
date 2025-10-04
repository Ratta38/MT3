#include "Ball.h"
#include "Collision.h"
#include "ConicalPendulum.h"
#include "Math.h"
#include "MathOperator.h"
#include "Pendulum.h"
#include "Plane.h"
#include "Shape.h"
#include "Sphere.h"
#include "Spring.h"
#include "Vector3.h"
#include "WindowSize.h"
#include "Capsule.h"
#include <Novice.h>
#include <cmath>
#include <imgui.h>
#undef min
#undef max
#include <algorithm>

const char kWindowTitle[] = "LE2A_16_ミハラ_ユウタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 from0 = Math::Normalize({1.0f, 0.7f, 0.5f});

	Vector3 to0 = -from0;

	Vector3 from1 = Math::Normalize({-0.6f, 0.9f, 0.2f});

	Vector3 to1 = Math::Normalize({0.4f, 0.7f, -0.5f});

	Matrix4x4 rotateMatrix0 = Math::DirectionToDirection(Math::Normalize({1.0f, 0.0f, 0.0f}), Math::Normalize({-1.0f, 0.0f, 0.0f}));

	Matrix4x4 rotateMatrix1 = Math::DirectionToDirection(from0, to0);

	Matrix4x4 rotateMatrix2 = Math::DirectionToDirection(from1, to1);

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

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 行列の表示
		Math::MatrixScreenPrintf(0, 0, rotateMatrix0, "rotateMatrix0");
		Math::MatrixScreenPrintf(0, 100, rotateMatrix1, "rotateMatrix1");
		Math::MatrixScreenPrintf(0, 200, rotateMatrix2, "rotateMatrix2");

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
