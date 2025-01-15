/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Fade;
	class TitleStage : public Stage {
		shared_ptr<Fade> m_Fade;
	public:
		TitleStage(){}
		virtual ~TitleStage(){}
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateResource();

		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy()override;
	};
}
//end basecross
