
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			auto& app = App::GetApp();
			wstring path = app->GetDataDirWString();
			wstring modelPath = path + L"Models/";

			auto multiModel = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Goalkari.bmf");
			app->RegisterResource(L"GOAL_MD", multiModel);
			auto model = MeshResource::CreateStaticModelMesh(modelPath, L"Bomb.bmf");
			app->RegisterResource(L"BOMB_MD", model);


			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");

			auto soundManager = SoundManager::Instance();
			soundManager.RegisterSounds();
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			//ResetActiveStage<GameStage>(L"Stage01.csv");
			ResetActiveStage<GameStageM>();
		}
	}

}
//end basecross
