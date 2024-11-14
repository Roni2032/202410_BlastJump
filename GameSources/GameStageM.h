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
	class GameStageM : public GameStage {
		float timer;
		//ビューの作成
		void CreateResource();
		void CreateViewLight();
	public:
		//構築と破棄
		GameStageM() :GameStage(L"Stage03.csv") {}
		virtual ~GameStageM() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

