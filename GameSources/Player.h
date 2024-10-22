/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

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

		shared_ptr<basecross::Transform> m_Transform;
		Vec3 m_Pos = Vec3(0.0f);
		shared_ptr<basecross::BcPNTStaticDraw> m_Draw;
		Col4 m_ColBlack = Col4(0.0f, 0.0f, 0.0f, 1.0f);
		Col4 m_TestCol = Col4(0.0f, 0.0f, 0.0f, 1.0f);

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

		Vec3 GetPlayerPos()
		{
			return m_Pos;
		}
		void SetPlayerPos(Vec3 pos)
		{
			m_Pos = pos;
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void DrawString();
	};

	//�����~�܂���
	class PlayerStateIdle : public PlayerState
	{
	public:
		//������Ԃł̓��͏���
		void HandleInput(shared_ptr<Player> player) override
		{

		}

		//������Ԃł̍X�V����
		void PlayerUpdate(shared_ptr<Player> player) override
		{

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

	public:

		PlayerStateWalk(float walkSpeed) : m_WalkSpeed(walkSpeed) {}

		//������Ԃł̓��͏���
		void HandleInput(shared_ptr<Player> player) override
		{

		}

		//������Ԃł̍X�V����
		void PlayerUpdate(shared_ptr<Player> player) override
		{
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

	//�����Ă�����
	class PlayerStateThrow : public PlayerState
	{

		shared_ptr<basecross::Stage> m_Stage;
		bool m_IsCreate = false;

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

