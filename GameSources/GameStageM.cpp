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
		const Vec3 eye(0.0f, 3.0f, -100.0f);
		const Vec3 at(0.0f,3.0f,0.0f);
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
			GameStage::OnCreate();

			//SoundManager::Instance().StopBGM();
			AddGameObject<Bomb>(Vec3(0, 5, 0));
			//AddGameObject<BackGroundManager>(9.0f);
		}
		catch (...) {
			throw;
		}
	}

	void GameStageM::OnUpdate() {
		GameStage::OnUpdate();

		/*float e = App::GetApp()->GetElapsedTime();
		timer += e;
		if (timer > 10.0f) {
			timer = 0;
			static_pointer_cast<MyCamera>(GetView()->GetTargetCamera())->SetStageAt(10.0f);
			m_Player->GetComponent<Transform>()->SetPosition(0, 10.0f, 0);
		}*/
	}
}
//end basecross
