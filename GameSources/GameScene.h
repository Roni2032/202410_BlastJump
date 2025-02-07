/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	struct StageData {
		wstring m_FileName;
		bool m_IsClear;
		int m_BombNum;
		float m_ScrollSpeed;

		StageData(const wstring& name,int bomb,float speed) : m_FileName(name),m_IsClear(false),m_BombNum(bomb),m_ScrollSpeed(speed){}
	};
	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class GameScene : public Scene{
		vector<StageData> m_StageData;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		GameScene() :Scene(){
			m_StageData = {
				StageData(L"Tutorial01.csv",20,0.0f),
				StageData(L"Tutorial02.csv",25,0.25f),
				StageData(L"Tutorial03.csv",20,0.25f),
				StageData(L"Tutorial04.csv",20,0.25f),
				StageData(L"Tutorial05.csv",99,0.25f),
				StageData(L"Tutorial06.csv",99,0.25f),

				StageData(L"Stage01.csv",20,0.25f),
				StageData(L"Stage02.csv",20,0.25f),
				StageData(L"Stage03.csv",20,0.25f),
				StageData(L"Stage04.csv",20,0.25f),
				StageData(L"Tutorial05.csv",99,0.25f),
				StageData(L"Stage06.csv",10,0.25f),
			};
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GameScene();
		bool IsNextStage(int currentIndex) {
			if (currentIndex + 1 >= m_StageData.size()) {
				return false;
			}
			return true;
		}
		bool IsClear(int index) {
			return m_StageData[index].m_IsClear;
		}
		void Clear(int index) {
			m_StageData[index].m_IsClear = true;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;
	};

}

//end basecross
