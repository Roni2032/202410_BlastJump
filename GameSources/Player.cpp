/*!
@file Player.cpp
@brief �E�v�E��E��E�C�E��E��E�[�E�Ȃǎ��E��E�
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	}

	void Player::PlayerBombShot()
	{
		if (IsCanBombCreate() == false) { return; }

		auto getStage = GetStage();
		getStage->AddGameObject<Bomb>(m_Pos, m_BombVec, 3.0f, 3.0f, 18.5f);

		SubtractHasBomb(1);

		if (IsPlayerOnAir() == true) { SubtractAirBombLimit(); }

		m_ThrowCoolTime = 0.07f;
		m_IsBombCreate = true;
	}

	void Player::PlayerDeathLogicUpdate()
	{
		if (m_IsDead) { return; }

		if (m_Pos.y < OnGetDrawCamera()->GetEye().y - m_DeadLine) { m_IsDead = true; }

		if (m_IsDead) 
		{ 
			GetTypeStage<GameStage>()->GameOver(); 
			PlayerAnimationChangeDeath();
		}
	}

	bool Player::GetIsClear()
	{
		if (GetTypeStage<GameStage>()->GetGameMode() == 4) { return true; }
		return false;
	}

	void Player::OnCreate()
	{
		PlayerInitDraw();
		PlayerInitBCGravity(true); //�d�͂��ɓǂݍ��܂��邱��
		PlayerInitBCCollObb();
		PlayerInitTransform(Vec3(3.0f, 2.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));

		PlayerInitHasBomb(15);
		ResetAirBombLimit();

		AddTag(L"Player");

		PlayerInitDebugString();
	}

	void Player::OnUpdate()
	{
		UpdateInputDevice();

		PlayerShowDebugLog();

		m_Pos = m_Transform->GetWorldPosition();

		PlayerMove();

		m_Transform->SetWorldPosition(m_Pos);

		PlayerAnimationUpdateMove();
		ThrowCoolTimeUpdate();
		PlayerDeathLogicUpdate();
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		if (Other->FindTag(L"Stage"))
		{
			Other->OnCollisionEnter(GetThis<GameObject>());
		}
	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other)
	{
		if (Other->FindTag(L"Stage"))
		{
			Other->OnCollisionExcute(GetThis<GameObject>());

			auto block = Other->GetComponent<Transform>();
			auto blockPosition = block->GetPosition();
			auto blockScale = block->GetScale();

			auto player = GetComponent<Transform>();
			auto playerPosition = player->GetWorldPosition();
			auto playerScale = player->GetScale();

			if ((playerPosition.y > blockPosition.y) && ((playerPosition.x + playerScale.x * 0.5f) > blockPosition.x) &&
				((playerPosition.x + playerScale.x * 0.5f) < (blockPosition.x + blockScale.x)))
			{
				m_IsJumping = false;
				m_IsBlownAway = false;
				ResetAirBombLimit();
			}
		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		if (Other->FindTag(L"Stage"))
		{
			m_IsBlownAway = true;
			Other->OnCollisionExit(GetThis<GameObject>());
		}
	}

}
//end basecross

