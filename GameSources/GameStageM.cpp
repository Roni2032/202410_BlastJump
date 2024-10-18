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
		wstring texPath = path + L"UITex/";

		wstring strPath = texPath + L"TimerNum.png";
		app->RegisterTexture(L"NUMBER_TEX", strPath);
	}

	void GameStageM::OnCreate() {
		try {
			CreateViewLight();
			CreateResource();

			AddGameObject<Bomb>(Vec3(0, 5, 0),1.0f,1.0f);
			AddGameObject<Bomb>(Vec3(1, 1, 0),3.0f,3.0f,3.0f,Vec3(0,9,0));

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					//AddGameObject<FloorBlock>(Vec3(-2.5f + j, 0, -2.5f + i));
				}
			}

			//数値表示
			shared_ptr<BCNumber> num = AddGameObject<BCNumber>(L"NUMBER_TEX", Vec3(0, 0, 0), Vec2(200, 100), 4);
			num->UpdateNumber(1432);

			
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
