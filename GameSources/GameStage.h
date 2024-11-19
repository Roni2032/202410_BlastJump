/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "BCSprite.h"
#include "Blocks.h"

namespace basecross {

	struct BetWeen {
		float m_High;
		float m_Low;
		BetWeen(float high,float low):m_High(high),m_Low(low){}
	};

	
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		vector<shared_ptr<GameObject>> m_LoadedStageObjects;
		int m_LoadedMaxHeight = 0;
		vector<vector<int>> m_Map;
		Vec3 m_MapLeftTop;
		wstring m_MapName;
		CsvFile m_CsvMap;

		int m_BombNum;
		//float m_MainTimer;

		// shared_ptr<BCNumber> m_TimerSprite[2];

		vector<BetWeen> m_scrollRange;
		//ビューの作成
		void CreateViewLight();
		void CreateResource();
		void CreateMap();
		void CreateWallCollider(Vec2 startPos, Vec2 mapSize);
		void GetStageInfo(const wstring& strVec);
		void CreateParticle();
		shared_ptr<Block> CreateBlock(int blockNum, Vec3 pos);
		void LoadMap();
		void CreateEnemy();
	public:
		//構築と破棄
		GameStage(const wstring& mapName) :Stage(),m_MapName(mapName) {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void PlayParticle(const wstring& key, Vec3 pos);
		vector<vector<int>> GetMap() {
			return m_Map;
		}

		Vec3 GetMapIndex(Vec3 pos);
		int GetBlock(Vec3 pos);
		void DestroyBlock(Vec3 pos, shared_ptr<GameObject>& block);

	};


}
//end basecross

