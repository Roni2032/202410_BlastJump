/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStageM : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateResource();
		int m_A;
	public:
		//構築と破棄
		GameStageM(int a) :Stage(),m_A(a) {}
		virtual ~GameStageM() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

