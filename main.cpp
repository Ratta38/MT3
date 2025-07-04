#include "Ball.h"
#include "Collision.h"
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

const char kWindowTitle[] = "LE2B_23_ミハラ_ユウタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// カメラ
	Vector3 cameraTranslate = {0.0f, 4.5f, -6.5f};
	Vector3 cameraRotate = {0.6f, 0.0f, 0.0f};

	// 球
	Sphere sphere{};
	sphere.center = {0.0f, 1.0f, 0.0f};
	sphere.radius = 0.1f;

	// 紐
	Pendulum pendulum{};
	pendulum.anchor = {0.0f, 1.0f, 0.0f};
	pendulum.length = 0.8f;
	pendulum.angle = 0.7f;
	pendulum.angularVelocity = 0.0f;
	pendulum.angularAcceleration = 0.0f;

	float deltaTime = 1.0f / 60.0f;

	// 球の動きを制御する変数
	bool isMove = false;

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

		if (isMove) {
			pendulum.angularAcceleration = -(9.8f / pendulum.length) * std::sinf(pendulum.angle);
			pendulum.angularVelocity += pendulum.angularAcceleration * deltaTime;
			pendulum.angle += pendulum.angularVelocity * deltaTime;

			// pは振り子の先端の位置。取り付けたいものを取り付ければいい
			sphere.center.x = pendulum.anchor.x + std::sinf(pendulum.angle) * pendulum.length;
			sphere.center.y = pendulum.anchor.y - std::cosf(pendulum.angle) * pendulum.length;
			sphere.center.z = pendulum.anchor.z;
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
		ImGui::Begin("Window");

		ImGui::DragFloat3("camera.translate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("camera.rotate", &cameraRotate.x, 0.01f);

		if (ImGui::Button("Start")) {
			isMove = true;
		}

		if (ImGui::Button("Stop")) {
			isMove = false;
		}

		ImGui::DragFloat3("pendulum.anchor", &pendulum.anchor.x, 0.01f);
		ImGui::DragFloat3("sphere.center", &sphere.center.x, 0.01f);

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

		// 紐
		Vector3 pendulumAnchorScreen = Math::Transform(Math::Transform(pendulum.anchor, worldViewProjectionMatrix), viewportMatrix);
		Vector3 sphereCenterScreen = Math::Transform(Math::Transform(sphere.center, worldViewProjectionMatrix), viewportMatrix);
		Shape::DrawLine(pendulumAnchorScreen.x, pendulumAnchorScreen.y, sphereCenterScreen.x, sphereCenterScreen.y, WHITE);

		// ボール
		Shape::DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, WHITE);

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
