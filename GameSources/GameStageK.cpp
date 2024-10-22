/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStageK::CreateViewLight() {
		const Vec3 eye(0.0f, 1.0f, -8.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStageK::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring texPath = path + L"TestTex/Diamond.png";
		app->RegisterTexture(L"DIAMOND_TX", texPath);
		texPath = path + L"TestTex/SmoothStone.png";
		app->RegisterTexture(L"SMOOTH_STONE_TX", texPath);
	}

	void GameStageK::OnCreate() {
		try {
			CreateViewLight();
			CreateResource();

			Vec3 floorPos = Vec3(-5.0f, -1.5f, 0.0f);
			for (int i = 0; i < 10; i++)
			{
				AddGameObject<FloorBlockTex>(floorPos, L"DIAMOND_TX");
				floorPos.x += 1.0f;
			}
			AddGameObject<Player>(make_shared<PlayerStateIdle>());
		}
		catch (...) {
			throw;
		}
	}

	void GameStageK::OnUpdate() {

	}

}
//end basecross
