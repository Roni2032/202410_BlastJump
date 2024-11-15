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
		if (m_Stage != nullptr) {
			if (m_Stage->GetGameMode() != GameStage::GameMode::InGame) {
				return;
			}
		}
		float elapsed = App::GetApp()->GetElapsedTime();
		Vec3 eye = GetEye();
		Vec3 at = GetAt();
		
		auto playerTransform = m_player.lock();
		if (playerTransform != nullptr && m_ScrollSpeed == 0) {
			Vec3 playerPos = playerTransform->GetPosition();
			if (playerPos.y > m_HighY && playerPos.y - m_CameraHight / 2.0f > m_Stage->GetBottomY() && playerPos.y + m_CameraHight / 2.0f < m_Stage->GetTopY()) {
				at.y = playerPos.y;
				eye.y = playerPos.y;

				m_HighY = playerPos.y;
			}
			if (playerPos.y - m_HighY < -m_CameraHight / 2.0f - 2.0f) {
				//プレイヤーの死亡処理
				
			}
		}
		
		if (m_ScrollSpeed != 0) {
			at.y += m_ScrollSpeed * elapsed;
			eye.y = at.y;
		}

		SetEye(eye);
		SetAt(at);

		
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
