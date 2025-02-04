/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void TitleStage::CreateViewLight() {
		const Vec3 eye(-0.5f, 4.0f, -34.0f);
		const Vec3 at(-0.5f, 4.0f, 0.0f);
		auto PtrView = CreateView<SingleView>();
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		auto PtrMultiLight = CreateLight<MultiLight>();
		PtrMultiLight->SetDefaultLighting();
	}

	void TitleStage::OnCreate() {
		try {
			CreateViewLight();
			CreateResource();
			auto sprite = AddGameObject<Sprite>(L"BACKGROUND", Vec3(0, 0, 0), Vec2(1280, 800), true);
			sprite = AddGameObject<Sprite>(L"TITLE_UI", Vec3(0, 100, 0), Vec2(700, 700),true);
			sprite = AddGameObject<Sprite>(L"PUSH_A_UI", Vec3(0,-300,0), Vec2(300, 120),true);
			sprite->AddComponent<SpriteFlash>(1.0f);
			SoundManager::Instance().PlayBGM(L"TITLE_BGM",0.5f);
		}
		catch (...) {
			throw;
		}
	}
	
	void TitleStage::OnUpdate() {
		auto ctrl = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (ctrl.bConnected) {
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_A && !m_Fade) {
				SoundManager::Instance().PlaySE(L"BUTTON_SD");
				m_Fade = AddGameObject<Fade>(1.0f);
				m_SelectMode = L"ToTutorialStage";
			}
		}
		if (m_Fade != nullptr) {
			if (m_Fade->IsFinished()) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage",make_shared<wstring>(m_SelectMode));
			}
		}
	}
	void TitleStage::OnDestroy() {
		SoundManager::Instance().StopBGM();
	}
	void TitleStage::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UITex/";
		wstring texPath = path + L"Texture/";
		wstring modelPath = path + L"Models/";
		
		app->RegisterTexture(L"TITLE_UI", uiPath + L"Title_Main.png");
		app->RegisterTexture(L"PUSH_A_UI", uiPath + L"PressA.png");
		app->RegisterTexture(L"BACKGROUND", uiPath + L"Title_BackGound.png");
	}
}
//end basecross
