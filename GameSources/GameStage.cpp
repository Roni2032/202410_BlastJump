/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -30.0f);
		const Vec3 at(0.0f,10.0f,0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UITex/";
		wstring mapPath = path + L"Maps/";
		wstring texPath = path + L"Texture/";
		app->RegisterTexture(L"TEST_TEX", texPath + L"TestTex_wall.jpg");
		m_CsvMap.SetFileName(mapPath + m_MapName);
		m_CsvMap.ReadCsv();
	}
	void GameStage::CreateMap() {
		
		auto& mapVec = m_CsvMap.GetCsvVec();
		vector<wstring> cells;
		Vec2 startPos;
		
		for (int y = 1; y < mapVec.size(); y++) {
			cells.clear();
			vector<int> cow;
			Util::WStrToTokenVector(cells, mapVec[y], L',');
			startPos = Vec2(static_cast<float>(cells.size()) / -2.0f, mapVec.size());
			
			for (int x = 0; x < cells.size(); x++) {
				int cell = stoi(cells[x]);
				switch (cell) {
				case 1:
					AddGameObject<FloorBlock>(L"",Vec3(startPos.x + x, startPos.y - y, 0));
					break;
				}
				cow.push_back(cell);
			}
			m_Map.push_back(cow);
		}
		Vec2 mapSize = Vec2(cells.size(), mapVec.size());
		cells.clear();
		Util::WStrToTokenVector(cells, mapVec[0], L',');
		
		Vec2 center = Vec2(0.0f, mapSize.y / 2.0f);
		//��
		AddGameObject<Block>(cells[0], Vec3(center.x - 0.5f, startPos.y + 1, 0), Vec3(mapSize.x + 2, 1, 1));
		//��
		AddGameObject<Block>(cells[0], Vec3(center.x - 0.5f, startPos.y - mapSize.y, 0), Vec3(mapSize.x + 2, 1, 1));
		//�E
		AddGameObject<Block>(cells[0], Vec3(startPos.x + mapSize.x, center.y + 0.5f, 0), Vec3(1, mapSize.y, 1));
		//��
		AddGameObject<Block>(cells[0], Vec3(startPos.x - 1, center.y + 0.5f, 0), Vec3(1, mapSize.y, 1));
	}
	void GameStage::OnCreate() {
		try {
			CreateViewLight();
			CreateResource();
			CreateMap();

			AddGameObject<Bomb>(Vec3(-3, 10, 0), 2.0f, 1.0f);
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
