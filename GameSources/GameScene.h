/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class GameScene : public Scene{
		vector<wstring> m_StageFileNames;
		vector<bool> m_IsStageClear;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		GameScene() :Scene(){
			m_StageFileNames = {
				L"Tutorial01.csv",
				L"Tutorial02.csv",
				L"Tutorial03.csv",
				L"Tutorial04.csv",
				L"Tutorial05.csv",
				L"Tutorial06.csv",
				L"Tutorial07.csv"
			};
			for (int i = 0; i < m_StageFileNames.size(); i++) {
				m_IsStageClear.push_back(false);
			}
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GameScene();

		bool IsClear(int index) {
			return m_IsStageClear[index];
		}
		void Clear(int index) {
			m_IsStageClear[index] = true;
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
