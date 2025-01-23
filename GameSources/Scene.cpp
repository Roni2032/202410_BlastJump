
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
	void Scene::OnCreate(){
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
			const auto boneModelIdle = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerIdole.bmf");
			const auto boneModelMove = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerMove.bmf");
			const auto boneModelJump = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerJump.bmf");
			const auto boneModelThrowDefault = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerDefaultThrow.bmf");
			const auto boneModelThrowUp = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerThrowUp.bmf");
			const auto boneModelThrowDown = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerThrowDown.bmf");
			const auto boneModelWin = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerWin.bmf");
			const auto boneModelLose = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerLose.bmf");

			const auto boneModelFull = MeshResource::CreateBoneModelMesh(modelPath, L"PlayerFullAnimation.bmf");

			app->RegisterResource(L"PLAYER_MD_IDLE", boneModelIdle);
			app->RegisterResource(L"PLAYER_MD_MOVE", boneModelMove);
			app->RegisterResource(L"PLAYER_MD_JUMP", boneModelJump);
			app->RegisterResource(L"PLAYER_MD_THROW_DEFAULT", boneModelThrowDefault);
			app->RegisterResource(L"PLAYER_MD_THROW_UP", boneModelThrowUp);
			app->RegisterResource(L"PLAYER_MD_THROW_DOWN", boneModelThrowDown);
			app->RegisterResource(L"PLAYER_MD_WIN", boneModelWin);
			app->RegisterResource(L"PLAYER_MD_LOSE", boneModelLose);


			boneModel = MeshResource::CreateBoneModelMesh(modelPath, L"CheckPoint.bmf");
			app->RegisterResource(L"CHECKPOINT_MD", boneModel);
			app->RegisterResource(L"PLAYER_MD_FULL", boneModelFull);

			app->RegisterTexture(L"PLAYER_MD_TEX", modelPath + L"chara.png");

			app->RegisterTexture(L"FADE_TEX", texPath + L"fade.png");

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");

			SoundManager::Instance().RegisterSounds();
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		Button::Clear();
		if (event->m_MsgStr == L"ToGameStage") {
			auto stage = static_pointer_cast<int>(event->m_Info).get();
			switch (*stage) {
			case 0:
				ResetActiveStage<GameStage>(L"Stage01.csv",*stage,20,0.0f);
				break;
			case 1:
				ResetActiveStage<GameStage>(L"Stage02.csv", *stage,25,0.25f);
				break;
			case 2:
				ResetActiveStage<GameStage>(L"Stage04.csv", *stage,30);
				break;
			default:
				ResetActiveStage<TitleStage>();
				break;
			}
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