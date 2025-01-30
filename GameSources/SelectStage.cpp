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
			AddGameObject<ButtonManager>();
			CreateViewLight();
			CreateResource();
			AddGameObject<Sprite>(L"BACKGROUND_TEX", Vec3(0, 0, 0), Vec2(1280, 800), true);
			
			auto sprite = AddGameObject<Sprite>(L"DIFFICULTY_TEXT_UI", Vec3(0, 300, 0), Vec2(400, 100), true);


			ButtonManager::Create(GetThis<Stage>(), L"tutorial", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(-400, 120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(0);
				});
			ButtonManager::Create(GetThis<Stage>(), L"tutorial", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(0, 120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(1);
				});
			ButtonManager::Create(GetThis<Stage>(), L"tutorial", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(400, 120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(2);
				});
			ButtonManager::Create(GetThis<Stage>(), L"tutorial", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(-400, -120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(3);
				});
			ButtonManager::Create(GetThis<Stage>(), L"tutorial", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(0, -120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(4);
				});
			ButtonManager::Create(GetThis<Stage>(), L"tutorial", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(400, -120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(5);
				});

			vector<shared_ptr<Sprite>> difficultySprites = {};
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR_UI", Vec3(-400, 120, 0), Vec2(60, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR2_UI", Vec3(0, 120, 0), Vec2(120, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR3_UI", Vec3(400, 120, 0), Vec2(180, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR4_UI", Vec3(-400, -120, 0), Vec2(120, 120), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR5_UI", Vec3(0, -120, 0), Vec2(180, 120), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR6_UI", Vec3(400, -120, 0), Vec2(180, 120), true));

			for (int i = 0; i < difficultySprites.size(); i++) {
				ButtonManager::instance->SetFrontSprite(L"tutorial", i, difficultySprites[i]);
			}

			ButtonManager::instance->SetInput(L"tutorial", InputData(XINPUT_GAMEPAD_DPAD_LEFT, -1));
			ButtonManager::instance->SetInput(L"tutorial", InputData(XINPUT_GAMEPAD_DPAD_RIGHT, 1));
			ButtonManager::instance->SetInput(L"tutorial", InputData(XINPUT_GAMEPAD_DPAD_DOWN, 3));
			ButtonManager::instance->SetInput(L"tutorial", InputData(XINPUT_GAMEPAD_DPAD_UP, -3));

			/*auto button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(-400, 120, 0), Vec2(240, 240),1);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");
			button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(0, 120, 0), Vec2(240, 240),2);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");
			button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(400, 120, 0), Vec2(240, 240),3);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");
			button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(-400, -120, 0), Vec2(240, 240), 4);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");
			button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(0, -120, 0), Vec2(240, 240), 5);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");
			button = AddGameObject<SelectButton>(L"STAGESELECT_FALSE_UI", Vec3(400, -120, 0), Vec2(240, 240), 6);
			button->AddSelectEffect(SelectEffect::ChangeSprite);
			button->SetSelectTex(L"STAGESELECT_TRUE_UI");*/

			AddGameObject<Sprite>(L"DPAD_UI", Vec3(0, -300, 0), Vec2(281.6f, 140.8f), true);

			SoundManager::Instance().PlayBGM(L"SELECT_BGM", 1.0f);
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
		/*if (ctrl.bConnected && m_Fade == nullptr) {
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				m_Select--;
			}
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				m_Select++;
			}
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				if (m_Select + 3 <= MAX_STAGE - 1) {
					m_Select += 3;
				}
			}
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
				if (m_Select - 3 >= 0) {
					m_Select -= 3;
				}
			}

			float stickX = ctrl.fThumbLX;
			float stickDeadZone = 0.2f;
			if (abs(stickX) >= stickDeadZone) {

				if (m_IsCanNextSelect >= 1.0f) {
					if (stickX < 0) {
						m_Select--;
					}
					else {
						m_Select++;
					}
					m_IsCanNextSelect = 0.0f;
				}
			}
			else{
				m_IsCanNextSelect = 1.0f;
			}
			m_Select = max(0, m_Select);
			m_Select = min(MAX_STAGE - 1, m_Select);

			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_A) {
				SoundManager::Instance().PlaySE(L"BUTTON_SD");
				m_Fade = AddGameObject<Fade>(1.0f);
			}
		}
		Button::SelectButton(m_Select);*/

		if (m_Fade != nullptr) {
			if (m_Fade->IsFinished()) {
				auto stage = make_shared<int>(m_Select);
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), gameMode, stage);
			}
		}
	}
	void SelectStage::OnDestroy() {
		SoundManager::Instance().StopAll();
	}
	void SelectStage::CreateFade(int select) {
		m_Fade = AddGameObject<Fade>(1.0f);
		m_Select = select;
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
		app->RegisterTexture(L"STAR4_UI", uiPath + L"star_difficulty4.png");
		app->RegisterTexture(L"STAR5_UI", uiPath + L"star_difficulty5.png");
		app->RegisterTexture(L"STAR6_UI", uiPath + L"star_difficulty6.png");
	}
}
//end basecross
