/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class TitleStage : public Stage {
	public:
		TitleStage(){}
		virtual ~TitleStage(){}
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateResource();

		virtual void OnCreate()override;

		virtual void OnUpdate()override;

	};
}
//end basecross
