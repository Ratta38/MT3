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

	Vector3 axis = Math::Normalize({1.0f, 1.0f, 1.0f});

	float angle = 0.44f;

	Matrix4x4 rotateMatrix = Math::MakeRotateAxisAngle(axis, angle);

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

		

#ifdef _DEBUG
		

#endif // _DEBUG

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 行列の表示
		Math::MatrixScreenPrintf(0, 0, rotateMatrix, "rotateMatrix");

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
