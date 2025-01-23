/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void MyCamera::OnCreate() {
		SetWidth(m_CameraWidth);
		SetHeight(m_CameraHight);

		SetFovY(XMConvertToRadians(m_DefaultFovY));
	}
	void MyCamera::OnUpdate() {
		if (m_Stage == nullptr) return;

		float elapsed = App::GetApp()->GetElapsedTime();
		Vec3 eye = GetEye();
		Vec3 at = GetAt();
		auto playerTransform = m_player.lock();
		if (playerTransform != nullptr) {
			Vec3 playerPos = playerTransform->GetWorldPosition();
			if (m_Stage->GetGameMode() == GameMode::InGame) {
				if (m_ScrollSpeed == 0) {
					if (playerPos.y > m_HighY) {
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

			else if (m_Stage->IsView()) {
				
				float fovY = GetFovY();
				fovY -= XMConvertToRadians(10.0f) * elapsed;
				SetFovY(fovY);

				at.y += 0.01f;
				eye.y += 0.01f;
				if (at.y > 10.0f) {
					StartCamera();
				}
			}
			float stageBottom = m_Stage->GetRightBottom().y + m_CameraHight / 2.0f;
			float stageTop = m_Stage->GetLeftTop().y - m_CameraHight / 2.0f;
			at.y = min(stageTop, at.y);
			at.y = max(stageBottom, at.y);

			eye.y = at.y;

			/*if (at.y - m_CameraHight / 2.0f < m_Stage->GetRightBottom().y) {
				at.y = m_Stage->GetRightBottom().y + m_CameraHight / 2.0f;
				eye.y = m_Stage->GetRightBottom().y + m_CameraHight / 2.0f;
			}
			if (at.y + m_CameraHight / 2.0f < m_Stage->GetRightBottom().y) {
				at.y = m_Stage->GetRightBottom().y - m_CameraHight / 2.0f - 0.5f;
				eye.y = m_Stage->GetRightBottom().y - m_CameraHight / 2.0f - 0.5f;
			}*/
			SetEye(eye);
			SetAt(at);


			if (m_Stage->IsView()) {
				auto device = App::GetApp()->GetInputDevice().GetControlerVec()[0];

				if (device.bConnected) {
					if (device.wPressedButtons & XINPUT_GAMEPAD_A) {
						StartCamera();
					}
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
		SetFovY(XMConvertToRadians(m_DefaultFovY));
<<<<<<< HEAD
		m_HighY = m_StartAt.y;
=======
>>>>>>> Yuya_task
		m_Stage->GameStart();
	}
	void MyCamera::RespawnCamera() {
		auto player = m_player.lock();
		if (player == nullptr) return;
		SetStageAt(player->GetPosition().y);
	}
}
//end basecross
