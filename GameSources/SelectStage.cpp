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
			
			m_Tab = AddGameObject<Sprite>(L"TUTORIAL_TAB_UI", Vec3(0, 300, 0), Vec2(400, 100), true);
			Vec3 firstPos = Vec3(-400, 120, 0);

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

			ButtonManager::Create(GetThis<Stage>(), L"stage", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(880, 120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(6);
				});
			ButtonManager::Create(GetThis<Stage>(), L"stage", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(1280, 120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(7);
				});
			ButtonManager::Create(GetThis<Stage>(), L"stage", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(1680, 120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(8);
				});
			ButtonManager::Create(GetThis<Stage>(), L"stage", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(880, -120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(9);
				});
			ButtonManager::Create(GetThis<Stage>(), L"stage", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(1280, -120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(10);
				});
			ButtonManager::Create(GetThis<Stage>(), L"stage", L"STAGESELECT_FALSE_UI", L"STAGESELECT_TRUE_UI", Vec3(1680, -120, 0), Vec2(240, 240),
				[](shared_ptr<Stage>& stage) {
					auto currentStage = static_pointer_cast<SelectStage>(stage);
					currentStage->CreateFade(11);
				});

			vector<shared_ptr<Sprite>> difficultySprites = {};
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR_UI", Vec3(-400, 120, 0), Vec2(60, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR2_UI", Vec3(0, 120, 0), Vec2(120, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR3_UI", Vec3(400, 120, 0), Vec2(180, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR4_UI", Vec3(-400, -120, 0), Vec2(120, 120), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR5_UI", Vec3(0, -120, 0), Vec2(180, 120), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR6_UI", Vec3(400, -120, 0), Vec2(180, 120), true));
			for (int i = 0; i < difficultySprites.size(); i++) {
				ButtonManager::instance->AddFrontSprite(L"tutorial", i, difficultySprites[i]);
			}
			difficultySprites.clear();
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR_UI", Vec3(880, 120, 0), Vec2(60, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR2_UI", Vec3(1280, 120, 0), Vec2(120, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR3_UI", Vec3(1680, 120, 0), Vec2(180, 60), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR4_UI", Vec3(880, -120, 0), Vec2(120, 120), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR5_UI", Vec3(1280, -120, 0), Vec2(180, 120), true));
			difficultySprites.push_back(AddGameObject<Sprite>(L"STAR6_UI", Vec3(1680, -120, 0), Vec2(180, 120), true));
			
			for (int i = 0; i < difficultySprites.size(); i++) {

				ButtonManager::instance->AddFrontSprite(L"stage", i, difficultySprites[i]);
			}
			for (int i = 1; i < MAX_TUTORIAL; i++) {
				ButtonManager::instance->AddFrontSprite(L"tutorial",i,
					AddGameObject<Sprite>(L"ROCK_UI", firstPos + Vec3(400 * (i % 3), -240 * (i / 3), 0), Vec2(160, 160), true));
			}
			for (int i = 1; i < MAX_STAGE; i++) {
				ButtonManager::instance->AddFrontSprite(L"stage", i,
					AddGameObject<Sprite>(L"ROCK_UI", firstPos + Vec3(400 * (i % 3), -240 * (i / 3), 0) + Vec3(1280, 0, 0), Vec2(160, 160), true));
			}

			ButtonManager::instance->SetInput(L"tutorial", InputData(XINPUT_GAMEPAD_DPAD_LEFT, -1));
			ButtonManager::instance->SetInput(L"tutorial", InputData(XINPUT_GAMEPAD_DPAD_RIGHT, 1));
			ButtonManager::instance->SetInput(L"tutorial", InputData(XINPUT_GAMEPAD_DPAD_DOWN, 3));
			ButtonManager::instance->SetInput(L"tutorial", InputData(XINPUT_GAMEPAD_DPAD_UP, -3));

			ButtonManager::instance->SetInput(L"stage", InputData(XINPUT_GAMEPAD_DPAD_LEFT, -1));
			ButtonManager::instance->SetInput(L"stage", InputData(XINPUT_GAMEPAD_DPAD_RIGHT, 1));
			ButtonManager::instance->SetInput(L"stage", InputData(XINPUT_GAMEPAD_DPAD_DOWN, 3));
			ButtonManager::instance->SetInput(L"stage", InputData(XINPUT_GAMEPAD_DPAD_UP, -3));

			for (int i = 1; i < ButtonManager::instance->GetSize(L"tutorial"); i++) {
				ButtonManager::instance->AddFunction(L"tutorial", i, [](shared_ptr<SpriteButton>& button) {
					auto scene = App::GetApp()->GetScene<GameScene>();
					if (scene->IsClear(button->GetOrder() - 1)) {
						button->SetActive(true);
						auto sprite = button->GetFrontSprite(1);
						if (sprite != nullptr) {
							sprite->SetDrawActive(false);
						}
					}
					else {
						button->SetActive(false);
						auto sprite = button->GetFrontSprite(1);
						if (sprite != nullptr) {
							sprite->SetDrawActive(true);
						}
					}});
			}
			for (int i = 1; i < ButtonManager::instance->GetSize(L"stage"); i++) {
				ButtonManager::instance->AddFunction(L"stage", i, [](shared_ptr<SpriteButton>& button) {
					auto scene = App::GetApp()->GetScene<GameScene>();
					if (scene->IsClear(MAX_TUTORIAL + button->GetOrder() - 1)) {
						button->SetActive(true);
						auto sprite = button->GetFrontSprite(1);
						if (sprite != nullptr) {
							sprite->SetDrawActive(false);
						}
					}
					else {
						button->SetActive(false);
						auto sprite = button->GetFrontSprite(1);
						if (sprite != nullptr) {
							sprite->SetDrawActive(true);
						}
					}});
			}
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
			m_LArrow = AddGameObject<Sprite>(L"LB_PUSH", Vec3(-566, 0, 0), Vec2(128, 128), true);
			m_RArrow = AddGameObject<Sprite>(L"RB_PUSH", Vec3(566, 0, 0), Vec2(128, 128), true);


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
		if (ButtonManager::instance->GetMoveAmount(ButtonManager::instance->GetUseGroup()).length() != 0) {
			m_Tab->SetDrawActive(false);
		}
		else {
			m_Tab->SetDrawActive(true);
		}
		if (ButtonManager::instance->CompareUseGroup(L"stage")) {
			m_LArrow->SetDrawActive(true);
			m_RArrow->SetDrawActive(false);

			m_Tab->GetComponent<SpriteBaseDraw>()->SetTextureResource(L"STAGESELECT_TAB_UI");
		}
		else if (ButtonManager::instance->CompareUseGroup(L"tutorial")) {
			m_LArrow->SetDrawActive(false);
			m_RArrow->SetDrawActive(true);
			m_Tab->GetComponent<SpriteBaseDraw>()->SetTextureResource(L"TUTORIAL_TAB_UI");
		}
		if (ButtonManager::instance->GetMoveAmount(L"stage").length() != 0 || ButtonManager::instance->GetMoveAmount(L"tutorial").length() != 0) {
			m_LArrow->SetDrawActive(false);
			m_RArrow->SetDrawActive(false);
		}

		if (ctrl.bConnected) {
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
				if (ButtonManager::instance->CompareUseGroup(L"stage")) {
					
					ButtonManager::instance->SetMoveAmount(L"stage", Vec3(1280, 0, 0));
					ButtonManager::instance->SetMoveAmount(L"tutorial", Vec3(1280, 0, 0));
					if (ButtonManager::instance->GetMoveAmount(L"stage") == Vec3(1280, 0, 0)) {
						ButtonManager::instance->UseGroup(L"tutorial");
					}
				}
			}
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				if (ButtonManager::instance->CompareUseGroup(L"tutorial")) {
					ButtonManager::instance->SetMoveAmount(L"stage", Vec3(-1280, 0, 0));
					ButtonManager::instance->SetMoveAmount(L"tutorial", Vec3(-1280, 0, 0));
					if (ButtonManager::instance->GetMoveAmount(L"stage") == Vec3(-1280, 0, 0)) {
						ButtonManager::instance->UseGroup(L"stage");
					}
				}
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
		app->RegisterTexture(L"TUTORIAL_TAB_UI", uiPath + L"TutorialTab.png");
		app->RegisterTexture(L"STAGESELECT_TAB_UI", uiPath + L"StageSelectTab.png");

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

		app->RegisterTexture(L"ROCK_UI", uiPath + L"Rock.png");
		app->RegisterTexture(L"ROCK2_UI", uiPath + L"Rock2.png");

		app->RegisterTexture(L"RB_PUSH", uiPath + L"RB_moveStage.png");
		app->RegisterTexture(L"LB_PUSH", uiPath + L"LB_moveTutorial.png");
	}
}
//end basecross
