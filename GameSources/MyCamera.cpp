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
			}
			else if (m_Stage->GetGameMode() == GameStage::GameMode::View) {

			}
			/*at.x = playerPos.x;
			eye.x = playerPos.x;

			if (at.x - m_CameraWidth / 2.0f < m_Stage->GetLeftTop().x ){
				at.x = m_Stage->GetLeftTop().x + m_CameraWidth / 2.0f;
				eye.x = m_Stage->GetLeftTop().x + m_CameraWidth / 2.0f;
			}
			if (at.x + m_CameraWidth / 2.0f > m_Stage->GetRightBottom().x) {
				at.x = m_Stage->GetRightBottom().x - m_CameraWidth / 2.0f;
				eye.x = m_Stage->GetRightBottom().x - m_CameraWidth / 2.0f;
			}*/
			SetEye(eye);
			SetAt(at);
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
}
//end basecross
