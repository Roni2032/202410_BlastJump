/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void SelectStage::CreateViewLight() {
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

	void SelectStage::OnCreate() {
		try {
			CreateViewLight();
			CreateResource();
			AddGameObject<BCSprite>(L"BACKGROUND_TEX", Vec3(0, 0, 0), Vec2(1280, 800), true);
			auto sprite = AddGameObject<BCSprite>(L"DIFFICULTY_TEXT_UI", Vec3(0, 200, 0), Vec2(400, 100),true);
			auto button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(-400, 0, 0), Vec2(240, 240),1);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");
			button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(0, 0, 0), Vec2(240, 240),2);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");
			button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(400, 0, 0), Vec2(240, 240),3);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");

			sprite = AddGameObject<BCSprite>(L"DPAD_UI", Vec3(0, -300, 0), Vec2(281.6f, 140.8f), true);

			SoundManager::Instance().PlayBGM(L"SELECT_BGM",0.1f);
		}
		catch (...) {
			throw;
		}
	}

	void SelectStage::OnUpdate() {
		auto ctrl = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float elapse = App::GetApp()->GetElapsedTime();
		if (m_IsCanNextSelect < 1.0f) {
			m_IsCanNextSelect += elapse / 0.5f;
		}
		if (ctrl.bConnected && m_Fade == nullptr) {
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				m_Select--;
			}
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				m_Select++;
			}
			float stickX = ctrl.fThumbLX;
			float stickDeadZone = 0.2f;
			if (abs(stickX) >= stickDeadZone && m_IsCanNextSelect >= 1.0f) {
				if (stickX < 0) {
					m_Select--;
				}
				else {
					m_Select++;
				}
				m_IsCanNextSelect = 0.0f;
			}
			if (m_Select < 0) {
				m_Select = 0;
			}
			if (m_Select >= MAX_STAGE) {
				m_Select = MAX_STAGE - 1;
			}

			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_A) {
				SoundManager::Instance().PlaySE(L"BUTTON_SD");
				m_Fade = AddGameObject<Fade>(1.0f);
			}
		}
		Button::SelectButton(m_Select);

		if (m_Fade != nullptr) {
			if (m_Fade->IsFinished()) {
				auto stage = make_shared<int>(m_Select);
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage",stage);
			}
		}
	}
	void SelectStage::OnDestroy() {
		SoundManager::Instance().StopAll();
	}
	void SelectStage::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UITex/";
		wstring texPath = path + L"Texture/";
		wstring modelPath = path + L"Models/";

		app->RegisterTexture(L"TITLE_UI", uiPath + L"Title.png");
		app->RegisterTexture(L"PUSH_A_UI", uiPath + L"PushA.png");
		app->RegisterTexture(L"DIFFICULTY_TEXT_UI", uiPath + L"Diffuculty.png");

		app->RegisterTexture(L"STAGESELECT_FALSE_UI", uiPath + L"Noselect.png");
		app->RegisterTexture(L"STAGESELECT_TRUE_UI", uiPath + L"Yesselect.png");
		app->RegisterTexture(L"DPAD_UI", uiPath + L"SelectStage_Operation.png");
		app->RegisterTexture(L"BACKGROUND_TEX", texPath + L"BackGround.png");
		app->RegisterTexture(L"STAR_UI", uiPath + L"star.png");
		app->RegisterTexture(L"STAR2_UI", uiPath + L"star_difficulty2.png");
		app->RegisterTexture(L"STAR3_UI", uiPath + L"star_difficulty3.png");
	}




	void SelectButton::OnCreate() {
		Button::OnCreate();
		m_BackGroundSprite = GetSprite();
		Vec3 centerPos = m_BackGroundSprite->GetPos();
		Vec2 backGroundSize = m_BackGroundSprite->GetSize();
		Vec3 startPos = Vec3();

		if (m_Difficulty == 1) {
			AddLockSprite(GetStage()->AddGameObject<BCSprite>(L"STAR_UI", centerPos, Vec2(60, 60), true));
		}
		else if(m_Difficulty == 2){
			AddLockSprite(GetStage()->AddGameObject<BCSprite>(L"STAR2_UI", centerPos, Vec2(120, 60), true));
		}
		else {
			AddLockSprite(GetStage()->AddGameObject<BCSprite>(L"STAR3_UI", centerPos, Vec2(180, 60), true));
		}
		
	}
	void SelectButton::OnUpdate() {
		Button::OnUpdate();
	}
}
//end basecross
