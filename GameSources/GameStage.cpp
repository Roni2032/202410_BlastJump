/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class Block;
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 6.0f, -15.0f);
		const Vec3 at(0.0f,6.0f,0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			CreateViewLight();
			CreateResource();
			CreateMap();

			auto bomb = AddGameObject<Bomb>(Vec3(-3, 2, 0),Vec3(1.0f,10.0f,0.0f), 1.0f );

			auto explodeParticle = AddGameObject<ExplodeParticle>(bomb->GetComponent<Transform>());
			SetSharedGameObject(L"EXPLODE_PCL", explodeParticle);

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UITex/";
		wstring mapPath = path + L"Maps/";
		wstring texPath = path + L"Texture/";
		app->RegisterTexture(L"TEST_TEX", texPath + L"TestTex_wall.jpg");
		app->RegisterTexture(L"EXPLODE1_TEX", texPath + L"explodeParticle1.png");
		app->RegisterTexture(L"EXPLODE2_TEX", texPath + L"explodeParticle2.png");

		m_CsvMap.SetFileName(mapPath + m_MapName);
		m_CsvMap.ReadCsv();
	}
	void GameStage::CreateMap() {
		
		auto& mapVec = m_CsvMap.GetCsvVec();
		GetStageInfo(mapVec[0]);
		auto walls = AddGameObject<InstanceBlock>(L"TEST_TEX", mapVec.size() - 1);
		vector<wstring> cells;
		Vec2 startPos;
		
		for (int y = 0; y < mapVec.size() - 1; y++) {
			cells.clear();
			vector<int> cow;
			Util::WStrToTokenVector(cells, mapVec[y + 1], L',');
			startPos = Vec2(static_cast<float>(cells.size()) / -2.0f, mapVec.size() - 2);
			if (y == 0) {
				m_MapLeftTop = startPos;
			}
			for (int x = 0; x < cells.size(); x++) {
				int cell = stoi(cells[x]);
				switch (cell) {
				case 1:
					AddGameObject<FloorBlock>(L"TEST_TEX",Vec3(startPos.x + x, startPos.y - y, 0));
					break;
				}
				if (cell == 2) {
					walls->AddBlock(y, cell);
				}
				else {
					walls->AddBlock(y, 0);
				}
				cow.push_back(cell);
			}
			m_Map.push_back(cow);
		}
		walls->SetStartPos(startPos);
		walls->DrawMap();
		Vec2 mapSize = Vec2(cells.size(), mapVec.size() - 1);
		CreateWallCollider(startPos, mapSize);
		

		
		/*cells.clear();
		Util::WStrToTokenVector(cells, mapVec[1], L',');

		int index = 0;
		while (true) {
			vector<wstring> strNum;
			wstring key = cells[index];
			index++;

			if (key == L"null") {
				break;
			}
			else if (key == L"scroll") {
				Util::WStrToTokenVector(strNum, cells[index], L'-');
				if (strNum.size() == 2) {
					m_scrollRange.push_back(BetWeen(stoi(strNum[0]), stoi(strNum[1])));
				}
				else {
					m_scrollRange.push_back(BetWeen(stoi(strNum[0]), 1000));
				}
			}
			else if (key == L"bomb") {
				m_BombNum = stoi(cells[index]);
			}
		}*/
	}

	void GameStage::CreateWallCollider(Vec2 startPos, Vec2 mapSize) {

		Vec2 center = Vec2(0.0f, mapSize.y / 2.0f);
		//上
		AddGameObject<Block>(L"", Vec3(center.x - 0.5f, startPos.y, 0), Vec3(mapSize.x, 1, 1));
		//下
		AddGameObject<Block>(L"", Vec3(center.x - 0.5f, startPos.y - mapSize.y + 1, 0), Vec3(mapSize.x, 1, 1));
		//右
		AddGameObject<Block>(L"", Vec3(startPos.x + mapSize.x - 1, center.y + 0.5f, 0), Vec3(1, mapSize.y - 2, 1));
		//左
		AddGameObject<Block>(L"", Vec3(startPos.x, center.y + 0.5f, 0), Vec3(1, mapSize.y - 2, 1));
	}
	
	void GameStage::GetStageInfo(const wstring& strVec) {
		vector<wstring> cells;
		Util::WStrToTokenVector(cells, strVec, L',');

		int index = 0;
		while (true) {
			vector<wstring> strNum;
			wstring key = cells[index];
			index++;
			if (index >= cells.size()) {
				break;
			}

			if (key == L"null") {
				break;
			}
			if (!all_of(cells[index].cbegin(), cells[index].cend(), isdigit)) {
				continue;
			}
			if (key == L"scroll") {
				Util::WStrToTokenVector(strNum, cells[index], L'-');
				if (strNum.size() == 2) {
					m_scrollRange.push_back(BetWeen(stoi(strNum[0]), stoi(strNum[1])));
				}
				else {
					m_scrollRange.push_back(BetWeen(stoi(strNum[0]), 1000));
				}
			}
			else if (key == L"bomb") {
				m_BombNum = stoi(cells[index]);
			}
		}
	}


	Vec3 GameStage::GetMapIndex(Vec3 pos) {
		Vec3 mapPos = Vec3(pos.x - m_MapLeftTop.x, m_MapLeftTop.y - pos.y, 0);
		return mapPos.floor(0);
	}
	int GameStage::GetBlock(Vec3 pos) {
		Vec3 mapPos = GetMapIndex(pos);
		
		return m_Map[mapPos.y][mapPos.x];
	}

	void GameStage::DestroyBlock(Vec3 pos,shared_ptr<GameObject>& block) {
		Vec3 mapPos = GetMapIndex(pos);
		m_Map[mapPos.y][mapPos.x] = 0;

		RemoveGameObject<GameObject>(block);
	}
}
//end basecross
