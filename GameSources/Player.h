/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "BCGravity.h"

namespace basecross {

	//�O���錾(�e���)
	class Player;
	class PlayerStateIdle;
	class PlayerStateWalk;
	class PlayerStateThrow;

	//�C���^�[�t�F�C�X�F���ۊ��N���X
	class PlayerState
	{
	public:
		virtual ~PlayerState() = default;

		//���[�U�[���͂��������鉼�z�֐�
		virtual void HandleInput(shared_ptr<Player>) = 0;

		//�t���[�����Ƃ̍X�V�������s�����z�֐�
		virtual void PlayerUpdate(shared_ptr<Player>) = 0;

		virtual wstring GetStateName() = 0;

		virtual Col4 GetDiffColor() = 0;
	};

	//�R���e�L�X�g�N���X
	class Player : public GameObject
	{
		//���݂̏�Ԃ�ێ�����X�}�[�g�|�C���^
		shared_ptr<PlayerState> m_State;

		KEYBOARD_STATE m_KeyState;
		vector <basecross::CONTROLER_STATE> m_Controler;

		shared_ptr<basecross::Transform> m_Transform;
		Vec3 m_Pos = Vec3(0.0f);
		shared_ptr<basecross::BcPNTStaticDraw> m_Draw;
		Col4 m_ColBlack = Col4(0.0f, 0.0f, 0.0f, 1.0f);
		Col4 m_TestCol = Col4(0.0f, 0.0f, 0.0f, 1.0f);

		shared_ptr<basecross::CollisionCapsule> m_Collision;

		shared_ptr<BCGravity> m_Velo;

		float m_WalkSpeed = 2.0f;

		Vec3 m_JumpPower = Vec3(0.0f, 5.0f, 0.0f);
		bool m_IsJumping = false;

		bool m_IsBombCreate = false;
		float m_ThrowCoolTime = 0.0f;
		float m_BombShotSpeed = 10.0f;
		Vec3 m_BombVec = Vec3(0.0f);
		uint8_t m_HasBomb = 0;

		bool m_IsDead = false;
		bool m_IsDeadInit = false;

	public:
		// �R���X�g���N�^�F������Ԃ��󂯎��ݒ肷��
		explicit Player(const shared_ptr<Stage>& ptr, shared_ptr<PlayerState> initialState)
			: GameObject(ptr), m_State(move(initialState)) {}

		// ��Ԃ�؂�ւ��邽�߂̃��\�b�h
		void SetState(shared_ptr<PlayerState> newState)
		{
			m_State = move(newState);  //�V������Ԃ�K�p
		}

		//���݂̏�Ԃɉ����ē��͏��������s
		void HandleInput(shared_ptr<Player> player)
		{
			m_State->HandleInput(player);  //��ԃN���X�ɏ������Ϗ�
		}

		//���݂̏�Ԃɉ����čX�V���������s
		void PlayerUpdate(shared_ptr<Player> player)
		{
			m_State->PlayerUpdate(player);  //��ԃN���X�ɏ������Ϗ�
		}

		enum KeyState
		{
			keyPush = 0,
			keyPressed,
			keyUp,
		};

		enum ButtonState
		{
			b_Push = 0,
			b_Pressed,
			b_Up,
		};

		bool InputKey(int keyState, int keyCord)
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

		bool InputButton(int useControler, int buttonState, int button)
		{
			if (m_Controler[useControler].bConnected)
			{
				switch (buttonState)
				{
				case 1:

					return m_Controler[useControler].wPressedButtons & button;

					break;

				case 2:

					return m_Controler[useControler].wReleasedButtons & button;

					break;

				default:

					return m_Controler[useControler].wButtons & button;

					break;
				}
			}
		}

		Vec3 GetPlayerPos() { return m_Pos; }
		void SetPlayerPos(Vec3 pos) { m_Pos = pos; }

		float GetWalkSpeed() { return m_WalkSpeed; }

		Vec3 GetJumpPower() { return m_JumpPower; }
		void PlayerJump(Vec3 velocity) { m_Velo->Jump(velocity); }
		float GetVerticalVelocity() { return m_Velo->GetVelocity().y; }
		const float m_PlayerNormalGravity = -9.8f;

		bool GetIsJumping() { return m_IsJumping; }
		void SetIsJumping(bool b) { m_IsJumping = b; }

		bool GetIsBombCreate() { return  m_IsBombCreate; }
		void SetIsBombCreate(bool b) { m_IsBombCreate = b; }

		float GetThrowCoolTime() { return m_ThrowCoolTime; }
		void SetThrowCoolTime(float f) { m_ThrowCoolTime = f; }

		float GetBombShotSpeed() { return m_BombShotSpeed; }
		void SetBombShotSpeed(float f) { m_BombShotSpeed = f; }

		Vec3 GetBombVec() { return m_BombVec; }
		void SetBombVec(Vec3 vec) { m_BombVec = vec; }

		uint8_t GetHasBomb() { return m_HasBomb; }
		void SetHasBomb(uint8_t n) { m_HasBomb = n; }
		void AddHasBomb() { m_HasBomb++; }
		void SubtractHasBomb() { m_HasBomb--; }
		void AddHasBombV2(uint8_t n) { m_HasBomb += n; }

		Vec3 m_cameraTest = Vec3(0.0f, 1.0f, 0.0f);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;
		void DrawString();
	};

	//�����~�܂���
	class PlayerStateIdle : public PlayerState
	{
	public:
		//������Ԃł̓��͏���
		void HandleInput(shared_ptr<Player> player) override;

		//������Ԃł̍X�V����
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

	//�������
	class PlayerStateWalk : public PlayerState
	{

		float m_WalkSpeed = 0.0f;
		Vec3 m_Pos;
		float m_DeltaTime = App::GetApp()->GetElapsedTime();

	public:

		PlayerStateWalk(float walkSpeed) : m_WalkSpeed(walkSpeed) {}

		//������Ԃł̓��͏���
		void HandleInput(shared_ptr<Player> player) override;

		//������Ԃł̍X�V����
		void PlayerUpdate(shared_ptr<Player> player) override
		{
			player->SetIsBombCreate(false);

			m_Pos = player->GetPlayerPos();
			m_Pos.x += m_WalkSpeed * m_DeltaTime;
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

	//�����Ă�����
	class PlayerStateThrow : public PlayerState
	{
		shared_ptr<basecross::Stage> m_Stage;

	public:
		//������Ԃł̓��͏���
		void HandleInput(shared_ptr<Player> player) override
		{

		}

		//������Ԃł̍X�V����
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

