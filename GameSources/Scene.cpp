
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
			wstring texPath = path + L"Texture/";

			auto multiModel = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Goalkari.bmf");
			app->RegisterResource(L"GOAL_MD", multiModel);
			app->RegisterTexture(L"GOAL_MD_TEX", modelPath + L"goaltex.png");
			auto model = MeshResource::CreateStaticModelMesh(modelPath, L"Bomb.bmf");
			app->RegisterResource(L"BOMB_MD", model);
			app->RegisterTexture(L"BOMB_MD_TEX", modelPath + L"bomb.png");
			multiModel = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Player.bmf");
			app->RegisterResource(L"PLAYER_MD", multiModel);
			app->RegisterTexture(L"PLAYER_MD_TEX", modelPath + L"chara.png");

			app->RegisterTexture(L"FADE_TEX", texPath + L"fade.png");

			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToSelectStage");

			SoundManager::Instance().RegisterSounds();
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		Button::Buttons.clear();
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			//ResetActiveStage<GameStage>(L"Stage01.csv");
			ResetActiveStage<GameStageK>();
//=======
//			//ResetActiveStage<GameStageM>();
//			auto stage = static_pointer_cast<int>(event->m_Info).get();
//			switch (*stage) {
//			case 0:
//				ResetActiveStage<GameStage>(L"Stage01.csv",*stage);
//				break;
//			case 1:
//				ResetActiveStage<GameStage>(L"Stage02.csv", *stage);
//				break;
//			case 2:
//				ResetActiveStage<GameStage>(L"Stage03.csv", *stage);
//				break;
//			default:
//				ResetActiveStage<TitleStage>();
//				break;
//			}
//>>>>>>> master
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToSelectStage") {
			ResetActiveStage<SelectStage>();
		}
	}

}
//end basecross