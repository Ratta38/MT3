#include "Ball.h"
#include "Capsule.h"
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

	Quaternion q1 = {2.0f, 3.0f, 4.0f, 1.0f};
	Quaternion q2 = {1.0f, 3.0f, 5.0f, 2.0f};
	Quaternion identity = Math::IdentityQuaternion();
	Quaternion conj = Math::Conjugate(q1);
	Quaternion inv = Math::Inverse(q1);
	Quaternion normal = Math::Normalize(q1);
	Quaternion mul1 = Math::Multiply(q1, q2);
	Quaternion mul2 = Math::Multiply(q2, q1);
	float norm = Math::Norm(q1);

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

		// 結果の表示
		Math::QuaternionPrint(0, 0, identity, ": Identity");
		Math::QuaternionPrint(0, 20, conj, ": Conjugate");
		Math::QuaternionPrint(0, 40, inv, ": Inverse");
		Math::QuaternionPrint(0, 60, normal, ": Normalize");
		Math::QuaternionPrint(0, 80, mul1, ": Multiply(q1, q2)");
		Math::QuaternionPrint(0, 100, mul2, ": Multiply(q2, q1)");
		Novice::ScreenPrintf(0, 120, "%6.02f", norm);
		Novice::ScreenPrintf(240, 120, ": Norm");

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
