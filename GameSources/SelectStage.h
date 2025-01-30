/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Fade;
	class Sprite;

	const static int MAX_STAGE = 6;

	class SelectStage : public Stage {
		int m_Select;
		float m_IsCanNextSelect;
		shared_ptr<Fade> m_Fade;
		wstring gameMode;
	public:
		SelectStage(const wstring& mode) : m_Select(0),m_IsCanNextSelect(1.0f),gameMode(mode){}
		virtual ~SelectStage() {}
		//ビューの作成
		void CreateViewLight();
		void CreateResource();

		void CreateFade(int select);
		virtual void OnCreate()override;

		virtual void OnUpdate()override;
		virtual void OnDestroy()override;
	};

	
}
//end basecross
