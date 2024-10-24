/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	struct BetWeen {
		float m_High;
		float m_Low;
		BetWeen(float high,float low):m_High(high),m_Low(low){}
	};

	
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		vector<vector<int>> m_Map;
		Vec3 m_MapLeftTop;
		wstring m_MapName;
		CsvFile m_CsvMap;

		int m_BombNum;
		float m_MainTimer;

		vector<BetWeen> m_scrollRange;
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateResource();
		void CreateMap();
		void CreateWallCollider(Vec2 startPos, Vec2 mapSize);
		void GetStageInfo(const wstring& strVec);
	public:
		//�\�z�Ɣj��
		GameStage(const wstring& mapName) :Stage(),m_MapName(mapName) {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;

		vector<vector<int>> GetMap() {
			return m_Map;
		}

		Vec3 GetMapIndex(Vec3 pos);
		int GetBlock(Vec3 pos);
		void DestroyBlock(Vec3 pos, shared_ptr<GameObject>& block);

	};


}
//end basecross

