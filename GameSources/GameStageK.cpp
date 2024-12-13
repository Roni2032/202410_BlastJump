/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStageK::CreateViewLight() {
		const Vec3 eye(0.0f, 3.0f, -100.0f);
		const Vec3 at(0.0f, 3.0f, 0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStageK::CreateResource() {
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

	void GameStageK::OnCreate() {
		try {
			GameStage::OnCreate();

		}
		catch (...) {
			throw;
		}
	}

	void GameStageK::OnUpdate() {
		GameStage::OnUpdate();

			timer = 0;
	}

}
//end basecross
