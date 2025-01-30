/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class GameScene : public Scene{
		vector<wstring> m_StageFileNames;
		vector<bool> m_IsStageClear;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
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
		@brief �f�X�g���N�^
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
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;
	};

}

//end basecross
