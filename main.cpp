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

	Segment segment{
	    {-2.0f, -1.0f, 0.0f},
        {3.0f,  2.0f,  2.0f}
    };
	Vector3 point{-1.5f, 0.6f, 0.6f};

	Vector3 project = Math::Project(Math::Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = Math::ClosestPoint(point, segment);

	Sphere pointSphere{point, 0.01f};// 1cmの球を描画
	Sphere closestPointSphere{closestPoint, 0.01f};

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
		Matrix4x4 viewProjectionMatrix = Math::Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 worldViewProjectionMatrix = Math::Multiply(worldMatrix, viewProjectionMatrix);
		// ViewportMatrixを作る
		Matrix4x4 viewportMatrix = Math::MakeViewPortMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);

#ifdef _DEBUG
		// 
		ImGui::InputFloat3("Point", &point.x);
		// セグメント始点
		ImGui::InputFloat3("segment.origin", &segment.origin.x);
		// セグメント終点への差分ベクトル
		ImGui::InputFloat3("segment.diff", &segment.diff.x);
		// 射影ベクトル
		ImGui::InputFloat3("Project", &project.x);

		ImGui::SliderFloat3("camera.translate", &cameraTranslate.x, -10.0f, 10.0f);
#endif // _DEBUG

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド
		Shape::DrawGrid(viewProjectionMatrix, viewportMatrix);

		// 線分
		Vector3 start = Math::Transform(Math::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 end = Math::Transform(Math::Transform(Math::Add(segment.origin,segment.diff),viewProjectionMatrix),viewportMatrix);
		Shape::DrawLine(start.x,start.y,end.x,end.y,WHITE);

		// 球
		Shape::DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, RED);
		Shape::DrawSphere(closestPointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

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
