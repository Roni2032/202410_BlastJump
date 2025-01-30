
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void GameScene::OnCreate(){
		try {
			auto& app = App::GetApp();
			wstring path = app->GetDataDirWString();
			wstring modelPath = path + L"Models/";
			wstring texPath = path + L"Texture/";
			

			auto boneModel = MeshResource::CreateBoneModelMesh(modelPath, L"Door.bmf");
			app->RegisterResource(L"GOAL_MD", boneModel);
			app->RegisterTexture(L"GOAL_MD_TEX", modelPath + L"door.png");
			auto model = MeshResource::CreateStaticModelMesh(modelPath, L"Bomb.bmf");
			app->RegisterResource(L"BOMB_MD", model);
			app->RegisterTexture(L"BOMB_MD_TEX", modelPath + L"bomb.png");

			boneModel = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerFullAnimation.bmf");
			const auto boneModelFull = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerFullAnimation.bmf");

			boneModel = MeshResource::CreateBoneModelMesh(modelPath, L"CheckPoint.bmf");

			app->RegisterResource(L"CHECKPOINT_MD", boneModel);
			app->RegisterTexture(L"CHECKPOINT_TEX", modelPath + L"save.png");

			app->RegisterResource(L"PLAYER_MD_FULL", boneModelFull);

			app->RegisterTexture(L"PLAYER_MD_TEX", modelPath + L"chara.png");

			app->RegisterTexture(L"FADE_TEX", texPath + L"fade.png");

			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");

			SoundManager::Instance().RegisterSounds();
		}
		catch (...) {
			throw;
		}
	}

	GameScene::~GameScene() {
	}

	void GameScene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			auto stage = static_pointer_cast<int>(event->m_Info).get();
			if (*stage < 0 || *stage >= m_StageFileNames.size()) {
				ResetActiveStage<TitleStage>();
			}
			ResetActiveStage<GameStage>(m_StageFileNames[*stage], *stage, 20, 0.0f);

			/*switch (*stage) {
			case 0:
				ResetActiveStage<GameStage>(L"Tutorial01.csv",*stage,20,0.0f);
				break;
			case 1:
				ResetActiveStage<GameStage>(L"Tutorial02.csv", *stage,25,0.25f);
				break;
			case 2:
				ResetActiveStage<GameStage>(L"Tutorial03.csv", *stage,30);
				break;
			case 3:
				ResetActiveStage<GameStage>(L"Tutorial04.csv", *stage, 30);
				break;
			case 4:
				ResetActiveStage<GameStage>(L"Tutorial05.csv", *stage, 30);
				break;
			case 5:
				ResetActiveStage<GameStage>(L"Tutorial06.csv", *stage, 99);
				break;
			case 6:
				ResetActiveStage<GameStage>(L"Tutorial07.csv", *stage, 30);
				break;
			default:
				ResetActiveStage<TitleStage>();
				break;
			}*/
			
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToSelectStage") {
			auto mode = static_pointer_cast<wstring>(event->m_Info).get();
			ResetActiveStage<SelectStage>(L"ToGameStage");
		}
	}

}
//end basecross