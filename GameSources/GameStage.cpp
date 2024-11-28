/*!
@file GameStage.cpp
@brief ・ｽQ・ｽ[・ｽ・ｽ・ｽX・ｽe・ｽ[・ｽW・ｽ・ｽ・ｽ・ｽ
*/

#include "stdafx.h"
#include "Project.h"
//m_MapDataを使ってデータ保存するように変更する

namespace basecross {
	class Block;
	//--------------------------------------------------------------------------------------
	//	・ｽQ・ｽ[・ｽ・ｽ・ｽX・ｽe・ｺﾛ・ｽW・ｽN・ｽ・ｽ・ｽX・ｽ・ｽ・ｽ・ｽ
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(-0.5f, 4.0f, -34.0f);
		const Vec3 at(-0.5f,4.0f,0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>(GetThis<GameStage>(), 0.0f);
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		auto PtrMultiLight = CreateLight<MultiLight>();
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			CreateViewLight();

			SoundManager::Instance().PlayBGM(L"BGM_SD",0.05f);
			Block::CollisionObjects.clear();
			CreateResource();
			m_Player = AddGameObject<Player>(make_shared<PlayerStateIdle>());
			SetSharedGameObject(L"Player", m_Player);
			CreateMap();
			CreateParticle();
			LoadMap();			

			//AddGameObject<BombThrowArrow>(m_Player);
			AddGameObject<BombThrowOrbit>(m_Player,30);
			
			auto camera = static_pointer_cast<MyCamera>(GetView()->GetTargetCamera());
			camera->SetPlayer(m_Player);
			float screenHight = camera->GetHeight();
			//camera->SetStageAt(m_MapLeftTop.y - screenHight / 2.0f - 1);

			//auto bomb = AddGameObject<Bomb>(Vec3(-5, 4, 0),Vec3(1.0f,8.0f,0.0f), 3.0f );

			//m_TimerSprite[0] = AddGameObject<BCNumber>(L"NUMBER_TEX", Vec3(-400.0f, 550.0f, 0.0f), Vec2(200, 400), 2);
			//m_TimerSprite[1] = AddGameObject<BCNumber>(L"NUMBER_TEX", Vec3(-650.0f, 550.0f, 0.0f), Vec2(200, 400), 2);

			AddGameObject<BCSprite>(L"BOMBNUM_UI", Vec3(-630.0f, -240.0f, 0), Vec2(200, 150));
			m_PlayerHasBombs =  AddGameObject<BCNumber>(L"NUMBER_TEX", Vec3(-520.0f, -220.0f, 0), Vec2(80, 250), 2);
			m_PlayerHasBombs->UpdateNumber(m_Player->GetHasBomb());

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_MainTimer += elapsedTime;
		int minute = static_cast<int>(m_MainTimer / 60.0f);
		int second = static_cast<int>(m_MainTimer - 60.0f * minute);

		//m_TimerSprite[1]->UpdateNumber(minute);
		//m_TimerSprite[0]->UpdateNumber(second);
		if (m_Mode != GameMode::View) {
			LoadMap();

			BlockUpdateActive();

			m_PlayerHasBombs->UpdateNumber(m_Player->GetHasBomb());
		}
		else {
			m_PlayerHasBombs->SetDrawActive(false);
			
		}

		if (m_Mode != GameMode::InGame) {

			auto pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (pad.bConnected) {
				if (pad.wPressedButtons == XINPUT_GAMEPAD_Y) {
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				}
			}
		}
	}
	void GameStage::OnDestroy() {
		SoundManager::Instance().StopBGM();
	}
	void GameStage::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UITex/";
		wstring mapPath = path + L"Maps/";
		wstring texPath = path + L"Texture/";
		wstring modelPath = path + L"Models/";
		app->RegisterTexture(L"TEST_TEX", texPath + L"TestTex_wall.jpg");
		app->RegisterTexture(L"TEST100_TEX", texPath + L"TestTex_wall100.png");
		app->RegisterTexture(L"TEST66_TEX", texPath + L"TestTex_wall66.png");
		app->RegisterTexture(L"TEST33_TEX", texPath + L"TestTex_wall33.png");
		app->RegisterTexture(L"EXPLODE1_TEX", texPath + L"explodeParticle_2.png");
		app->RegisterTexture(L"EXPLODE_SPARK_TEX", texPath + L"explodeSpark.png");
		app->RegisterTexture(L"BOMB_THROW_TEX", texPath + L"arrow.png");
		app->RegisterTexture(L"BOMB_ITEM_TEX", texPath + L"BombItem.png");

