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

		m_PlayerPosArrow = m_Stage->AddGameObject<OutOfCameraPlayerPos>();
	}
	void MyCamera::OnUpdate() {
		auto cntlState = App::GetApp()->GetInputDevice().GetControlerVec();
		InputController::GetInstance().UpdateCntlState(cntlState);

		if (m_Stage == nullptr) return;

		float stageBottom = m_Stage->GetRightBottom().y + m_CameraHight / 2.0f;
		float stageTop = m_Stage->GetLeftTop().y - m_CameraHight / 2.0f;

		float elapsed = App::GetApp()->GetElapsedTime();
		Vec3 eye = GetEye();
		Vec3 at = GetAt();
		auto playerTransform = m_player.lock();
		if (playerTransform != nullptr) {
			Vec3 playerPos = playerTransform->GetWorldPosition();

			float speedBoost = 1.0f;
			if (m_Stage->GetGameMode() == GameMode::Clear || speedBoost != 1.0f) {
				if (at.y < stageTop) {
					speedBoost = 8.0f;
				}
			}

			if (InputController::GetInstance().InputButton(0, InputController::buttonPush, XINPUT_GAMEPAD_A) &&
				m_Stage->GetGameMode() == GameMode::InGame)
			{
				if (at.y < stageTop) 
				{
					speedBoost = 8.0f;
				}
			}

			if (m_Stage->GetGameMode() == GameMode::InGame || speedBoost != 1.0f) {
				at.y += m_ScrollSpeed * speedBoost * elapsed;
				eye.y = at.y;
			}

			at.y = min(stageTop, at.y);
			at.y = max(stageBottom, at.y);

			eye.y = at.y;

			SetEye(eye);
			SetAt(at);

			if (m_Stage->IsView()) {
				StartCamera();
				if (m_Fade != nullptr) {
					auto fade = m_Fade->GetComponent<SpriteFade>();
					if (fade->IsFinish() && !fade->IsFadeOut()) {
						
					}
					
				}
			}

			if (m_Stage->IsPlaying()) {
				Vec2 drawPos = Vec2(playerPos.x, -1);
				if (playerPos.y < at.y - m_CameraHight / 2.0f) {
					drawPos.y = at.y - m_CameraHight / 2.0f + 0.5f;
					m_PlayerPosArrow->Draw(drawPos, 0);
				}
				else if (playerPos.y > at.y + m_CameraHight / 2.0f) {
					drawPos.y = at.y + m_CameraHight / 2.0f - 0.5f;
					m_PlayerPosArrow->Draw(drawPos, 1);
				}
				else {
					m_PlayerPosArrow->UnDraw();
				}

			}
			else {
				m_PlayerPosArrow->UnDraw();
			}

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
		m_Stage->GameStart();
	}
	void MyCamera::RespawnCamera() {
		auto player = m_player.lock();
		if (player == nullptr) return;
		SetStageAt(player->GetPosition().y);
	}


	void OutOfCameraPlayerPos::OnCreate() {
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SQUARE");
		draw->SetTextureResource(L"ARROW_ORBIT_TEX");
		SetAlphaActive(true);

		m_Trans = GetComponent<Transform>();
		m_Trans->SetScale(Vec3(0.75f));
	}

	void OutOfCameraPlayerPos::Draw(Vec2 pos,float dir) {
		SetDrawActive(true);
		if (dir == 0) {
			m_Trans->SetRotation(Vec3(0, 0, XMConvertToRadians(-90)));
		}
		else {
			m_Trans->SetRotation(Vec3(0, 0, XMConvertToRadians(90)));
		}

		m_Trans->SetPosition(Vec3(pos.x, pos.y, -1.0f));
	}
}
//end basecross
