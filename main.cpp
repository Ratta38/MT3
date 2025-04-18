#include "Math.h"
#include "Vector3.h"
#include <Novice.h>

const char kWindowTitle[] = "LE2B_23_ミハラ_ユウタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 rotate{0.4f, 1.43f, -0.8f};
	Matrix4x4 rotateXMatrix = Math::MakePitchRotateMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = Math::MakeYawRotateMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = Math::MakeRollRotateMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Math::Multiply(rotateXMatrix, Math::Multiply(rotateYMatrix, rotateZMatrix));

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

		Math::MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		Math::MatrixScreenPrintf(0, Math::kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		Math::MatrixScreenPrintf(0, Math::kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		Math::MatrixScreenPrintf(0, Math::kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

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
