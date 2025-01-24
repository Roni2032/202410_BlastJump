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

	void Player::OnCreate()
	{
		PlayerInitDraw();
		PlayerInitBCGravity(true); //�d�͂��ɓǂݍ��܂��邱��
		PlayerInitBCCollObb();
		PlayerInitTransform(Vec3(3.0f, 2.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));

		PlayerInitHasBomb(15);
		ResetAirBombLimit();

		AddTag(L"Player");
		m_GameStage = GetTypeStage<GameStage>();
		m_EffectGoalCount = 0;

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

		if (InputKeyboard::GetInstance().InputKey(InputKeyboard::keyPressed, 'Z'))
		{
		}
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
		}
	}

	void Player::PlayerInitDraw()
	{
		m_Draw = AddComponent<PNTBoneModelDraw>();
		m_Draw->SetMeshResource(m_PlayerModelFull);
		m_Draw->SetTextureResource(m_PlayerModelTex);
		m_ModelSpanMat.affineTransformation
		(
			m_ModelScale,
			m_ModelRotOrigin,
			m_ModelRotVec,
			m_ModelTrans
		);
		m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

		const uint8_t animationFrameLength = 60;
		const float useFps = 60.0f;


		m_Draw->AddAnimation(m_PlayerModelAnimIdle,         m_StartAnimationFrame[ModelAnimation::Idle], animationFrameLength, true, useFps);
		m_Draw->AddAnimation(m_PlayerModelAnimMove,         m_StartAnimationFrame[ModelAnimation::Move], animationFrameLength, true, useFps);
		m_Draw->AddAnimation(m_PlayerModelAnimJump,         m_StartAnimationFrame[ModelAnimation::Jump], animationFrameLength, false, useFps);
		m_Draw->AddAnimation(m_PlayerModelAnimThrowDefault, m_StartAnimationFrame[ModelAnimation::ThrowDefault], animationFrameLength, false, useFps);
		m_Draw->AddAnimation(m_PlayerModelAnimThrowUp,      m_StartAnimationFrame[ModelAnimation::ThrowUp], animationFrameLength, false, useFps);
		m_Draw->AddAnimation(m_PlayerModelAnimThrowDown,    m_StartAnimationFrame[ModelAnimation::ThrowDown], animationFrameLength, false, useFps);
		m_Draw->AddAnimation(m_PlayerModelAnimWin,          m_StartAnimationFrame[ModelAnimation::Win], animationFrameLength, true, useFps);
		m_Draw->AddAnimation(m_PlayerModelAnimLose,         m_StartAnimationFrame[ModelAnimation::Lose], animationFrameLength, true, useFps);
		m_Draw->AddAnimation(m_PlayerModelAnimStun,         m_StartAnimationFrame[ModelAnimation::Stun], animationFrameLength, false, useFps);

		m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimIdle);
		m_Draw->SetMeshResource(m_PlayerModelFull);
	}
	
	void Player::PlayerInitBCCollObb()
	{
		m_BCCollObb = AddComponent<BCCollisionObb>(3.0f, L"Stage");
		m_BCCollObb->SetSize(Vec3(0.75f, 1.5f, 0.75f));
		m_BCCollObb->SetGap(Vec3(0.1f, 0.5f, 0.0f));
		m_BCCollObb->AddSlipTag(L"Item");
	}

	void Player::UpdateInputDevice()
	{
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		InputKeyboard::GetInstance().UpdateKeyState(keyState);

		auto cntlState = App::GetApp()->GetInputDevice().GetControlerVec();
		InputController::GetInstance().UpdateCntlState(cntlState);
	}

	void Player::PlayerInitTransform(const Vec3 pos, const Vec3 scale)
	{
		m_Transform = GetComponent<Transform>();
		m_Pos = pos;
		m_Transform->SetPosition(pos);
		m_Transform->SetScale(scale);
	}

	void Player::PlayerMove()
	{
		float deltaTime = App::GetApp()->GetElapsedTime();
		if (GetIsClear() == true)
		{
			PlayerAnimationChangeClear();
			PlayEffectGoal();

			return;
		}

		if (GetIsInGame() == false) { return; }
		
		if (m_IsStun) 
		{
			if (m_StunTime > 0) 
			{
				m_StunTime -= deltaTime;
				PlayerAnimationChangeStun();
			}
			else 
			{
				m_StunTime = 0.0f;
				m_IsStun = false;
			}
			return;
		}

		Vec2 cntlMoveVec = InputController::GetInstance().InputStick(0, 1);
		float smoothWalkSpeed = cntlMoveVec.x * m_WalkSpeed;
		float smoothWalkSpeedAir = m_AirLateralMovementSave * m_WalkSpeed;

		if ((smoothWalkSpeed != 0.0f) && !m_IsJumping)
		{
			m_Pos.x += smoothWalkSpeed * deltaTime;
			m_IsMoving = true;
		}
		else if ((smoothWalkSpeed == 0.0f) && !m_IsJumping)
		{
			m_IsMoving = false;
		}

		if (m_IsJumping)
		{
			m_Pos.x += smoothWalkSpeedAir * deltaTime;
		}

		Vec2 cntlBombVec = InputController::GetInstance().InputStick(0, 2);
		m_BombVec = cntlBombVec * m_BombShotSpeed;

		bool cntlL = InputController::GetInstance().InputButton(0, InputController::buttonPressed, XINPUT_GAMEPAD_LEFT_SHOULDER);
		if (cntlL && (IsPlayerOnAir() == false))
		{
			PlayerJump();
			PlayerAnimationChangeJump();
		}

		bool cntlR = InputController::GetInstance().InputButton(0, InputController::buttonPressed, XINPUT_GAMEPAD_RIGHT_SHOULDER);
		if (cntlR && (IsCanBombCreate() == true))
		{
			PlayerBombShot();
			PlayerAnimationChangeThrow(cntlBombVec);
		}

		m_Transform->SetPosition(m_Pos);
	}

	void Player::PlayerInitBCGravity(const bool active)
	{
		if (active == false) { return; }

		m_BCGravity = AddComponent<BCGravity>();
	}

	void Player::PlayerJump()
	{
		Vec2 cntlMoveVec = InputController::GetInstance().InputStick(0, 1);

		m_BCGravity->Jump(m_JumpPower);
		m_AirLateralMovementSave = cntlMoveVec.x;
		m_IsJumping = true;
	}

	void Player::PlayerBombShot()
	{
		if (IsCanBombCreate() == false) { return; }

		auto getStage = GetStage();
		getStage->AddGameObject<Bomb>(m_Pos + Vec3(0.0f,0.7f,0), m_BombVec, 3.0f, 3.0f, 18.5f);

		SubtractHasBomb(1);

		if (IsPlayerOnAir() == true) { SubtractAirBombLimit(); }

		m_ThrowCoolTime = 0.07f;
		m_IsBombCreate = true;
	}

	void Player::ThrowCoolTimeUpdate()
	{
		if (m_ThrowCoolTime <= 0.0f)
		{
			m_IsBombCreate = false;
			return;
		}

		float deltaTime = App::GetApp()->GetElapsedTime();

		m_ThrowCoolTime -= m_ThrowCoolTimeSpeed * deltaTime;

	}

	bool Player::IsCanBombCreate()
	{
		if (m_HasBomb <= 0) { return false; }
		if (m_CurrentAirBombLimit <= 0) { return false; }
		if (m_IsBombCreate == true) { return false; }
		return true;
	}

	bool Player::IsPlayerOnAir()
	{
		if (m_IsJumping || m_IsBlownAway) { return true; }
		return false;
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

	bool Player::GetIsInGame()
	{
		if (GetTypeStage<GameStage>()->IsPlaying()) { return true; }
		return false;
	}

	void Player::PlayerAnimationUpdateMove()
	{
		float deltaTime = App::GetApp()->GetElapsedTime();
		m_Draw->UpdateAnimation(deltaTime);

		//�ʏ펞�łȂ���ΏI��
		if (GetIsClear() == true) { return; }
		if (GetIsInGame() == false) { return; }

		//�X�^�����Ă���I��
		if (m_IsStun) { return; }

		const auto getCurrentAnim = m_Draw->GetCurrentAnimation();

		//���f���̌��������߂�
		Vec2 cntlMoveVec = InputController::GetInstance().InputStick(0, 1);
		if (cntlMoveVec.x > 0.0f) { m_ModelRotVec.y = -XM_PIDIV2; }
		if (cntlMoveVec.x < 0.0f) { m_ModelRotVec.y = XM_PIDIV2; }

		//�����Ă��āA���e�𓊂��Ă��炸�A�n��ɂ��鎞
		if (m_IsMoving && !m_IsBombCreate && (IsPlayerOnAir() == false))
		{
			m_ModelSpanMat.affineTransformation
			(
				m_ModelScale,
				m_ModelRotOrigin,
				m_ModelRotVec,
				m_ModelTrans
			);
			m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

			if (getCurrentAnim == m_PlayerModelAnimMove) { return; }
			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimMove);

		}

		//�~�܂��Ă��āA���e�𓊂��Ă��炸�A�n��ɂ��鎞
		if (!m_IsMoving && !m_IsBombCreate && (IsPlayerOnAir() == false))
		{
			m_ModelSpanMat.affineTransformation
			(
				m_ModelScale,
				m_ModelRotOrigin,
				m_ModelRotVec,
				m_ModelTrans
			);
			m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

			Vec3 getWorldPosition = GetComponent<Transform>()->GetWorldPosition();
			m_GameStage->PlayParticle<ParticleRunDust>(L"PCL_RUNDUST", Vec3(getWorldPosition.x, getWorldPosition.y - 0.5f, getWorldPosition.z));

			if (getCurrentAnim == m_PlayerModelAnimIdle) { return; }
			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimIdle);
		}

	}

	void Player::PlayerAnimationChangeJump()
	{
		if (GetIsClear() == true) { return; }
		if (GetIsInGame() == false) { return; }

		m_ModelSpanMat.affineTransformation
		(
			m_ModelScale,
			m_ModelRotOrigin,
			m_ModelRotVec,
			m_ModelTrans
		);
		m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

		m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimJump);
	}

	void Player::PlayerAnimationChangeThrow(const Vec2 cntlBombVec)
	{
		if (GetIsClear() == true) { return; }
		if (GetIsInGame() == false) { return; }

		const float neutralZoneLine = 0.75f;

		if (cntlBombVec.x > 0.0f) { m_ModelRotVec.y = -XM_PIDIV2; }
		if (cntlBombVec.x < 0.0f) { m_ModelRotVec.y = XM_PIDIV2; }

		m_ModelSpanMat.affineTransformation
		(
			m_ModelScale,
			m_ModelRotOrigin,
			m_ModelRotVec,
			m_ModelTrans
		);
		m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

		if (cntlBombVec.y == 0.0f)
		{
			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimThrowDown);
		}
		else if (cntlBombVec.y <= neutralZoneLine && cntlBombVec.y >= -neutralZoneLine)
		{
			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimThrowDefault);
		}
		else if (cntlBombVec.y > neutralZoneLine)
		{
			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimThrowUp);
		}
		else if ((cntlBombVec.y < -neutralZoneLine))
		{
			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimThrowDown);
		}
	}

	void Player::PlayerAnimationChangeDeath()
	{
		m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimLose);
	}

	void Player::PlayerAnimationChangeClear()
	{
		const auto getCurrentAnim = m_Draw->GetCurrentAnimation();

		m_ModelRotVec.y = 0.0f;

		if (getCurrentAnim == m_PlayerModelAnimWin) { return; }
		m_ModelSpanMat.affineTransformation
		(
			m_ModelScale,
			m_ModelRotOrigin,
			m_ModelRotVec,
			m_ModelTrans
		);
		m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

		m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimWin);
	}

	void Player::PlayerAnimationChangeStun()
	{
		const auto getCurrentAnim = m_Draw->GetCurrentAnimation();

		if (getCurrentAnim == m_PlayerModelAnimStun) { return; }
		m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimStun);
	}

	void Player::PlayEffectGoal()
	{
		//����ɒB�����珈���I��
		if (m_EffectGoalCount >= 8) { return; }

		float deltaTime = App::GetApp()->GetElapsedTime();

		Vec3 getWorldPosition = GetComponent<Transform>()->GetWorldPosition();

		//�N�[���^�C�����[���ȉ��̏ꍇ�A�p�[�e�B�N�����Đ�
		if (m_EffectCoolTime <= 0.0f)
		{
			const int8_t xRndMin = -4;
			const int8_t xRndMax =  4;
			const int8_t yRndMin = -4;
			const int8_t yRndMax =  4;

			int xRnd = rand() % (xRndMax - xRndMin + 1) + xRndMin;
			int yRnd = rand() % (yRndMax - yRndMin + 1) + yRndMin;

			m_GameStage->PlayParticle<ParticleGoal>(L"PCL_GOAL",
				Vec3(getWorldPosition.x + static_cast<float>(xRnd), getWorldPosition.y + static_cast<float>(yRnd), getWorldPosition.z));

			m_EffectGoalCount++;

			//�N�[���^�C�������Z�b�g
			m_EffectCoolTime = 0.25f;
		}

		//�N�[���^�C��������������
		if (m_EffectCoolTime > 0.0f)
		{
			m_EffectCoolTime -= m_EffectCoolTimeSpeed * deltaTime;
		}
	}

	void Player::PlayerStun(float time) {
		m_IsStun = true;
		m_StunTime = time;
	}

	void Player::PlayerInitDebugString()
	{
		m_String = AddComponent<StringSprite>();
		m_String->SetText(L"");
		m_String->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		m_String->SetTextRect(Rect2D<float>(16.0f, 16.0f, 510.0f, 230.0f));
		m_String->SetDrawActive(true);
		SetDrawLayer(2);
	}

	void Player::PlayerShowDebugLog()
	{
		const int numberOfDecimalPlaces = 2;
		const auto showNumberFixed = Util::FloatModify::Fixed;

		const wstring separator = L",\t";
		const wstring indention = L"\n";

		const auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring strFps(L"FPS: ");
		strFps += Util::UintToWStr(fps);
		strFps += indention;

		const auto getPos = GetComponent<Transform>()->GetPosition();
		wstring strPosition(L"Position: ");
		strPosition += L"X=" + Util::FloatToWStr(getPos.x, numberOfDecimalPlaces, showNumberFixed) + separator;
		strPosition += L"Y=" + Util::FloatToWStr(getPos.y, numberOfDecimalPlaces, showNumberFixed) + separator;
		strPosition += L"Z=" + Util::FloatToWStr(getPos.z, numberOfDecimalPlaces, showNumberFixed) + indention;

		auto velocity = m_BCGravity->GetVelocity();
		wstring strVelocity(L"Velocity: ");
		strVelocity += L"VX=" + Util::FloatToWStr(velocity.x, numberOfDecimalPlaces, showNumberFixed) + separator;
		strVelocity += L"VY=" + Util::FloatToWStr(velocity.y, numberOfDecimalPlaces, showNumberFixed) + separator;
		strVelocity += L"VZ=" + Util::FloatToWStr(velocity.z, numberOfDecimalPlaces, showNumberFixed) + indention;

		const auto hasBomb = m_HasBomb;
		const auto currentAirBombLimit = m_CurrentAirBombLimit;
		const auto throwCoolTime = m_ThrowCoolTime;
		const auto getIsCanBombCreate = IsCanBombCreate();
		wstring strBombCanUseInfo(L"BombCanUseInfo: ");
		strBombCanUseInfo += L"HB=" + Util::IntToWStr(hasBomb) + separator;
		strBombCanUseInfo += L"ABL=" + Util::IntToWStr(currentAirBombLimit) + separator;
		strBombCanUseInfo += L"TCT=" + Util::FloatToWStr(throwCoolTime, numberOfDecimalPlaces, showNumberFixed) + separator;
		strBombCanUseInfo += L"CBC=" + Util::IntToWStr(getIsCanBombCreate) + indention;

		const auto bombVec = m_BombVec;
		wstring strBombVec(L"BombVec: ");
		strBombVec += L"BVX=" + Util::FloatToWStr(bombVec.x, numberOfDecimalPlaces, showNumberFixed) + separator;
		strBombVec += L"BVY=" + Util::FloatToWStr(bombVec.y, numberOfDecimalPlaces, showNumberFixed) + separator;
		strBombVec += L"BVZ=" + Util::FloatToWStr(bombVec.z, numberOfDecimalPlaces, showNumberFixed) + indention;

		const auto getCurrentAnim = m_Draw->GetCurrentAnimation();
		wstring strCurrentAnim(L"CurrentAnim: ");
		strCurrentAnim += L"CUA=" + getCurrentAnim + indention;

		const auto isMoving = m_IsMoving;
		wstring strIsMoving(L"IsMoving: ");
		strIsMoving += L"ISM=" + Util::IntToWStr(isMoving) + indention;

		const auto isJumping = m_IsJumping;
		const auto isBrownAway = m_IsBlownAway;
		const auto getIsPlayerOnAir = IsPlayerOnAir();
		wstring strIsOnAir(L"IsPlayerOnAir: ");
		strIsOnAir += L"ISJ=" + Util::IntToWStr(isJumping) + separator;
		strIsOnAir += L"ISBA=" + Util::IntToWStr(isBrownAway) + separator;
		strIsOnAir += L"ISPOA=" + Util::IntToWStr(getIsPlayerOnAir) + indention;

		const auto isDead = m_IsDead;
		wstring strIsDead(L"IsDead: ");
		strIsDead += L"ISD=" + Util::IntToWStr(isDead) + indention;

		const auto effectGoalCount = m_EffectGoalCount;
		const auto effectCoolTime = m_EffectCoolTime;
		wstring strEffectGoalCount(L"EffectGoalCount: ");
		strEffectGoalCount += L"EGC=" + Util::IntToWStr(effectGoalCount) + separator;
		strEffectGoalCount += L"ECT=" + Util::FloatToWStr(effectCoolTime, numberOfDecimalPlaces, showNumberFixed) + indention;

		const wstring strShow = strFps +
			strPosition +
			strVelocity +
			strBombCanUseInfo +
			strBombVec +
			strCurrentAnim +
			strIsMoving +
			strIsOnAir +
			strIsDead +
			strEffectGoalCount;

		m_String = GetComponent<StringSprite>();
		m_String->SetText(strShow);
	}
}
//end basecross

