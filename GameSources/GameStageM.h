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
	class GameStageM : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateResource();
		int m_A;
	public:
		//�\�z�Ɣj��
		GameStageM(int a) :Stage(),m_A(a) {}
		virtual ~GameStageM() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

