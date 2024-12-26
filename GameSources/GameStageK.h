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
		float timer;
		//�r���[�̍쐬
		void CreateResource();
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStageK() :GameStage(L"StageK3.csv"), timer(0) {}
		virtual ~GameStageK() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

