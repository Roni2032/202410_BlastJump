/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void MyCamera::OnCreate() {
		//SetPers(false);
		SetWidth(m_CameraWidth);
		SetHeight(m_CameraHight);

		SetFovY(XMConvertToRadians(15.0f));
	}
	void MyCamera::OnUpdate() {
		if (m_Stage == nullptr) return;

		float elapsed = App::GetApp()->GetElapsedTime();
		Vec3 eye = GetEye();
		Vec3 at = GetAt();
		auto playerTransform = m_player.lock();
		if (playerTransform != nullptr) {
			Vec3 playerPos = playerTransform->GetWorldPosition();
			if (m_Stage->GetGameMode() == GameStage::GameMode::InGame) {
				if (m_ScrollSpeed == 0) {
					if (playerPos.y > m_HighY && playerPos.y - m_CameraHight / 2.0f > m_Stage->GetRightBottom().y && playerPos.y + m_CameraHight / 2.0f < m_Stage->GetLeftTop().y) {
						at.y = playerPos.y;
						eye.y = playerPos.y;

						m_HighY = playerPos.y;

					}
					
				}

				if (m_ScrollSpeed != 0) {
					at.y += m_ScrollSpeed * elapsed;
					eye.y = at.y;
				}
				SetEye(eye);
				SetAt(at);
			}

			else if (m_Stage->IsView()) {
				at.y += 0.01f;
				eye.y += 0.01f;

				if (at.y > 10.0f) {
					StartCamera();
				}
				else {
					SetEye(eye);
					SetAt(at);
				}
			}
			
			
		}
		
	}

	void MyCamera::SetPlayer(weak_ptr<Player> player) {
		auto s_player = player.lock();
		m_player = s_player->GetComponent<Transform>();
	}

	void MyCamera::SetStageAt(float hight) {
		m_HighY = hight;
		Vec3 at = GetAt();
		Vec3 eye = GetEye();
		at.y = hight;
		eye.y = hight;
		SetAt(at);
		SetEye(eye);
	}
	void MyCamera::StartCamera() {
		SetAt(m_StartAt);
		SetEye(m_StartEye);
		m_Stage->GameStart();
	}
}
//end basecross
