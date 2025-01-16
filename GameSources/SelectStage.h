/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "Button.h"

namespace basecross {
	class Fade;
	class BCSprite;
	class SelectStage : public Stage {
		const int MAX_STAGE;
		int m_Select;
		float m_IsCanNextSelect;
		shared_ptr<Fade> m_Fade;
	public:
		SelectStage() : m_Select(0),m_IsCanNextSelect(1.0f),MAX_STAGE(3){}
		virtual ~SelectStage() {}
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateResource();

		virtual void OnCreate()override;

		virtual void OnUpdate()override;
		virtual void OnDestroy()override;
	};

	class SelectButton : public Button {
	public:
		int m_Difficulty;
		shared_ptr<BCSprite> m_BackGroundSprite;
		SelectButton(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec2 size,int difficulty) :
			Button(ptr,texKey,pos,size),m_Difficulty(difficulty)
		{}
		virtual ~SelectButton() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