		app->RegisterTexture(L"GOALCLEAR_TEX", uiPath + L"GameClearTest1.png");
		app->RegisterTexture(L"NUMBER_TEX", uiPath + L"TimerNum.png");
		app->RegisterTexture(L"GAMEOVER_TEX", uiPath + L"GameOverText1.png");
		app->RegisterTexture(L"BACKGROUND_TEX", texPath + L"BackGround.png");
		app->RegisterTexture(L"PUSHY_TEX", uiPath + L"PushYText1.png");
		app->RegisterTexture(L"BOMBNUM_UI", uiPath + L"BombNumUI.png");


		m_CsvMap.SetFileName(mapPath + m_MapName);
		m_CsvMap.ReadCsv();
	}
	void GameStage::CreateMap() {
		
		auto& mapVec = m_CsvMap.GetCsvVec();
		GetStageInfo(mapVec[0]);
		m_Walls = AddGameObject<InstanceBlock>(L"TEST_TEX", mapVec.size() - 1);
		vector<wstring> cells;
		Vec2 startPos;
		
		for (int y = 0; y < mapVec.size() - 1; y++) {
			m_MapData.push_back({});
			cells.clear();
			//vector<int> cow;
			Util::WStrToTokenVector(cells, mapVec[y + 1], L',');
			startPos = Vec2(static_cast<float>(cells.size()) / -2.0f, mapVec.size() - 2);
			if (y == 0) {
				m_MapLeftTop = startPos + Vec3(0.0f,-0.5f,0);
			}
			for (int x = 0; x < cells.size(); x++) {
				int cell = stoi(cells[x]);
				
				if (cell == 2) {
					m_Walls->AddBlock(y, cell);
				}
				else {
					m_Walls->AddBlock(y, 0);
				}
				m_MapData[y].push_back(BlockData(cell));
				//cow.push_back(cell);
			}
			//m_Map.push_back(cow);
		}
		m_Walls->SetStartPos((Vec2)m_MapLeftTop);
		auto camera = GetView()->GetTargetCamera();
		float atY = camera->GetAt().y;

		Vec2 mapSize = Vec2(cells.size(), mapVec.size() - 1);
		//CreateWallCollider(startPos, mapSize);
		LoadMap();
	}

	void GameStage::RegisterBlock(Vec2 mapIndex, const shared_ptr<GameObject>& obj) {
		if (m_MapData[mapIndex.y][mapIndex.x].GetBlock() == nullptr) {
			m_MapData[mapIndex.y][mapIndex.x].SetGameObject(obj);
		}
	}
	shared_ptr<GameObject> GameStage::CreateBlock(Vec2 mapIndex, Vec3 pos) {
		shared_ptr<GameObject> obj = nullptr;
		switch (m_MapData[mapIndex.y][mapIndex.x].GetID()) {
		case 1:
			obj = AddGameObject<FloorBlock>(L"TEST_TEX", pos,100);
			break;
		/*case 2:
			obj = AddGameObject<Block>(L"", pos, Vec3(1.0f));
			break;*/
		case 3:
			obj = AddGameObject<FloorBlock>(L"TEST_TEX", pos, 50);
			break;
		case 4:
			obj = AddGameObject<FloorBlock>(L"TEST_TEX", pos, 10);
			break;
		case 5:
			obj = AddGameObject<BombItem>(pos,4);
			break;
		case 6:
			obj = AddGameObject<Goal>(pos);
			break;
		case 7:
			obj = AddGameObject<CheckPoint>(pos);
			break;
		case 8:
			obj = AddGameObject<MoveBlock>(L"TEST_TEX", pos, 1.0f, Vec3(2, 0, 0));
			break;
		case 9:
			obj = AddGameObject<MoveBlock>(L"TEST_TEX", pos, 1.0f, Vec3(-2, 0, 0));
			break;
		case 10:
			obj = AddGameObject<MoveBlock>(L"TEST_TEX", pos, 1.0f, Vec3(0, 2, 0));
			break;
		case 11:
			obj = AddGameObject<MoveBlock>(L"TEST_TEX", pos, 1.0f, Vec3(0, -2, 0));
			break;

		}
		
		m_MapData[mapIndex.y][mapIndex.x].SetGameObject(obj);
		
		return obj;
	}
	void GameStage::LoadMap() {
		auto camera = GetView()->GetTargetCamera();
		float atY = camera->GetAt().y;

		

		/*if (m_LoadedMaxHeight == 0) {
			for (int i = 0; i <= atY + m_LoadStageSize.y; i++) {
				if (i >= m_Map.size()) {
					break;
				}
				int y;
				y = m_Map.size() - i - 1;
				int sizeX = m_Map[y].size();
				for (int x = 0; x < sizeX; x++) {
					int size = m_Map[y].size();
					auto obj = CreateBlock(m_Map[y][x], Vec3(m_MapLeftTop.x + x, m_MapLeftTop.y - y, 0));
					if (obj != nullptr) {
						m_LoadedStageObjects.push_back(obj);
					}
				}
			}

			m_LoadedMaxHeight = static_cast<int>(atY + m_LoadStageSize.y);
			m_Walls->DrawMap(Vec2(m_Map[0].size(), atY + m_LoadStageSize.y), Vec2(0, atY - m_LoadStageSize.y));
			return;
		}*/
		//・ｽV・ｽ・ｽ・ｽ・ｽ・ｽ}・ｽb・ｽv・ｽ・ｽ・ｽ・ｽ・ｽ[・ｽh
		//if (m_LoadedMaxHeight < static_cast<int>(atY) + m_LoadStageSize.y) {
		//	m_LoadedMaxHeight = static_cast<int>(atY + m_LoadStageSize.y);
		//	if (m_LoadedMaxHeight >= m_Map.size()) {
		//		return;
		//	}
		//	int loadedIndex = m_Map.size() - 1 - m_LoadedMaxHeight;
		//	for (int x = 0; x < m_Map[loadedIndex].size(); x++) {
		//		int size = m_Map[loadedIndex].size();
		//		Vec2 startPos = Vec2(size / -2 , m_Map.size() - 2);
		//		auto obj = CreateBlock(m_Map[loadedIndex][x], Vec3(startPos.x + x, startPos.y - loadedIndex, 0));//AddGameObject<FloorBlock>(L"TEST_TEX", );
		//		if (obj != nullptr) {
		//			m_LoadedStageObjects.push_back(obj);
		//		}
		//	}
		//}
		////・ｽ・ｽ・ｽ[・ｽh・ｽ・ｽ・ｽﾈゑｿｽ・ｽ鼾・ｿｽﾍゑｿｽ・ｽ・ｽ・ｽﾅ終・ｽ・ｽ
		//else if(m_LoadedMaxHeight == static_cast<int>(atY) + m_LoadStageSize.y){
		//	return;
		//}
		if (m_CameraAtY == 0) {
			m_CameraAtY = atY;
			for (int i = 0; i <= m_CameraAtY + m_LoadStageSize.y; i++) {
				if (i >= m_MapData.size()) {
					break;
				}
				int y = static_cast<int>(m_MapData.size()) - i - 1;
				int sizeX = static_cast<int>(m_MapData[y].size());
				for (int x = 0; x < sizeX; x++) {
					int size = static_cast<int>(m_MapData[y].size());
					auto obj = CreateBlock(Vec2(x,y), Vec3(m_MapLeftTop.x + x, m_MapLeftTop.y - y, 0));
					if (obj != nullptr) {
						m_LoadedStageObjects.push_back(obj);
					}
				}
			}

			m_Walls->DrawMap(Vec2(m_MapData[0].size(), atY + m_LoadStageSize.y), Vec2(0, atY - m_LoadStageSize.y));
			return;
		}
		for (int i = m_CameraAtY + m_LoadStageSize.y + 1; i <= atY + m_LoadStageSize.y; i++) {
			if (i >= m_MapData.size()) return;

			for (int j = 0; j < m_MapData[i].size(); j++) {

				int loadIndexY = static_cast<int>(m_MapData.size()) - i - 1;
				float sizeX = static_cast<float>(m_MapData[i].size());
				Vec2 startPos = Vec2(sizeX / -2, m_MapData.size() - 2);
				auto obj = CreateBlock(Vec2(j,loadIndexY), Vec3(startPos.x + j, startPos.y - loadIndexY, 0));
				if (obj != nullptr) {
					m_LoadedStageObjects.push_back(obj);
				}
			}
		}

		for (int i = m_CameraAtY - m_LoadStageSize.y - 1; i >= atY - m_LoadStageSize.y; i--) {
			if (i < 0) return;

			for (int j = 0; j < m_MapData[i].size(); j++) {

				int loadIndexY = static_cast<int>(m_MapData.size()) - i - 1;
				Vec2 startPos = Vec2(m_MapData[i].size() / -2.0f, m_MapData.size() - 2);
				auto obj = CreateBlock(Vec2(j, loadIndexY), Vec3(startPos.x + j, startPos.y - loadIndexY, 0));//AddGameObject<FloorBlock>(L"TEST_TEX", );
				if (obj != nullptr) {
					m_LoadedStageObjects.push_back(obj);
				}
			}
		}
		m_CameraAtY = atY;
		m_Walls->DrawMap(Vec2(m_MapData[0].size(), m_CameraAtY + m_LoadStageSize.y), Vec2(0, m_CameraAtY - m_LoadStageSize.y));
		//・ｽﾍ囲外・ｽﾉ難ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽu・ｽ・ｽ・ｽb・ｽN・ｽ・ｽ・ｽ尞・
		for (int i = 0; i < m_LoadedStageObjects.size(); i++) {
			auto objTrans = m_LoadedStageObjects[i]->GetComponent<Transform>(false);
			float y = objTrans->GetPosition().y;

			if (y < static_cast<int>(atY) - m_LoadStageSize.y) {
				RemoveGameObject<GameObject>(m_LoadedStageObjects[i]);
				m_LoadedStageObjects.erase(m_LoadedStageObjects.begin() + i);
				
			}
			if (y > static_cast<int>(atY) + m_LoadStageSize.y) {
				RemoveGameObject<GameObject>(m_LoadedStageObjects[i]);
				m_LoadedStageObjects.erase(m_LoadedStageObjects.begin() + i);
			}
		}

		
		
	}
	void GameStage::BlockUpdateActive() {
		for (auto& blockObject : GetGameObjectVec()) {
			if (blockObject->FindTag(L"Stage")) {
				bool isCollider = false;
				for (int i = 0; i < Block::CollisionObjects.size(); i++) {
					auto trans = Block::CollisionObjects[i].lock();
					if (trans != nullptr) {
						
						if (length(trans->GetWorldPosition() - blockObject->GetComponent<Transform>()->GetWorldPosition()) < 3.0f) {
							isCollider = true;
						}
						
					}
					else {
						Block::CollisionObjects.erase(Block::CollisionObjects.begin() + i);
					}
				}
				auto col = blockObject->GetComponent<Collision>(false);
				if (col != nullptr) {
					//col->SetDrawActive(isCollider);
					col->SetUpdateActive(isCollider);
				}
				else {
					blockObject->SetUpdateActive(isCollider);
				}
			}
		}
	}
	void GameStage::CreateWallCollider(Vec2 startPos, Vec2 mapSize) {

		Vec2 center = Vec2(0.0f, mapSize.y / 2.0f);
		//・ｽ・ｽ
		AddGameObject<Block>(L"", Vec3(center.x - 0.5f, startPos.y, 0), Vec3(mapSize.x, 1, 1));
		//・ｽ・ｽ
		AddGameObject<Block>(L"", Vec3(center.x - 0.5f, startPos.y - mapSize.y + 1, 0), Vec3(mapSize.x, 1, 1));
		//・ｽE
		AddGameObject<Block>(L"", Vec3(startPos.x + mapSize.x - 1, center.y - 0.5f, 0), Vec3(1, mapSize.y - 2, 1));
		//・ｽ・ｽ
		AddGameObject<Block>(L"", Vec3(startPos.x, center.y - 0.5f, 0), Vec3(1, mapSize.y - 2, 1));
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
	void GameStage::CreateParticle() {
		auto explodeParticle = AddGameObject<ExplodeParticle>();
		SetSharedGameObject(L"EXPLODE_PCL", explodeParticle);

		auto blockDestroyParticle = AddGameObject<BlockDestroyParticle>();
		SetSharedGameObject(L"DESTROY_BLOCK_PCL", blockDestroyParticle);
	}

	void GameStage::PlayParticle(const wstring& key, Vec3 pos) {
		auto particle = GetSharedGameObject<ExplodeParticle>(key, false);
		if (particle != nullptr) {
			particle->Shot(pos);
		}
	}
	Vec3 GameStage::GetMapIndex(Vec3 pos) {
		Vec3 mapPos = Vec3(pos.x - m_MapLeftTop.x + 0.5f, m_MapLeftTop.y - pos.y + 0.5f, 0);
		return mapPos.floor(0);
	}
	shared_ptr<GameObject> GameStage::GetBlock(Vec3 pos) {
		Vec3 mapPos = GetMapIndex(pos);
		if (mapPos.y < 0 || mapPos.y >= m_MapData.size() ||
			mapPos.x < 0 || mapPos.x >= m_MapData[mapPos.y].size()) {
			return nullptr;
		}
		return m_MapData[static_cast<int>(mapPos.y)][static_cast<int>(mapPos.x)].GetBlock();
	}
	int GameStage::GetBlockId(Vec3 pos) {
		Vec3 mapPos = GetMapIndex(pos);
		
		return m_MapData[static_cast<int>(mapPos.y)][static_cast<int>(mapPos.x)].GetID();
	}

	void GameStage::DestroyBlock(Vec3 pos,shared_ptr<GameObject>& block) {
		if (m_Player->GetComponent<Transform>()->GetParent() == block) {
			m_Player->GetComponent<Transform>()->SetParent(nullptr);
		}
		Vec3 mapPos = GetMapIndex(pos);
		//m_Map[static_cast<int>(mapPos.y)][static_cast<int>(mapPos.x)] = 0;
		m_MapData[static_cast<int>(mapPos.y)][static_cast<int>(mapPos.x)].RemoveBlock();
		auto it = find(m_LoadedStageObjects.begin(), m_LoadedStageObjects.end(), block);
		if (it != m_LoadedStageObjects.end()) {
			m_LoadedStageObjects.erase(it);
		}
		PlayParticle(L"DESTROY_BLOCK_PCL", block->GetComponent<Transform>()->GetPosition());
		
		RemoveGameObject<GameObject>(block);
	}

	void GameStage::GameClear() {
		if (m_Mode != GameMode::InGame) return;

		SoundManager::Instance().PlaySE(L"WINNER_SD",0.1f);
		AddGameObject<BCSprite>(L"GOALCLEAR_TEX", Vec3(-250,50,0), Vec2(500,100));
		AddGameObject<BCSprite>(L"PUSHY_TEX", Vec3(-150, -200, 0), Vec2(500, 100));

		m_Mode = GameMode::Clear;

	}
	void GameStage::GameOver() {
		if (m_Mode != GameMode::InGame) return;
		
		//SoundManager::Instance().PlaySE(L"LOSER_SD");
		SoundManager::Instance().StopBGM();
		AddGameObject<BCSprite>(L"GAMEOVER_TEX", Vec3(-250, 50, 0), Vec2(500, 100));
		AddGameObject<BCSprite>(L"PUSHY_TEX", Vec3(-150, -200, 0), Vec2(500, 100));

		m_Mode = GameMode::Over;

	}
}
//end basecross
