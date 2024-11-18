/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class TitleStage : public Stage {
	public:
		TitleStage(){}
		virtual ~TitleStage(){}
		//ビューの作成
		void CreateViewLight();
		void CreateResource();

		virtual void OnCreate()override;

		virtual void OnUpdate()override;

	};
}
//end basecross
