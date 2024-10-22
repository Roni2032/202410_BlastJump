/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStageH : public Stage {
		vector<vector<int>> m_Map;
		wstring m_MapName;
		CsvFile m_CsvMap;

		//�r���[�̍쐬
		void CreateViewLight();
		void CreateResource();
		void CreateMap();
		void CreateEnemy();
	public:
		//�\�z�Ɣj��
		GameStageH(const wstring& mapName) : Stage(),m_MapName(mapName) {}
		virtual ~GameStageH() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross

