/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Fade;
	class Sprite;

	const static int MAX_STAGE = 6;
	const static int MAX_TUTORIAL = 6;

	class SelectStage : public Stage {
		int m_Select;
		float m_IsCanNextSelect;
		shared_ptr<Fade> m_Fade;
		wstring gameMode;

		shared_ptr<Sprite> m_Tab;
	public:
		SelectStage(const wstring& mode) : m_Select(0),m_IsCanNextSelect(1.0f),gameMode(mode){}
		virtual ~SelectStage() {}
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateResource();

		void CreateFade(int select);
		virtual void OnCreate()override;

		virtual void OnUpdate()override;
		virtual void OnDestroy()override;
	};

	
}
//end basecross
