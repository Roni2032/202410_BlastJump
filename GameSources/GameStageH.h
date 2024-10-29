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
	class GameStageH : public GameStage {
		vector<vector<int>> m_Map;
		wstring m_MapName;
		CsvFile m_CsvMap;

		//ビューの作成
		void CreateViewLight();
		void CreateResource();
		void CreateMap();
		void CreateEnemy();
	public:
		//構築と破棄
		GameStageH(const wstring& mapName) : GameStage(L"TestMap.csv"), m_MapName(mapName) {}
		virtual ~GameStageH() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross

