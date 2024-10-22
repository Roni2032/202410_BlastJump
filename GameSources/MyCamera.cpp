/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void MyCamera::OnCreate() {

	}
	void MyCamera::OnUpdate() {

		Vec3 eye = GetEye();
		Vec3 at = GetAt();
		
		auto playerTransform = m_player.lock();
		if (playerTransform != nullptr) {
			Vec3 playerPos = playerTransform->GetPosition();
			at.y = playerPos.y;

			eye.y = playerPos.y;
		}
		
		SetEye(eye);
		SetAt(at);

	}

	void MyCamera::SetPlayer(weak_ptr<GameObject>& player) {
		auto s_player = player.lock();
		m_player = s_player->GetComponent<Transform>();
	}
}
//end basecross
