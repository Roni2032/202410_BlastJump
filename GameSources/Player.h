/*!
@file Player.h
@brief ÉvÉåÉCÉÑÅ[Ç»Ç«
*/

#pragma once
#include "stdafx.h"

#include "GameStage.h"
#include "BCCollision.h"
#include "BCGravity.h"

namespace basecross {

	class Player : public GameObject
	{
	public:

		Player(const shared_ptr<Stage>& StagePtr);

		~Player() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;

	private:

		shared_ptr<PNTBoneModelDraw> m_Draw;
		const wstring m_PlayerModelIdle = L"PLAYER_MD_IDLE";
		const wstring m_PlayerModelMove = L"PLAYER_MD_MOVE";
		const wstring m_PlayerModelJump = L"PLAYER_MD_JUMP";
		const wstring m_PlayerModelThrowDefault = L"PLAYER_MD_THROW_DEFAULT";
		const wstring m_PlayerModelThrowUp = L"PLAYER_MD_THROW_UP";
		const wstring m_PlayerModelThrowDown = L"PLAYER_MD_THROW_DOWN";
		const wstring m_PlayerModelWin = L"PLAYER_MD_WIN";
		const wstring m_PlayerModelLose = L"PLAYER_MD_LOSE";

		const wstring m_PlayerModelTex = L"PLAYER_MD_TEX";

		const wstring m_PlayerModelAnimIdle = L"PLAYER_ANIM_IDLE";
		const wstring m_PlayerModelAnimMove = L"PLAYER_ANIM_MOVE";
		const wstring m_PlayerModelAnimJump = L"PLAYER_ANIM_JUMP";
		const wstring m_PlayerModelAnimThrowDefault = L"PLAYER_ANIM_THROW_DEFAULT";
		const wstring m_PlayerModelAnimThrowUp = L"PLAYER_ANIM_THROW_UP";
		const wstring m_PlayerModelAnimThrowDown = L"PLAYER_ANIM_THROW_DOWN";
		const wstring m_PlayerModelAnimWin = L"PLAYER_ANIM_WIN";
		const wstring m_PlayerModelAnimLose = L"PLAYER_ANIM_LOSE";

		Mat4x4 m_ModelSpanMat;
		Vec3 m_ModelScale = Vec3(0.45f);
		const Vec3 m_ModelRotOrigin = Vec3(0.0f);
		Vec3 m_ModelRotVec = Vec3(0.0f);
		const Vec3 m_ModelTransIdle = Vec3(0.0f, -1.0f, 0.0f);
		const Vec3 m_ModelTransMove = Vec3(0.0f, -2.0f, 0.0f);
		const Vec3 m_ModelTransJump = Vec3(0.0f, -1.0f, 0.0f);
		const Vec3 m_ModelTransThrow = Vec3(0.0f, -1.0f, 0.0f);
		const Vec3 m_ModelTransWin = Vec3(0.0f, -1.0f, 0.0f);
		void PlayerInitDraw()
		{
			m_Draw = AddComponent<PNTBoneModelDraw>();
			m_Draw->SetMeshResource(m_PlayerModelIdle);
			m_Draw->SetTextureResource(m_PlayerModelTex);
			m_ModelSpanMat.affineTransformation
			(
				m_ModelScale,
				m_ModelRotOrigin,
				m_ModelRotVec,
				m_ModelTransIdle
			);
			m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

			const uint8_t useFps = 60;

			m_Draw->AddAnimation(m_PlayerModelAnimIdle, 0, useFps, false, 60);
			m_Draw->AddAnimation(m_PlayerModelAnimMove, 0, useFps, true, 90);
			m_Draw->AddAnimation(m_PlayerModelAnimJump, 0, useFps, false, 60);
			m_Draw->AddAnimation(m_PlayerModelAnimThrowDefault, 0, useFps, false, 150);
			m_Draw->AddAnimation(m_PlayerModelAnimThrowUp, 0, useFps, false, 150);
			m_Draw->AddAnimation(m_PlayerModelAnimThrowDown, 0, useFps, false, 120);
			m_Draw->AddAnimation(m_PlayerModelAnimWin, 0, useFps, true, 60);
			m_Draw->AddAnimation(m_PlayerModelAnimLose, 0, useFps, false, 60);

			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimIdle);
			m_Draw->SetMeshResource(m_PlayerModelIdle);
		}

