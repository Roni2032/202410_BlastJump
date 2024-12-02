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

			auto button = AddGameObject<Button>(L"TITLE_UI", Vec3(0, 25, 0), Vec2(500, 500));
			button->AddSelectEffect(SelectEffect::Expand);
			button = AddGameObject<Button>(L"PUSH_A_UI", Vec3(0, -320, 0), Vec2(300, 120));
			button->AddSelectEffect(SelectEffect::Expand);
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
		if (ctrl.bConnected) {
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				m_Select--;
			}
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				m_Select++;
			}
			float stickX = ctrl.fThumbLX;
			if (abs(stickX) >= 0.2f && m_IsCanNextSelect >= 1.0f) {
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
	void SelectStage::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UITex/";
		wstring texPath = path + L"Texture/";
		wstring modelPath = path + L"Models/";

		app->RegisterTexture(L"TITLE_UI", uiPath + L"Title.png");
		app->RegisterTexture(L"PUSH_A_UI", uiPath + L"PushA.png");
	}
}
//end basecross
