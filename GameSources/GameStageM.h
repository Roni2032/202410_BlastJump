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
	class GameStageM : public GameStage {
		//�r���[�̍쐬
		void CreateResource();
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStageM() :GameStage(L"Stage01.csv") {}
		virtual ~GameStageM() {}
		//������
		virtual void OnCreate()override;

	};


}
//end basecross

