/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class Block;
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(-0.5f, 4.0f, -34.0f);
		const Vec3 at(-0.5f,4.0f,0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>(GetThis<GameStage>(),1.0f);
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			Block::m_MoveObjects.clear();
			CreateViewLight();
			CreateResource();
			m_Player = AddGameObject<Player>(make_shared<PlayerStateIdle>());
			Block::m_MoveObjects.push_back(m_Player->GetComponent<Transform>());
			CreateMap();
			CreateParticle();
			LoadMap();

			AddGameObject<BombThrowArrow>(m_Player);
			

			auto camera = static_pointer_cast<MyCamera>(GetView()->GetTargetCamera());
			camera->SetPlayer(m_Player);

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
		int minute = m_MainTimer / 60.0f;
		int second = m_MainTimer - 60.0f * minute;

		//m_TimerSprite[1]->UpdateNumber(minute);
		//m_TimerSprite[0]->UpdateNumber(second);

		LoadMap();

		BlockUpdateActive();

		m_PlayerHasBombs->UpdateNumber(m_Player->GetHasBomb());

<<<<<<< HEAD
		if (m_Mode != GameMode::InGame) {
=======
		if (isGameOver) {
>>>>>>> master
			auto pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (pad.bConnected) {
				if (pad.wPressedButtons == XINPUT_GAMEPAD_Y) {
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				}
			}
		}
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
		app->RegisterTexture(L"EXPLODE1_TEX", texPath + L"explodeParticle1.png");
		app->RegisterTexture(L"EXPLODE2_TEX", texPath + L"explodeParticle2.png");
		app->RegisterTexture(L"BOMB_THROW_TEX", texPath + L"arrow.png");

		app->RegisterTexture(L"GOALCLEAR_TEX", uiPath + L"GameClearTest1.png");
		app->RegisterTexture(L"NUMBER_TEX", uiPath + L"TimerNum.png");
<<<<<<< HEAD
		app->RegisterTexture(L"GAMEOVER_TEX", uiPath + L"GameOverText1.png");
		app->RegisterTexture(L"BACKGROUND_TEX", texPath + L"BackGround.png");
		app->RegisterTexture(L"PUSHY_TEX", uiPath + L"PushYText1.png");
		app->RegisterTexture(L"BOMBNUM_UI", uiPath + L"BombNumUI.png");

=======
		app->RegisterTexture(L"GOALCLEAR_TEX", texPath + L"GameClearTest.png");
		app->RegisterTexture(L"GAMEOVER_TEX", uiPath + L"GameOverText.png");
		app->RegisterTexture(L"BACKGROUND_TEX", texPath + L"BackGround.png");
		app->RegisterTexture(L"PUSHY_TEX", uiPath + L"PushYText.png");
		app->RegisterTexture(L"BOMBNUM_UI", uiPath + L"BombNumUI.png");

		auto model = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Goalkari.bmf");
		app->RegisterResource(L"GOAL_MD", model);
		
		model = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Player.bmf");
		app->RegisterResource(L"PLAYER_MD", model);
		app->RegisterTexture(L"PLAYER_MD_TEX", modelPath + L"chara.png");
>>>>>>> master

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
			cells.clear();
			vector<int> cow;
			Util::WStrToTokenVector(cells, mapVec[y + 1], L',');
			startPos = Vec2(static_cast<float>(cells.size()) / -2.0f, mapVec.size() - 2);
			if (y == 0) {
				m_MapLeftTop = startPos;
			}
			for (int x = 0; x < cells.size(); x++) {
				int cell = stoi(cells[x]);
				
				if (cell == 2) {
					m_Walls->AddBlock(y, cell);
				}
				else {
					m_Walls->AddBlock(y, 0);
				}
				cow.push_back(cell);
			}
			m_Map.push_back(cow);
		}
		m_Walls->SetStartPos((Vec2)m_MapLeftTop);
		auto camera = GetView()->GetTargetCamera();
		float atY = camera->GetAt().y;

		Vec2 mapSize = Vec2(cells.size(), mapVec.size() - 1);
		//CreateWallCollider(startPos, mapSize);
		LoadMap();
	}

	shared_ptr<GameObject> GameStage::CreateBlock(int blockNum, Vec3 pos) {
		shared_ptr<GameObject> obj = nullptr;
		switch (blockNum) {
		case 1:
			obj = AddGameObject<FloorBlock>(L"TEST_TEX", pos,100);
			break;
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
		}

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
		//�V�����}�b�v�����[�h
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
		////���[�h���Ȃ��ꍇ�͂����ŏI��
		//else if(m_LoadedMaxHeight == static_cast<int>(atY) + m_LoadStageSize.y){
		//	return;
		//}
		if (m_CameraAtY == 0) {
			m_CameraAtY = atY;
			for (int i = 0; i <= m_CameraAtY + m_LoadStageSize.y; i++) {
				if (i >= m_Map.size()) {
					break;
				}
				int y = m_Map.size() - i - 1;
				int sizeX = m_Map[y].size();
				for (int x = 0; x < sizeX; x++) {
					int size = m_Map[y].size();
					auto obj = CreateBlock(m_Map[y][x], Vec3(m_MapLeftTop.x + x, m_MapLeftTop.y - y, 0));
					if (obj != nullptr) {
						m_LoadedStageObjects.push_back(obj);
					}
				}
			}
<<<<<<< HEAD
=======

>>>>>>> master
			m_Walls->DrawMap(Vec2(m_Map[0].size(), atY + m_LoadStageSize.y), Vec2(0, atY - m_LoadStageSize.y));
			return;
		}
		for (int i = m_CameraAtY + m_LoadStageSize.y + 1; i <= atY + m_LoadStageSize.y; i++) {
			if (i >= m_Map.size()) return;

			for (int j = 0; j < m_Map[i].size(); j++) {

				int loadIndexY = m_Map.size() - i - 1;
				float sizeX = static_cast<float>(m_Map[i].size());
				Vec2 startPos = Vec2(sizeX / -2, m_Map.size() - 2);
				auto obj = CreateBlock(m_Map[loadIndexY][j], Vec3(startPos.x + j, startPos.y - loadIndexY, 0));//AddGameObject<FloorBlock>(L"TEST_TEX", );
				if (obj != nullptr) {
					m_LoadedStageObjects.push_back(obj);
				}
			}
		}

		for (int i = m_CameraAtY - m_LoadStageSize.y - 1; i >= atY - m_LoadStageSize.y; i--) {
			if (i < 0) return;

			for (int j = 0; j < m_Map[i].size(); j++) {

				int loadIndexY = m_Map.size() - i - 1;
				Vec2 startPos = Vec2(m_Map[i].size() / -2.0f, m_Map.size() - 2);
				auto obj = CreateBlock(m_Map[loadIndexY][j], Vec3(startPos.x + j, startPos.y - loadIndexY, 0));//AddGameObject<FloorBlock>(L"TEST_TEX", );
				if (obj != nullptr) {
					m_LoadedStageObjects.push_back(obj);
				}
			}
		}
		m_CameraAtY = atY;
		m_Walls->DrawMap(Vec2(m_Map[0].size(), m_CameraAtY + m_LoadStageSize.y), Vec2(0, m_CameraAtY - m_LoadStageSize.y));
		//�͈͊O�ɓ������u���b�N���폜
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
				for (int i = 0; i < Block::m_MoveObjects.size(); i++) {
					auto trans = Block::m_MoveObjects[i].lock();
					if (trans != nullptr) {
						
						if (length(trans->GetWorldPosition() - blockObject->GetComponent<Transform>()->GetWorldPosition()) < 3.0f) {
							isCollider = true;
						}
						
					}
					else {
						Block::m_MoveObjects.erase(Block::m_MoveObjects.begin() + i);
					}
				}
				auto col = blockObject->GetComponent<Collision>(false);
				if (col != nullptr) {
					col->SetDrawActive(isCollider);
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
		//��
		AddGameObject<Block>(L"", Vec3(center.x - 0.5f, startPos.y, 0), Vec3(mapSize.x, 1, 1));
		//��
		AddGameObject<Block>(L"", Vec3(center.x - 0.5f, startPos.y - mapSize.y + 1, 0), Vec3(mapSize.x, 1, 1));
		//�E
		AddGameObject<Block>(L"", Vec3(startPos.x + mapSize.x - 1, center.y - 0.5f, 0), Vec3(1, mapSize.y - 2, 1));
		//��
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
		Vec3 mapPos = Vec3(pos.x - m_MapLeftTop.x, m_MapLeftTop.y - pos.y, 0);
		return mapPos.floor(0);
	}
	int GameStage::GetBlock(Vec3 pos) {
		Vec3 mapPos = GetMapIndex(pos);
		
		return m_Map[mapPos.y][mapPos.x];
	}

	void GameStage::DestroyBlock(Vec3 pos,shared_ptr<GameObject>& block) {
		if (m_Player->GetComponent<Transform>()->GetParent() == block) {
			m_Player->GetComponent<Transform>()->SetParent(nullptr);
		}
		Vec3 mapPos = GetMapIndex(pos);
		m_Map[mapPos.y][mapPos.x] = 0;
		auto it = find(m_LoadedStageObjects.begin(), m_LoadedStageObjects.end(), block);
		if (it != m_LoadedStageObjects.end()) {
			m_LoadedStageObjects.erase(it);
		}
		PlayParticle(L"DESTROY_BLOCK_PCL", block->GetComponent<Transform>()->GetPosition());
		
		RemoveGameObject<GameObject>(block);
	}

	void GameStage::GameClear() {
		AddGameObject<BCSprite>(L"GOALCLEAR_TEX", Vec3(-250,50,0), Vec2(500,100));
		AddGameObject<BCSprite>(L"PUSHY_TEX", Vec3(-150, -200, 0), Vec2(500, 100));

<<<<<<< HEAD
		m_Mode = GameMode::Clear;
=======
		isGameOver = true;
>>>>>>> master
	}
	void GameStage::GameOver() {
		AddGameObject<BCSprite>(L"GAMEOVER_TEX", Vec3(-250, 50, 0), Vec2(500, 100));
		AddGameObject<BCSprite>(L"PUSHY_TEX", Vec3(-150, -200, 0), Vec2(500, 100));

<<<<<<< HEAD
		m_Mode = GameMode::Over;
=======
		isGameOver = true;
>>>>>>> master
	}
}
//end basecross
