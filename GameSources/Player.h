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

		const wstring m_PlayerModelFull = L"PLAYER_MD_FULL";

		const wstring m_PlayerModelTex = L"PLAYER_MD_TEX";

		const wstring m_PlayerModelAnimIdle = L"PLAYER_ANIM_IDLE";
		const wstring m_PlayerModelAnimMove = L"PLAYER_ANIM_MOVE";
		const wstring m_PlayerModelAnimJump = L"PLAYER_ANIM_JUMP";
		const wstring m_PlayerModelAnimThrowDefault = L"PLAYER_ANIM_THROW_DEFAULT";
		const wstring m_PlayerModelAnimThrowUp = L"PLAYER_ANIM_THROW_UP";
		const wstring m_PlayerModelAnimThrowDown = L"PLAYER_ANIM_THROW_DOWN";
		const wstring m_PlayerModelAnimWin = L"PLAYER_ANIM_WIN";
		const wstring m_PlayerModelAnimLose = L"PLAYER_ANIM_LOSE";

		vector<unsigned int> m_StartAnimationFrame = { 0,61,122,183,244,305,366,427 };
		enum ModelAnimation
		{
			Idle = 0,
			Move,
			Jump,
			ThrowDefault,
			ThrowUp,
			ThrowDown,
			Win,
			Lose,
		};

		Mat4x4 m_ModelSpanMat;
		Vec3 m_ModelScale = Vec3(0.45f);
		const Vec3 m_ModelRotOrigin = Vec3(0.0f);
		Vec3 m_ModelRotVec = Vec3(0.0f);
		const Vec3 m_ModelTrans = Vec3(0.0f, -1.0f, 0.0f);
		void PlayerInitDraw();

		shared_ptr<BCCollisionObb> m_BCCollObb;
		void PlayerInitBCCollObb();

		void UpdateInputDevice();

		shared_ptr<Transform> m_Transform;
		shared_ptr<GameStage> m_GameStage;
		Vec3 m_Pos = Vec3(0.0f);
		const float m_WalkSpeed = 2.0f;
		void PlayerInitTransform(const Vec3 pos, const Vec3 scale);

		bool m_IsMoving = false;
		void PlayerMove();

		shared_ptr<BCGravity> m_BCGravity;
		void PlayerInitBCGravity(const bool active);

		const Vec3 m_JumpPower = Vec3(0.0f, 5.0f, 0.0f);
		bool m_IsJumping = false;
		float m_AirLateralMovementSave = 0.0f;
		void PlayerJump();

		bool m_IsBlownAway = false;

		bool m_IsBombCreate = false;

		bool m_IsStun = false;

		float m_StunTime = 0.0f;
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

		void ThrowCoolTimeUpdate();

		bool IsCanBombCreate();

		bool IsPlayerOnAir();

		bool m_IsDead = false;
		const uint8_t m_DeadLine = 6;
		void PlayerDeathLogicUpdate();

		bool GetIsClear();
		bool GetIsInGame();

		void PlayerAnimationUpdateMove();

		void PlayerAnimationChangeJump();

		void PlayerAnimationChangeThrow(const Vec2 cntlBombVec);

		void PlayerAnimationChangeDeath();

		void PlayerAnimationChangeClear();

		uint8_t m_EffectGoalCount = 0;
		float m_EffectCoolTime = 0.0f;
		const float m_EffectCoolTimeSpeed = 1.0f;
		void PlayEffectGoal();

		shared_ptr<StringSprite> m_String;
		void PlayerInitDebugString();

		void PlayerShowDebugLog();

	public:
		void PlayerInitHasBomb(const uint8_t n) { m_HasBomb = n; }
		const uint8_t GetHasBomb() { return m_HasBomb; }
		Vec3 GetBombVec() { return m_BombVec; }
		void AddHasBomb(const uint8_t n) { m_HasBomb += n; }
		void SubtractHasBomb(const uint8_t n) { m_HasBomb -= n; }
		void Stun(float time);
	};


}
//end basecross

