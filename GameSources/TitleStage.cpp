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

			AddGameObject<BCSprite>(L"TITLE_UI", Vec3(0, 150, 0), Vec2(500, 500),true);
			AddGameObject<BCSprite>(L"PUSH_A_UI", Vec3(0,-300,0), Vec2(300, 120),true);
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
		auto ctrl = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (ctrl.bConnected) {
			if (ctrl.wPressedButtons & XINPUT_GAMEPAD_A) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
			}
		}
	}
	void TitleStage::CreateResource() {
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
