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
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f,0.0f,0.0f);
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
		wstring texPath = path + L"Texture/";
	}

	void GameStageM::OnCreate() {
		try {
			CreateViewLight();
			AddGameObject<Bomb>();

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					AddGameObject<FloorBlock>(Vec3(-2.5f + j, 0, -2.5f + i));
				}
			}
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
