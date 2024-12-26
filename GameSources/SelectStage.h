/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Fade;
	class SelectStage : public Stage {
		const int MAX_STAGE;
		int m_Select;
		float m_IsCanNextSelect;
		shared_ptr<Fade> m_Fade;
	public:
		SelectStage() : m_Select(0),m_IsCanNextSelect(1.0f),MAX_STAGE(3){}
		virtual ~SelectStage() {}
		//ビューの作成
		void CreateViewLight();
		void CreateResource();

		virtual void OnCreate()override;

		virtual void OnUpdate()override;
		virtual void OnDestroy()override;
	};
}
//end basecross
