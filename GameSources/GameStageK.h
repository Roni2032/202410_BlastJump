/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStageK : public GameStage {
		void CreateResource();
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStageK() :GameStage(L"Stage01.csv") {}
		virtual ~GameStageK() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};


}
//end basecross

