/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Fade;
	class TitleStage : public Stage {
		shared_ptr<Fade> m_Fade;
		wstring m_SelectMode;
	public:
		TitleStage() : m_SelectMode(L"") {}
		virtual ~TitleStage(){}
		//ビューの作成
		void CreateViewLight();
		void CreateResource();

		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy()override;
	};
}
//end basecross
