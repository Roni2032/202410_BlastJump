/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "BCSprite.h"
#include "Blocks.h"

#include "Player.h"

namespace basecross {
	class BlockData;
	struct BetWeen {
		float m_High;
		float m_Low;
		BetWeen(float high,float low):m_High(high),m_Low(low){}
	};

	
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage{
	public:
		enum GameMode {
			View,
			NotBomb,
			InGame,
			Menu,
			Clear,
			Over
		};
	private:
		shared_ptr<InstanceBlock> m_Walls;
		shared_ptr<GameObject> m_Goal;
		shared_ptr<GameObject> m_MenuBackGround;
		int m_LoadedMaxHeight = 0;
		float m_CameraAtY = 0;
		vector<vector<BlockData>> m_MapData;
		Vec3 m_MapLeftTop;
		Vec3 m_MapRightBottom;

		wstring m_MapName;
		CsvFile m_CsvMap;

		int m_BombNum;
		GameMode m_Mode;
		GameMode m_BeforeMode;

		int m_StageNumber;
		shared_ptr<int> m_SendStageNumber;

		shared_ptr<BCNumber> m_PlayerHasBombs;


		int m_MenuSelect;
		

		Vec3 m_RespawnPosition;
		Vec3 m_LoadStageSize;
		//ビューの作成
		void CreateViewLight();
		void CreateResource();
		void CreateMap();
		void CreateParticle();
		void LoadMap();
		void BlockUpdateActive();
	public:
		//構築と破棄
		GameStage(const wstring& mapName, const int stageNumber = 0, const int bombNum = 10) :Stage(), m_MapName(mapName),
			m_LoadStageSize(Vec3(20,48,0)),
			m_BombNum(bombNum),
			m_StageNumber(stageNumber),
			m_MenuSelect(0),
			m_Mode(GameMode::View),m_BeforeMode(GameMode::View)
		{}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;
		void RegisterBlock(Vec2 mapIndex, const shared_ptr<GameObject>& obj);
		shared_ptr<GameObject> CreateBlock(Vec2 mapIndex, Vec3 pos);

		shared_ptr<Player> m_Player;

		template<typename particleType>
		void PlayParticle(const wstring& key, Vec3 pos) const{
			auto particle = GetSharedGameObject<particleType>(key, false);
			if (particle != nullptr) {
				particle->Shot(pos);
			}
		}
		vector<vector<BlockData>>& GetMap() {
			return m_MapData;
		}

		float GetBottomY() {
			return -0.5f;
		}
		float GetTopY() {
			return m_MapLeftTop.y;
		}
		Vec3 GetLeftTop() {
			return m_MapLeftTop;
		}
		Vec3 GetRightBottom() {
			return m_MapRightBottom;
		}
		Vec2 GetMapSize() {
			return Vec2(m_MapData[0].size(), m_MapData.size());
		}
		Vec3 GetMapIndex(Vec3 pos);
		Vec3 GetWorldPosition(Vec2 pos);
		shared_ptr<GameObject> GetBlock(Vec3 pos);
		int GetBlockId(Vec3 pos);
		int GetBlockId(Vec2 index);

		void DestroyBlock(Vec3 pos, shared_ptr<GameObject>& block);

		void NewRespawnPosition(Vec3 pos) {
			m_RespawnPosition = pos;
		}
		Vec3 GetRespawnPosition() {
			return m_RespawnPosition;
		}
		shared_ptr<int> GetStageNumPtr() {
			return m_SendStageNumber;
		}
		GameMode GetGameMode() {
			return m_Mode;
		}
		void GameClear();
		void GameOver();

		void ChangeMode(GameMode mode) {
			m_BeforeMode = m_Mode;
			m_Mode = mode;
		}
		GameMode GetBeforeMode() {
			return m_BeforeMode;
		}
		void GameStart() {
			ChangeMode(GameMode::NotBomb);
		}
		bool IsInGame() {
			return m_Mode == GameMode::InGame || m_Mode == GameMode::NotBomb;
		}
		bool IsFinishGame() {
			return m_Mode == GameMode::Clear || m_Mode == GameMode::Over;
		}
		bool IsView() {
			return m_Mode == GameMode::View;
		}
		bool IsOpenMenu() {
			return m_Mode == GameMode::Menu;
		}
		bool IsCanMovePlayer() {
			return !IsView() && !IsOpenMenu();
		}
		void OpenMenu();
		void CloseMenu();
	};


}
//end basecross