		shared_ptr<BCCollisionObb> m_BCCollObb;
		void PlayerInitBCCollObb()
		{
			m_BCCollObb = AddComponent<BCCollisionObb>(3.0f, L"Stage");
			m_BCCollObb->SetSize(Vec3(0.75f, 1.5f, 0.75f));
			m_BCCollObb->SetGap(Vec3(0.1f, 0.5f, 0.0f));
			m_BCCollObb->AddSlipTag(L"Item");
		}

		void UpdateInputDevice()
		{
			auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
			InputKeyboard::GetInstance().UpdateKeyState(keyState);

			auto cntlState = App::GetApp()->GetInputDevice().GetControlerVec();
			InputController::GetInstance().UpdateCntlState(cntlState);
		}

		shared_ptr<Transform> m_Transform;
		Vec3 m_Pos = Vec3(0.0f);
		const float m_WalkSpeed = 2.0f;
		void PlayerInitTransform(const Vec3 pos, const Vec3 scale)
		{
			m_Transform = GetComponent<Transform>();
			m_Pos = pos;
			m_Transform->SetPosition(pos);
			m_Transform->SetScale(scale);
		}

		bool m_IsMoving = false;
		void PlayerMove()
		{
			float deltaTime = App::GetApp()->GetElapsedTime();

			if (GetIsClear() == true)
			{
				PlayerAnimationChangeClear();
				return;
			}

			if (GetIsInGame() == false) { return; }

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

			//m_Transform->SetPosition(m_Pos);
		}

		shared_ptr<BCGravity> m_BCGravity;
		void PlayerInitBCGravity(const bool active)
		{
			if (active == false) { return; }

			m_BCGravity = AddComponent<BCGravity>();
		}

		const Vec3 m_JumpPower = Vec3(0.0f, 5.0f, 0.0f);
		bool m_IsJumping = false;
		float m_AirLateralMovementSave = 0.0f;
		void PlayerJump()
		{
			Vec2 cntlMoveVec = InputController::GetInstance().InputStick(0, 1);

			m_BCGravity->Jump(m_JumpPower);
			m_AirLateralMovementSave = cntlMoveVec.x;
			m_IsJumping = true;
		}

		bool m_IsBlownAway = false;

		bool m_IsBombCreate = false;

		float m_ThrowCoolTime = 0.0f;
		const float m_ThrowCoolTimeSpeed = 0.1f;

		const float m_BombShotSpeed = 10.0f;
		Vec3 m_BombVec = Vec3(0.0f);

		uint8_t m_HasBomb = 0;

		const uint8_t m_AirBombLimit = 1;
		uint8_t m_CurrentAirBombLimit = 0;
		void ResetAirBombLimit() { m_CurrentAirBombLimit = m_AirBombLimit; }
		void SubtractAirBombLimit() { m_CurrentAirBombLimit--; }

		void PlayerBombShot();

		void ThrowCoolTimeUpdate()
		{
			if (m_ThrowCoolTime <= 0.0f)
			{
				m_IsBombCreate = false;
				return;
			}

			float deltaTime = App::GetApp()->GetElapsedTime();

			m_ThrowCoolTime -= m_ThrowCoolTimeSpeed * deltaTime;

		}

		bool IsCanBombCreate()
		{
			if (m_HasBomb <= 0) { return false; }
			if (m_CurrentAirBombLimit <= 0) { return false; }
			if (m_IsBombCreate == true) { return false; }
			return true;
		}

		bool IsPlayerOnAir()
		{
			if (m_IsJumping || m_IsBlownAway) { return true; }
			return false;
		}

		bool m_IsDead = false;
		const uint8_t m_DeadLine = 6;
		void PlayerDeathLogicUpdate();

		bool GetIsClear();
		bool GetIsInGame();

		void PlayerAnimationUpdateMove()
		{
			float deltaTime = App::GetApp()->GetElapsedTime();
			m_Draw->UpdateAnimation(deltaTime);

			if (GetIsClear() == true) { return; }
			if (GetIsInGame() == false) { return; }

			const auto getCurrentAnim = m_Draw->GetCurrentAnimation();

			Vec2 cntlMoveVec = InputController::GetInstance().InputStick(0, 1);
			if (cntlMoveVec.x > 0.0f) { m_ModelRotVec.y = -XM_PIDIV2; }
			if (cntlMoveVec.x < 0.0f) { m_ModelRotVec.y = XM_PIDIV2; }

			if (m_IsMoving && !m_IsBombCreate && (IsPlayerOnAir() == false))
			{
				m_ModelSpanMat.affineTransformation
				(
					m_ModelScale,
					m_ModelRotOrigin,
					m_ModelRotVec,
					m_ModelTransMove
				);
				m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

				if (getCurrentAnim == m_PlayerModelAnimMove) { return; }
				m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimMove);
				m_Draw->SetMeshResource(m_PlayerModelMove);
			}

