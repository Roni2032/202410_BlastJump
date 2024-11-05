/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void MyCamera::OnCreate() {
		SetPers(false);
		SetWidth(15);
		SetHeight(10);
	}
	void MyCamera::OnUpdate() {

		Vec3 eye = GetEye();
		Vec3 at = GetAt();
		
		auto playerTransform = m_player.lock();
		if (playerTransform != nullptr) {
			Vec3 playerPos = playerTransform->GetPosition();
			if (playerPos.y > m_HighY) {
				at.y = playerPos.y;

				eye.y = playerPos.y;

				m_HighY = playerPos.y;
			}
			if (playerPos.y - m_HighY < -8.0f) {
				//プレイヤーの死亡処理
				
			}
		}
		
		SetEye(eye);
		SetAt(at);

		
	}

	void MyCamera::SetPlayer(weak_ptr<Player> player) {
		auto s_player = player.lock();
		m_player = s_player->GetComponent<Transform>();
	}
}
//end basecross
