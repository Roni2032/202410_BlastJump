/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void BackGround::OnCreate() {
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SQUARE");
		
		draw->SetDiffuse(Col4(0, 0, 1, 1));
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_Pos);
		trans->SetScale(Vec3(15.0f,m_Scale.y,1));
	}
	void BackGround::OnUpdate() {

	}

	void BackGround::SetActive(bool flag) {
	}

	void BackGroundManager::OnCreate(){
		m_Camera = OnGetDrawCamera();
		auto camera = m_Camera.lock();
		if (camera != nullptr) {
			for (int i = -1; i < 3; i++) {
				float cameraHight = camera->GetHeight();
				Vec3 at = camera->GetAt();
				m_BackGrounds.push_back(GetStage()->AddGameObject<BackGround>(at + Vec3(0, 0, 1) + Vec3(0,m_LoopDistance,0) * i, Vec3(cameraHight)));
			}
		}
	}
	void BackGroundManager::OnUpdate() {
		auto camera = m_Camera.lock();
		if (camera == nullptr) return;

		for (auto& backGround : m_BackGrounds) {
			auto trans = backGround->GetComponent<Transform>();
			Vec3 pos = trans->GetPosition();
			Vec3 at = camera->GetAt();

			if (at.y - m_LoopDistance >= pos.y) {
				trans->SetPosition(pos.x, pos.y + m_LoopDistance * 4.0f, pos.z);
			}
		}
	}
}
//end basecross
