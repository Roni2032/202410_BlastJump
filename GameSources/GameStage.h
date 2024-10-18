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
	class GameStage : public Stage {
		vector<vector<int>> m_Map;
		wstring m_MapName;
		CsvFile m_CsvMap;
		//ビューの作成
		void CreateViewLight();
		void CreateResource();
		void CreateMap();

	public:
		//構築と破棄
		GameStage(const wstring& mapName) :Stage(),m_MapName(mapName) {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

