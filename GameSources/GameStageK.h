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
	class GameStageK : public Stage {
		void CreateResource();
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameStageK() :Stage() {}
		virtual ~GameStageK() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};


}
//end basecross

