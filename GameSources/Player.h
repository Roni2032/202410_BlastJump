/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"
#include "BCGravity.h"

namespace basecross{

	//前方宣言(各状態)
	class Player;
	class PlayerStateIdle;
	class PlayerStateWalk;
	class PlayerStateThrow;

	//インターフェイス：抽象基底クラス
	class PlayerState
	{
	public:
		virtual ~PlayerState() = default;

		//ユーザー入力を処理する仮想関数
		virtual void HandleInput(shared_ptr<Player>) = 0;

		//フレームごとの更新処理を行う仮想関数
		virtual void PlayerUpdate(shared_ptr<Player>) = 0;

		virtual wstring GetStateName() = 0;

		virtual Col4 GetDiffColor() = 0;
	};

	//コンテキストクラス
	class Player : public GameObject
	{
		//現在の状態を保持するスマートポインタ
		shared_ptr<PlayerState> m_State;

		KEYBOARD_STATE m_KeyState;
		//CONTROLER_STATE m_Controler;

		shared_ptr<basecross::Transform> m_Transform;
		Vec3 m_Pos = Vec3(0.0f);
		shared_ptr<basecross::BcPNTStaticDraw> m_Draw;
		Col4 m_ColBlack = Col4(0.0f, 0.0f, 0.0f, 1.0f);
		Col4 m_TestCol = Col4(0.0f, 0.0f, 0.0f, 1.0f);

		shared_ptr<basecross::CollisionSphere> m_Collision;

		shared_ptr<BCGravity> m_Grav;

		float m_WalkSpeed = 0.1f;

		Vec3 m_JumpPower = Vec3(0.0f, 5.0f, 0.0f);

		bool m_IsBombCreate = false;
		Vec3 m_BombVec = Vec3(0.0f);

	public:
		// コンストラクタ：初期状態を受け取り設定する
		explicit Player(const shared_ptr<Stage>& ptr, shared_ptr<PlayerState> initialState)
			: GameObject(ptr), m_State(move(initialState)) {}

		// 状態を切り替えるためのメソッド
		void SetState(shared_ptr<PlayerState> newState)
		{
			m_State = move(newState);  //新しい状態を適用
		}

		//現在の状態に応じて入力処理を実行
		void HandleInput(shared_ptr<Player> player)
		{
			m_State->HandleInput(player);  //状態クラスに処理を委譲
		}

		//現在の状態に応じて更新処理を実行
		void PlayerUpdate(shared_ptr<Player> player)
		{
			m_State->PlayerUpdate(player);  //状態クラスに処理を委譲
		}

		enum KeyState
		{
			keyPush = 0,
			keyPressed,
			keyUp,
		};

		bool InputKey(int keyState ,int keyCord)
		{
			switch (keyState)
			{
			case 1:

				return m_KeyState.m_bPressedKeyTbl[keyCord];

				break;

			case 2:

				return m_KeyState.m_bUpKeyTbl[keyCord];

				break;

			default:

				return m_KeyState.m_bPushKeyTbl[keyCord];

				break;
			}
		}

		Vec3 GetPlayerPos()
		{
			return m_Pos;
		}
		void SetPlayerPos(Vec3 pos)
		{
			m_Pos = pos;
		}

		float GetWalkSpeed()
		{
			return m_WalkSpeed;
		}

		Vec3 GetJumpPower()
		{
			return m_JumpPower;
		}
		void PlayerJump(Vec3 velocity)
		{
			m_Grav->Jump(velocity);
		}
		float GetVerticalVelocity()
		{
			return m_Grav->GetVelocity().y;
		}
		const float m_PlayerNormalGravity = -9.8f;

		bool GetIsBombCreate()
		{
			return  m_IsBombCreate;
		}
		void SetIsBombCreate(bool b)
		{
			m_IsBombCreate = b;
		}

		Vec3 GetBombVec()
		{
			return m_BombVec;
		}
		void SetBombVec(Vec3 vec)
		{
			m_BombVec = vec;
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void DrawString();
	};

	//立ち止まり状態
	class PlayerStateIdle : public PlayerState
	{
	public:
		//立ち状態での入力処理
		void HandleInput(shared_ptr<Player> player) override;

		//立ち状態での更新処理
		void PlayerUpdate(shared_ptr<Player> player) override
		{
			player->SetIsBombCreate(false);
		}

		wstring GetStateName() override
		{
			return L"Idle";
		}

		Col4 GetDiffColor() override
		{
			return Col4(0.0f, 0.0f, 1.0f, 1.0f);
		}
	};

	//歩き状態
	class PlayerStateWalk : public PlayerState
	{

		float m_WalkSpeed = 0.0f;
		Vec3 m_Pos;

	public:

		PlayerStateWalk(float walkSpeed) : m_WalkSpeed(walkSpeed) {}

		//歩き状態での入力処理
		void HandleInput(shared_ptr<Player> player) override;

		//歩き状態での更新処理
		void PlayerUpdate(shared_ptr<Player> player) override
		{
			player->SetIsBombCreate(false);

			m_Pos = player->GetPlayerPos();
			m_Pos.x += m_WalkSpeed;
			player->SetPlayerPos(m_Pos);
		}

		wstring GetStateName() override
		{
			return L"Walk";
		}

		Col4 GetDiffColor() override
		{
			return Col4(1.0f, 0.0f, 0.0f, 1.0f);
		}
	};

	//投げている状態
	class PlayerStateThrow : public PlayerState
	{
		shared_ptr<basecross::Stage> m_Stage;

	public:
		//投げ状態での入力処理
		void HandleInput(shared_ptr<Player> player) override
		{

		}

		//投げ状態での更新処理
		void PlayerUpdate(shared_ptr<Player> player) override;


		wstring GetStateName() override
		{
			return L"Throw";
		}

		Col4 GetDiffColor() override
		{
			return Col4(0.0f, 1.0f, 1.0f, 1.0f);
		}


	};
}
//end basecross

