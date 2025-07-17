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

	// Plane
	Plane plane{};
	plane.normal = Math::Normalize({-0.2f, 0.9f, -0.3f});
	plane.distance = 0.0f;

	// Ball
	Ball ball{};
	ball.position = {0.8f, 1.2f, 0.3f};
	ball.velocity = 0.0f;
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;
	ball.acceleration = {0.0f, -9.8f, 0.0f};

	// 描画用球
	Sphere sphere{};
	sphere.center = ball.position;
	sphere.radius = ball.radius;

	// Capsule
	Capsule capsule{};

	float deltaTime = 1.0f / 60.0f;

	const float e = 0.6f; // 反発係数 

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

			// ボールの前の位置を保存
			Vector3 prePosition = ball.position;

			// 物理更新
			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;

			// カプセル
			capsule.segment.origin = prePosition;
			capsule.segment.diff = ball.position;
			capsule.radius = ball.radius;

			if (Collision::Intersect(capsule, plane)) {
				Vector3 reflected = Math::Reflect(ball.velocity, plane.normal);
				Vector3 projectToNormal = Math::Project(reflected, plane.normal);
				Vector3 movingDirection = reflected - projectToNormal;
				ball.velocity = projectToNormal * e + movingDirection;

				// ボールがめり込んだままにならないように平面上に補正
				float penetration = ball.radius - Math::Dot(plane.normal, ball.position) + plane.distance;
				ball.position += plane.normal * penetration;
			}

			// 描画用の球に反映
			sphere.center = ball.position;
		}

		// リトライ用
		if (keys[DIK_R]) {
			ball.position = {0.8f, 1.2f, 0.3f};
			ball.velocity = 0.0f;
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

		if (ImGui::Button("Start")) {
			isMove = true;
		}

		if (ImGui::Button("Stop")) {
			isMove = false;
		}

		ImGui::DragFloat3("camera.translate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("camera.rotate", &cameraRotate.x, 0.01f);

		ImGui::DragFloat3("ball.position", &ball.position.x, 0.01f);
		ImGui::DragFloat3("ball.acceleration", &ball.acceleration.x, 0.01f);
		ImGui::DragFloat3("ball.velocity", &ball.velocity.x, 0.01f);
		ImGui::DragFloat3("plane.normal", &plane.normal.x, 0.01f);

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

		// 平面
		Shape::DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, WHITE);

		// ボール
		Shape::DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, ball.color);

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
