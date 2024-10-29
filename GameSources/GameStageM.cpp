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
	void GameStageM::CreateViewLight() {
		const Vec3 eye(0.0f, 2.0f, -10.0f);
		const Vec3 at(0.0f,2.0f,0.0f);
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

	void GameStageM::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UITex/";
		wstring texPath = path + L"Texture/";

		wstring strPath = uiPath + L"TimerNum.png";
		app->RegisterTexture(L"NUMBER_TEX", strPath);

		strPath = texPath + L"gole1.png";
		app->RegisterTexture(L"GOAL_TEX", strPath);

		strPath = texPath + L"explodParticle.png";
		app->RegisterTexture(L"EXPLODE_TEX", strPath);

		strPath = texPath + L"explodeParticle1.png";
		app->RegisterTexture(L"EXPLODE1_TEX", strPath);
		strPath = texPath + L"explodeParticle2.png";
		app->RegisterTexture(L"EXPLODE2_TEX", strPath);

	}

	void GameStageM::OnCreate() {
		try {
			//CreateViewLight();
			GameStage::OnCreate();
			//CreateResource();

			//AddGameObject<Bomb>(Vec3(0, 10, 0));
			//AddGameObject<Bomb>(Vec3(1, 1, 0));

			//for (int i = 0; i < 5; i++) {
			//	for (int j = 0; j < 5; j++) {
			//		//AddGameObject<FloorBlock>(Vec3(-2.5f + j, 0, -2.5f + i));
			//	}
			//}

			////数値表示
			////shared_ptr<BCNumber> num = AddGameObject<BCNumber>(L"NUMBER_TEX", Vec3(0, 0, 0), Vec2(200, 100), 4);
			////num->UpdateNumber(rand() % 1000);

			//AddGameObject<BCSprite>(L"EXPLODE_TEX", Vec3(0, 0, 0), Vec2(100, 100));
			////AddGameObject<BCParticleSprite>();
			//auto particle = AddGameObject<BCParticle>();
			//particle->Shot();
			////AddGameObject<BombEffect>(false,1.0f,0.0f)->InsertFire(Vec3(0, 0, 0));
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
