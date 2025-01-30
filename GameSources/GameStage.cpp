/*!
@file GameStage.cpp
@brief �E�Q�E�[�E��E��E�X�E�e�E�[�E�W�E��E��E��E�
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class Block;
	//--------------------------------------------------------------------------------------
	//	�E�Q�E�[�E��E��E�X�E�e�E�ہE�W�E�N�E��E��E�X�E��E��E��E�
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(-0.5f, 4.0f, -34.0f);
		const Vec3 at(-0.5f,4.0f,0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>(GetThis<GameStage>(), m_ScrollSpeed);
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		PtrCamera->SetStartAt(at);
		PtrCamera->SetStartEye(eye);
		auto PtrMultiLight = CreateLight<MultiLight>();
		PtrMultiLight->SetDefaultLighting();
		
	}

	void GameStage::OnCreate() {
		try {
			

			SoundManager::Instance().PlayBGM(L"BGM_SD",0.2f);
			AddGameObject<ButtonManager>();
			Block::CollisionObjects.clear();
			CreateResource();
			CreateViewLight();
			m_Player = AddGameObject<Player>();
			m_Player->PlayerInitHasBomb(m_BombNum);
			m_RespawnBomb = m_BombNum;

			SetSharedGameObject(L"Player", m_Player);
			CreateMap();
			CreateParticle();
			LoadMap();
			AddGameObject<BackGroundManager>(11.0f);

			AddGameObject<BombThrowOrbit>(m_Player,30);
			
			auto camera = static_pointer_cast<MyCamera>(GetView()->GetTargetCamera());
			camera->SetPlayer(m_Player);

			AddGameObject<Sprite>(L"BOMBNUM_UI", Vec3(430.0f, -250.0f, 0.0f), Vec2(100, 100));
			m_PlayerHasBombs =  AddGameObject<BCNumber>(L"NUMBER_TEX", Vec3(530.0f, -205.0f, 0.0f), Vec2(80, 250), 2);
			m_PlayerHasBombs->UpdateNumber(m_Player->GetHasBomb());

			m_SkipText = AddGameObject<Sprite>(L"SKIP_TEXT_UI", Vec3(450, -310,0), Vec2(150, 50));
			
			CreateMenu();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		SoundManager::Instance().Update();
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		LoadMap();
		BlockUpdateActive();
		if (!IsView()) {
			m_SkipText->SetDrawActive(false);
			m_PlayerHasBombs->UpdateNumber(m_Player->GetHasBomb());

			auto pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (pad.bConnected) {
				//if (IsFinishGame()) {

				//	if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
				//		//���j���[����
				//		Button::Function(m_MenuSelect);
				//		SoundManager::Instance().PlaySE(L"BUTTON_SD");
				//	}
				//	//�I��
				//	if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				//		m_MenuSelect--;
				//	}
				//	else if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				//		m_MenuSelect++;
				//	}
				//	Button::LimitIndex(m_MenuSelect);

				//	Button::SelectButton(m_MenuSelect);

				//}
				//else if (IsOpenMenu()) {
				//	if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
				//		//���j���[����
				//		Button::Function(m_MenuSelect);
				//		SoundManager::Instance().PlaySE(L"BUTTON_SD");
				//	}
				//	//�I��
				//	if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
				//		m_MenuSelect--;
				//	}
				//	else if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				//		m_MenuSelect++;
				//	}
				//	Button::LimitIndex(m_MenuSelect);

				//	Button::SelectButton(m_MenuSelect);
				//}
				if (IsCanActionMenu() && pad.wPressedButtons & XINPUT_GAMEPAD_START) {

					if (IsOpenMenu()) {
						CloseMenu();
					}
					else {
						OpenMenu();
					}
				}

			}
		}
		
	}
	void GameStage::OnDestroy() {
		SoundManager::Instance().StopAll();
	}
	void GameStage::CreateResource() {
		auto& app = App::GetApp();
		wstring path = app->GetDataDirWString();
		wstring uiPath = path + L"UITex/";
		wstring mapPath = path + L"Maps/";
		wstring texPath = path + L"Texture/";
		wstring modelPath = path + L"Models/";
		app->RegisterTexture(L"TEST_TEX", texPath + L"TestTex_wall.jpg");
		app->RegisterTexture(L"TEST100_TEX", texPath + L"TestTex_Wall.png");
		app->RegisterTexture(L"TEST75_TEX", texPath + L"TestTex_wall75.png");
		app->RegisterTexture(L"TEST50_TEX", texPath + L"TestTex_wall50.png");
		app->RegisterTexture(L"TEST25_TEX", texPath + L"TestTex_wall25.png");
		app->RegisterTexture(L"EXPLODE1_TEX", texPath + L"explodeParticle_2.png");
		app->RegisterTexture(L"EXPLODE_SPARK_TEX", texPath + L"explodeSpark.png");
		app->RegisterTexture(L"BOMB_ITEM_TEX", texPath + L"BombItem.png");
		app->RegisterTexture(L"ARROW_ORBIT_TEX", texPath + L"arrow_Orbit.png");
		app->RegisterTexture(L"EXPLODE_BLOCK_TEX", texPath + L"protoExplodeBlock.png");
		app->RegisterTexture(L"TEST_MOVE_TEX", texPath + L"TestTex_Wall_Move.png");

		app->RegisterTexture(L"GOALCLEAR_TEX", uiPath + L"GameClearText_2.png");
		app->RegisterTexture(L"NUMBER_TEX", uiPath + L"TimerNum.png");
		app->RegisterTexture(L"GAMEOVER_TEX", uiPath + L"GameOverText_2.png");
		app->RegisterTexture(L"BACKGROUND_TEX", texPath + L"BackGround.png");

		app->RegisterTexture(L"BOMB_PLUS", uiPath + L"Bumb+3.png");

		app->RegisterTexture(L"RESTART_TEXT_SELECT_UI", uiPath + L"Restart_Selected.png");
		app->RegisterTexture(L"RESTART_TEXT_UI", uiPath + L"Restart.png");
		app->RegisterTexture(L"TITLE_TEXT_SELECT_UI", uiPath + L"BackToTitle_Selected.png");
		app->RegisterTexture(L"TITLE_TEXT_UI", uiPath + L"BackToTitle.png");
		app->RegisterTexture(L"NEXT_TEXT_SELECT_UI", uiPath + L"NextStage_Selected.png");
		app->RegisterTexture(L"NEXT_TEXT_UI", uiPath + L"NextStage.png");
		app->RegisterTexture(L"SELECT_TEXT_SELECT_UI", uiPath + L"Select_Selected.png");
		app->RegisterTexture(L"SELECT_TEXT_UI", uiPath + L"Select.png");

		app->RegisterTexture(L"BOMBNUM_UI", uiPath + L"BomNum.png");
		app->RegisterTexture(L"GOAL_SYMBLE_UI", uiPath + L"GoalSymble.png");
		app->RegisterTexture(L"HEIGHT_BAR_UI", uiPath + L"HeightBar_2.png");
		app->RegisterTexture(L"MENU_BACKGROUND_UI", uiPath + L"Menu_BackGround.png");
		app->RegisterTexture(L"MENU_TEXT_UI", uiPath + L"MenuText.png");
		app->RegisterTexture(L"SKIP_TEXT_UI", uiPath + L"SkipText.png");
		app->RegisterTexture(L"DPAD_NEXT_UI", uiPath + L"NextGame_Oparation.png");

		m_CsvMap.SetFileName(mapPath + m_MapName);
		m_CsvMap.ReadCsv();
	}
	
	void GameStage::CreateMenu() {
		m_MenuBackGround = AddGameObject<Sprite>(L"MENU_BACKGROUND_UI", Vec3(0, 50, 0), Vec2(800, 950), true);
		m_MenuText = AddGameObject<Sprite>(L"MENU_TEXT_UI", Vec3(0, 250, 0), Vec2(256, 64), true);
		m_SendStageNumber = make_shared<int>(m_StageNumber);

		ButtonManager::Create(GetThis<Stage>(), L"Menu", L"RESTART_TEXT_UI", L"RESTART_TEXT_SELECT_UI", Vec3(0.0f, 160.0f, 0.0f), Vec2(400, 80),
			[](shared_ptr<Stage> stage) {
				auto currentStage = static_pointer_cast<GameStage>(stage);
				currentStage->PostEvent(0.0f, currentStage, App::GetApp()->GetScene<Scene>(), L"ToGameStage", currentStage->GetStageNumPtr());
			});
		ButtonManager::Create(GetThis<Stage>(), L"Menu", L"SELECT_TEXT_UI", L"SELECT_TEXT_SELECT_UI", Vec3(0.0f, 0.0f, 0.0f), Vec2(400, 80),
			[](shared_ptr<Stage> stage) {
				stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToSelectStage");
			});
		ButtonManager::Create(GetThis<Stage>(), L"Menu", L"TITLE_TEXT_UI", L"TITLE_TEXT_SELECT_UI", Vec3(0.0f, -160.0f, 0.0f), Vec2(400, 80),
			[](shared_ptr<Stage> stage) {
				stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			});
		ButtonManager::instance->SetInput(L"Menu", InputData(XINPUT_GAMEPAD_DPAD_DOWN, 1));
		ButtonManager::instance->SetInput(L"Menu", InputData(XINPUT_GAMEPAD_DPAD_UP, -1));

		ButtonManager::Create(GetThis<Stage>(), L"clear", L"NEXT_TEXT_UI", L"NEXT_TEXT_SELECT_UI", Vec3(-400.0f, -160.0f, 0.0f), Vec2(300, 60),
			[](shared_ptr<Stage> stage) {
				auto currentStage = static_pointer_cast<GameStage>(stage);
				auto nextStageNumber = *currentStage->GetStageNumPtr().get() + 1;
				currentStage->PostEvent(0.0f, currentStage, App::GetApp()->GetScene<Scene>(), L"ToGameStage", make_shared<int>(nextStageNumber));
			});
		ButtonManager::Create(GetThis<Stage>(), L"clear", L"TITLE_TEXT_UI", L"TITLE_TEXT_SELECT_UI", Vec3(0.0f, -160.0f, 0.0f), Vec2(300, 60),
			[](shared_ptr<Stage> stage) {
				stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			});
		ButtonManager::Create(GetThis<Stage>(), L"clear", L"RESTART_TEXT_UI", L"RESTART_TEXT_SELECT_UI", Vec3(400.0f, -160.0f, 0.0f), Vec2(300, 60),
			[](shared_ptr<Stage> stage) {
				auto currentStage = static_pointer_cast<GameStage>(stage);
				currentStage->PostEvent(0.0f, currentStage, App::GetApp()->GetScene<Scene>(), L"ToGameStage", currentStage->GetStageNumPtr());
			});

		ButtonManager::instance->AddFunction(L"clear", 0, [](shared_ptr<SpriteButton>& button) {
			auto stage = static_pointer_cast<GameStage>(button->GetStage());
			button->SetActive(App::GetApp()->GetScene<GameScene>()->IsNextStage(*stage->GetStageNumPtr().get()));
			});
		ButtonManager::instance->SetInput(L"clear", InputData(XINPUT_GAMEPAD_DPAD_RIGHT, 1));
		ButtonManager::instance->SetInput(L"clear", InputData(XINPUT_GAMEPAD_DPAD_LEFT, -1));

		ButtonManager::Create(GetThis<Stage>(), L"failed", L"TITLE_TEXT_UI", L"TITLE_TEXT_SELECT_UI", Vec3(-400.0f, -160.0f, 0.0f), Vec2(300, 60),
			[](shared_ptr<Stage> stage) {
				stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			});
		ButtonManager::Create(GetThis<Stage>(), L"failed", L"RESTART_TEXT_UI", L"RESTART_TEXT_SELECT_UI", Vec3(400.0f, -160.0f, 0.0f), Vec2(300, 60),
			[](shared_ptr<Stage> stage) {
				auto currentStage = static_pointer_cast<GameStage>(stage);
				if (currentStage->GetGameMode() == GameMode::Clear) {
					currentStage->PostEvent(0.0f, currentStage, App::GetApp()->GetScene<Scene>(), L"ToGameStage", currentStage->GetStageNumPtr());
				}
				else {
					currentStage->InitializeStage();
				}
			});
		ButtonManager::instance->SetInput(L"failed", InputData(XINPUT_GAMEPAD_DPAD_RIGHT, 1));
		ButtonManager::instance->SetInput(L"failed", InputData(XINPUT_GAMEPAD_DPAD_LEFT, -1));

		ButtonManager::instance->CloseAll();


		CloseMenu();
	}
	void GameStage::CreateMap() {
		auto& mapVec = m_CsvMap.GetCsvVec();
		m_Walls = AddGameObject<InstanceBlock>(L"TEST_TEX", mapVec.size() - 1);

		vector<wstring> cellStr;

		m_MapData.clear();
		m_InitMapData.clear();

		for (int y = 0; y < mapVec.size(); y++) {
			m_MapData.push_back({});
			m_InitMapData.push_back({});

			cellStr.clear();
			Util::WStrToTokenVector(cellStr, mapVec[y], L',');
			if (y == 0) {
				m_MapLeftTop = Vec3(static_cast<float>(cellStr.size()) / -2.0f, mapVec.size() - 1, 0);
				m_MapRightBottom = Vec3(cellStr.size() / 2.0f - 1, -0.5f, 0.0f);
			}

			for (int x = 0; x < cellStr.size(); x++) {
				vector<wstring> numStr;
				Util::WStrToTokenVector(numStr, cellStr[x], L'>');
				wstring blockTypeStr = numStr[0];
				wstring blockArgumentStr = L"";
				if (numStr.size() > 1) {
					blockArgumentStr = numStr[1];
				}

				if (blockTypeStr == L"") continue;

				if (all_of(blockTypeStr.cbegin(), blockTypeStr.cend(), isdigit)) {
					int blockType = stoi(blockTypeStr);
					m_MapData[y].push_back(BlockData(blockType, blockArgumentStr));
					m_InitMapData[y].push_back(BlockData(blockType, blockArgumentStr));

					switch (blockType) {
					case BlockTypes::UNBREAK:
						m_Walls->AddBlock(y, blockType);
						break;
					case BlockTypes::GOAL:
						CreateBlock(Vec2(x, y), GetWorldPosition(Vec2(x,y)));
						break;
					}
				}
				else {
					if (blockTypeStr == L"s") {
						m_Player->GetComponent<Transform>()->SetPosition(GetWorldPosition(Vec2(x, y)));
						m_Walls->AddBlock(y, BlockTypes::AIR);
						NewRespawnPosition(GetWorldPosition(Vec2(x, y)));
						m_DefaultStartPos = GetWorldPosition(Vec2(x, y));
						m_MapData[y].push_back(BlockData(BlockTypes::AIR));
						m_InitMapData[y].push_back(BlockData(BlockTypes::AIR));
					}
				}
			}
		}

		m_Walls->SetStartPos((Vec2)m_MapLeftTop);
		auto camera = GetView()->GetTargetCamera();
		float atY = camera->GetAt().y;

		float mapHeight = mapVec.size() - 1;
		LoadMap();
		AddGameObject<StageLengthBar>(mapHeight, m_Player, m_Goal);
		/*auto& mapVec = m_CsvMap.GetCsvVec();
		m_Walls = AddGameObject<InstanceBlock>(L"TEST_TEX", mapVec.size() - 1);
		vector<wstring> cells;
		Vec2 startPos;

		for (int y = 0; y < mapVec.size() - 1; y++) {
			m_MapData.push_back({});
			cells.clear();
			Util::WStrToTokenVector(cells, mapVec[y + 1], L',');
			startPos = Vec2(static_cast<float>(cells.size()) / -2.0f, mapVec.size() - 2);
			if (y == 0) {
				m_MapLeftTop = startPos;
				m_MapRightBottom = Vec3(cells.size() / 2.0f - 1, -0.5f, 0.0f);
			}
			for (int x = 0; x < cells.size(); x++) {
				vector<wstring> numStr;
				Util::WStrToTokenVector(numStr, cells[x], L'>');
				if (numStr[0] == L"") {
					continue;
				}
				if (all_of(numStr[0].cbegin(), numStr[0].cend(), isdigit)) {
					int cell = stoi(numStr[0]);

					if (numStr.size() >= 2) {
						m_MapData[y].push_back(BlockData(cell, numStr[1]));
					}
					else {
						m_MapData[y].push_back(BlockData(cell));
					}

					if (cell == BlockTypes::UNBREAK) {
						m_Walls->AddBlock(y, cell);
					}
					else if (cell == BlockTypes::GOAL) {
						CreateBlock(Vec2(x, y), Vec3(m_MapLeftTop.x + x, m_MapLeftTop.y - y, 0));
					}
					else {
						m_Walls->AddBlock(y, 0);
					}

				}
				else {
					if (numStr[0] == L"s") {
						m_Player->GetComponent<Transform>()->SetPosition(Vec3(m_MapLeftTop.x + x, m_MapLeftTop.y - y, 0));
						m_Walls->AddBlock(y, 0);
						NewRespawnPosition(Vec3(m_MapLeftTop.x + x, m_MapLeftTop.y - y, 0));
						m_MapData[y].push_back(BlockData(0));
					}
				}
			}
		}
		m_Walls->SetStartPos((Vec2)m_MapLeftTop);
		auto camera = GetView()->GetTargetCamera();
		float atY = camera->GetAt().y;

		Vec2 mapSize = Vec2(cells.size(), mapVec.size() - 1);
		LoadMap();
		AddGameObject<StageLengthBar>(mapSize.y, m_Player, m_Goal);*/
	}
	void GameStage::RegisterBlock(Vec2 mapIndex, const shared_ptr<GameObject>& obj) {
		if (m_MapData[mapIndex.y][mapIndex.x].GetBlock() == nullptr) {
			m_MapData[mapIndex.y][mapIndex.x].SetGameObject(obj);
		}
	}
	shared_ptr<GameObject> GameStage::CreateBlock(Vec2 mapIndex, Vec3 pos) {
		shared_ptr<GameObject> obj = nullptr;
		BlockData mapData = m_MapData[mapIndex.y][mapIndex.x];
		switch (mapData.GetID()) {
		case BlockTypes::NORMAL: {
			auto durabilityStr = mapData.GetData(L"hp");
			float durability = 100;
			if (durabilityStr != L"") {
				durability = BlockData::WstrToFloat(durabilityStr);
			}
			obj = AddGameObject<FloorBlock>(L"TEST_TEX", pos, durability);
			break;
		}
		case BlockTypes::EXPLODE: {
			auto rangeStr = mapData.GetData(L"range");
			auto powerStr = mapData.GetData(L"power");
			float range = 0;
			float power = 0;

			if (rangeStr != L"") {
				range = BlockData::WstrToFloat(rangeStr);
			}
			if (powerStr != L"") {
				power = BlockData::WstrToFloat(powerStr);
			}
			obj = AddGameObject<ExplodeBlock>(L"EXPLODE_BLOCK_TEX",pos, power,range);
			break;
		}
		case BlockTypes::ADDBOMB: {
			
			obj = AddGameObject<BombItem>(pos, 3);
			break;
		}
		case BlockTypes::GOAL:
			m_Goal = AddGameObject<Goal>(pos + Vec3(0,0,1));
			m_MapData[mapIndex.y][mapIndex.x].m_Id = 0;
			break;
		case BlockTypes::CHECKPOINT:
			obj = AddGameObject<CheckPoint>(pos);
			break;
		case BlockTypes::MOVE: {
			auto speedStr = mapData.GetData(L"speed");
			auto rangeStr = mapData.GetData(L"range");
			auto startStr = mapData.GetData(L"start");
			auto endStr = mapData.GetData(L"end");
			float speed = 0;
			Vec3 range = Vec3();
			Vec3 start = Vec3();
			Vec3 end = Vec3();
			
			if (speedStr != L"") {
				speed = BlockData::WstrToFloat(speedStr);
			}
			if (rangeStr != L"") {
				range = BlockData::WstrToVec3(rangeStr);
			}
			if (startStr != L"") {
				start = BlockData::WstrToVec3(startStr);
			}
			if (endStr != L"") {
				end = BlockData::WstrToVec3(endStr);
			}

			if (start == Vec3() && end == Vec3()) {
				obj = AddGameObject<MoveBlock>(L"TEST_MOVE_TEX", pos, speed, range);
			}
			else {
				obj = AddGameObject<MoveBlock>(L"TEST_MOVE_TEX", pos, speed, start,end);
			}
			break;
		}
		}
		
		m_MapData[mapIndex.y][mapIndex.x].SetGameObject(obj);
		if (obj != nullptr) {
			m_MapData[mapIndex.y][mapIndex.x].SetIsLoaded(true);
		}
		
		return obj;
	}
	void GameStage::LoadMap() {
		auto camera = GetView()->GetTargetCamera();
		auto playerTrans = m_Player->GetComponent<Transform>();
		Vec3 playerPos = playerTrans->GetWorldPosition();
		Vec3 mapIndex = GetMapIndex(camera->GetAt());
		int maxLoadIndexY = mapIndex.y + m_LoadStageSize.y;
		int minLoadIndexY = mapIndex.y - m_LoadStageSize.y;
		//�v���C���[�̎��ӂ܂ł͍Œ�ł���������
		Vec3 playerIndex = GetMapIndex(playerPos);
		maxLoadIndexY = max(playerIndex.y + 2, maxLoadIndexY);
		minLoadIndexY = min(playerIndex.y, minLoadIndexY);
		//�}�b�v�̍ő�ŏ����z���Ȃ��悤�ɂ���
		maxLoadIndexY = min(m_MapData.size() - 1, maxLoadIndexY);
		minLoadIndexY = max(0, minLoadIndexY);

		for (int y = minLoadIndexY; y < maxLoadIndexY; y++) {
			for (int x = 0; x < m_MapData[y].size(); x++) {
				if (!m_MapData[y][x].GetIsLoaded()) {
					auto obj = CreateBlock(Vec2(x, y), Vec3(m_MapLeftTop.x + x, m_MapLeftTop.y - y, 0));
				}
			}
		}
		for (int y = 0; y < m_MapData.size(); y++) {
			for (int x = 0; x < m_MapData[y].size(); x++) {
				if (!m_MapData[y][x].GetIsLoaded()) continue;

				if (y < minLoadIndexY || y > maxLoadIndexY) {
					RemoveGameObject<GameObject>(m_MapData[y][x].GetBlock());
					m_MapData[y][x].SetIsLoaded(false);
				}
			}
		}
		m_Walls->DrawMap(m_MapData,Vec2(m_LoadStageSize.x, m_LoadStageSize.y), m_MapLeftTop);
	}
	void GameStage::InitializeStage() {
		if (m_DefaultStartPos == m_RespawnPosition) {
			PostEvent(0.0f, GetThis<Stage>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage", GetStageNumPtr());
		}
		for (int i = 0; i < m_MapData.size(); i++) {
			for (int j = 0; j < m_MapData[i].size(); j++) {
				RemoveGameObject<GameObject>(m_MapData[i][j].m_Obj);
				m_MapData[i][j] = m_InitMapData[i][j];
			}
		}
		LoadMap();
		PlayerRespawn();
		CloseMenu();
		ButtonManager::instance->CloseAll();
		CreateMenu();
		m_MenuSelect = 0;

		for (auto& object : m_DeleteToRestartObjects) {
			RemoveGameObject<GameObject>(object);
		}
		m_DeleteToRestartObjects.clear();
		auto camera = GetView()->GetTargetCamera();
		auto myCamera = static_pointer_cast<MyCamera>(camera);
		myCamera->RespawnCamera();

		
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
					col->SetUpdateActive(isCollider);
				}
				else {
					blockObject->SetUpdateActive(isCollider);
				}
			}
		}
	}
	void GameStage::CreateParticle() {
		auto explodeParticle = AddGameObject<ExplodeParticle>();
		SetSharedGameObject(L"EXPLODE_PCL", explodeParticle);

		auto blockDestroyParticle = AddGameObject<BlockDestroyParticle>();
		SetSharedGameObject(L"DESTROY_BLOCK_PCL", blockDestroyParticle);

		auto particleRunDust = AddGameObject<ParticleRunDust>();
		SetSharedGameObject(L"PCL_RUNDUST", particleRunDust);

		auto particleGoal = AddGameObject<ParticleGoal>();
		SetSharedGameObject(L"PCL_GOAL", particleGoal);
	}
	Vec3 GameStage::GetMapIndex(Vec3 pos) {
		Vec3 mapPos = Vec3(pos.x - m_MapLeftTop.x + 0.5f, m_MapLeftTop.y - pos.y + 0.5f, 0);
		return mapPos.floor(0);
	}
	Vec3 GameStage::GetWorldPosition(Vec2 pos) {
		Vec3 worldPos = Vec3(m_MapLeftTop.x + pos.x, m_MapLeftTop.y - pos.y, 0);
		return worldPos;
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
		if (mapPos.y < 0 || mapPos.y >= m_MapData.size() ||
			mapPos.x < 0 || mapPos.x >= m_MapData[mapPos.y].size()) {
			return 0;
		}
		return m_MapData[static_cast<int>(mapPos.y)][static_cast<int>(mapPos.x)].GetID();
	}
	int GameStage::GetBlockId(Vec2 index) {
		if (index.y < 0 || index.y >= m_MapData.size() ||
			index.x < 0 || index.x >= m_MapData[index.y].size()) {
			return 0;
		}
		return m_MapData[static_cast<int>(index.y)][static_cast<int>(index.x)].GetID();
	}

	void GameStage::DestroyBlock(Vec3 pos,shared_ptr<GameObject>& block) {
		if (m_Player->GetComponent<Transform>()->GetParent() == block) {
			m_Player->GetComponent<Transform>()->SetParent(nullptr);
		}
		Vec3 mapPos = GetMapIndex(pos);
		m_MapData[static_cast<int>(mapPos.y)][static_cast<int>(mapPos.x)].RemoveBlock();
		RemoveGameObject<GameObject>(block);
	}

	void GameStage::GameClear() {
		if (!IsPlaying()) return;

		m_Player->GetComponent<BCGravity>()->SetVelocity(Vec3(0));
		SoundManager::Instance().PlaySE(L"WINNER_SD",0.1f);
		SoundManager::Instance().StopBGM();
		m_DeleteToRestartObjects.push_back(AddGameObject<Sprite>(L"GOALCLEAR_TEX", Vec3(-250,50,0), Vec2(500,100)));
		ButtonManager::instance->OpenAndUse(L"clear");
		
		m_DeleteToRestartObjects.push_back(AddGameObject<Sprite>(L"DPAD_NEXT_UI", Vec3(338.4f, -230, 0), Vec2(281.6f, 140.8f)));

		ChangeMode(GameMode::Clear);

		App::GetApp()->GetScene<GameScene>()->Clear(m_StageNumber);
	}
	void GameStage::GameOver() {
		if (!IsPlaying()) return;
		
		SoundManager::Instance().PlaySE(L"LOSER_SD");
		SoundManager::Instance().StopBGM();
		m_DeleteToRestartObjects.push_back(AddGameObject<Sprite>(L"GAMEOVER_TEX", Vec3(-250, 50, 0), Vec2(500, 100)));
		ButtonManager::instance->OpenAndUse(L"failed");
		m_DeleteToRestartObjects.push_back(AddGameObject<Sprite>(L"DPAD_NEXT_UI", Vec3(338.4f, -230, 0), Vec2(281.6f, 140.8f)));

		ChangeMode(GameMode::Over);

	}

	void GameStage::OpenMenu() {
		ChangeMode(GameMode::Menu);
		//Button::SetActive(true);
		ButtonManager::instance->OpenAndUse(L"Menu");
		m_MenuBackGround->GetComponent<SpriteBaseDraw>()->SetDrawActive(true);
		m_MenuText->GetComponent<SpriteBaseDraw>()->SetDrawActive(true);
	}

	void GameStage::CloseMenu() {
		ChangeMode(GetBeforeMode());
		ButtonManager::instance->Close(L"Menu");
		//Button::SetActive(false);
		m_MenuBackGround->GetComponent<SpriteBaseDraw>()->SetDrawActive(false);
		m_MenuText->GetComponent<SpriteBaseDraw>()->SetDrawActive(false);
	}
}
//end basecross
