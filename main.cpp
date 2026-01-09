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

	Quaternion rotation0 = Math::MakeRotateAxisAngleQuaternion({0.71f, 0.71f, 0.0f}, 0.3f);
	Quaternion rotation1 = Math::MakeRotateAxisAngleQuaternion({0.71f, 0.0f, 0.71f}, 3.141592f);

	Quaternion interpolate0 = Math::Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Math::Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Math::Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Math::Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Math::Slerp(rotation0, rotation1, 1.0f);

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
		Math::QuaternionPrint(0, 0, interpolate0, " : interpolate0, Slerp(q0, q1, 0.0f)");
		Math::QuaternionPrint(0, 20, interpolate1, " : interpolate1, Slerp(q0, q1, 0.3f)");
		Math::QuaternionPrint(0, 40, interpolate2, " : interpolate2, Slerp(q0, q1, 0.5f)");
		Math::QuaternionPrint(0, 60, interpolate3, " : interpolate3, Slerp(q0, q1, 0.7f)");
		Math::QuaternionPrint(0, 80, interpolate4, " : interpolate4, Slerp(q0, q1, 1.0f)");

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