			if (!m_IsMoving && !m_IsBombCreate && !m_IsJumping)
			{
				m_ModelSpanMat.affineTransformation
				(
					m_ModelScale,
					m_ModelRotOrigin,
					m_ModelRotVec,
					m_ModelTransIdle
				);
				m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

				if (getCurrentAnim == m_PlayerModelAnimIdle) { return; }
				m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimIdle);
				m_Draw->SetMeshResource(m_PlayerModelIdle);
			}

		}

		void PlayerAnimationChangeJump()
		{
			if (GetIsClear() == true) { return; }
			if (GetIsInGame() == false) { return; }

			m_ModelSpanMat.affineTransformation
			(
				m_ModelScale,
				m_ModelRotOrigin,
				m_ModelRotVec,
				m_ModelTransJump
			);
			m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimJump);
			m_Draw->SetMeshResource(m_PlayerModelJump);
		}

		void PlayerAnimationChangeThrow(const Vec2 cntlBombVec)
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
				m_ModelTransThrow
			);
			m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

			if (cntlBombVec.y == 0.0f)
			{
				m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimThrowDown);
				m_Draw->SetMeshResource(m_PlayerModelThrowDown);
			}
			else if (cntlBombVec.y <= neutralZoneLine && cntlBombVec.y >= -neutralZoneLine)
			{
				m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimThrowDefault);
				m_Draw->SetMeshResource(m_PlayerModelThrowDefault);
			}
			else if (cntlBombVec.y > neutralZoneLine)
			{
				m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimThrowUp);
				m_Draw->SetMeshResource(m_PlayerModelThrowUp);
			}
			else if ((cntlBombVec.y < -neutralZoneLine))
			{
				m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimThrowDown);
				m_Draw->SetMeshResource(m_PlayerModelThrowDown);
			}
		}

		void PlayerAnimationChangeDeath()
		{
			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimLose);
			m_Draw->SetMeshResource(m_PlayerModelLose);
		}

		void PlayerAnimationChangeClear()
		{
			const auto getCurrentAnim = m_Draw->GetCurrentAnimation();

			m_ModelRotVec.y = 0.0f;

			if (getCurrentAnim == m_PlayerModelAnimWin) { return; }
			m_ModelSpanMat.affineTransformation
			(
				m_ModelScale,
				m_ModelRotOrigin,
				m_ModelRotVec,
				m_ModelTransWin
			);
			m_Draw->SetMeshToTransformMatrix(m_ModelSpanMat);

			m_Draw->ChangeCurrentAnimation(m_PlayerModelAnimWin);
			m_Draw->SetMeshResource(m_PlayerModelWin);
		}

		shared_ptr<StringSprite> m_String;
		void PlayerInitDebugString()
		{
			m_String = AddComponent<StringSprite>();
			m_String->SetText(L"");
			m_String->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
			m_String->SetTextRect(Rect2D<float>(16.0f, 16.0f, 510.0f, 230.0f));
			m_String->SetDrawActive(true);
			SetDrawLayer(1);
		}

		void PlayerShowDebugLog()
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

			const wstring strShow = strFps +
				strPosition +
				strVelocity +
				strBombCanUseInfo +
				strBombVec +
				strCurrentAnim +
				strIsMoving +
				strIsOnAir +
				strIsDead;

			m_String = GetComponent<StringSprite>();
			m_String->SetText(strShow);
		}

	public:
		void PlayerInitHasBomb(const uint8_t n) { m_HasBomb = n; }
		const uint8_t GetHasBomb() { return m_HasBomb; }
		Vec3 GetBombVec() { return m_BombVec; }
		void AddHasBomb(const uint8_t n) { m_HasBomb += n; }
		void SubtractHasBomb(const uint8_t n) { m_HasBomb -= n; }
	};


}
//end basecross

