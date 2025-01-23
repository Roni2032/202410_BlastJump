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
			CreateViewLight();

			SoundManager::Instance().PlayBGM(L"BGM_SD",0.2f);
			Block::CollisionObjects.clear();
			CreateResource();
			m_Player = AddGameObject<Player>();
			m_Player->PlayerInitHasBomb(m_BombNum);

			SetSharedGameObject(L"Player", m_Player);
			NewCreateMap();
			CreateParticle();
			LoadMap();
			AddGameObject<BackGroundManager>(11.0f);

			AddGameObject<BombThrowOrbit>(m_Player,30);
			
			auto camera = static_pointer_cast<MyCamera>(GetView()->GetTargetCamera());
			camera->SetPlayer(m_Player);

			AddGameObject<BCSprite>(L"BOMBNUM_UI", Vec3(-630.0f, -230.0f, 0.0f), Vec2(200, 150));
			m_PlayerHasBombs =  AddGameObject<BCNumber>(L"NUMBER_TEX", Vec3(-520.0f, -190.0f, 0.0f), Vec2(80, 250), 2);
			m_PlayerHasBombs->UpdateNumber(m_Player->GetHasBomb());

			m_SkipText = AddGameObject<BCSprite>(L"SKIP_TEXT_UI", Vec3(450, -310,0), Vec2(150, 50));
			
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
				if (IsFinishGame()) {

					if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
						//���j���[����
						Button::Function(m_MenuSelect);
						SoundManager::Instance().PlaySE(L"BUTTON_SD");
					}
					//�I��
					if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
						m_MenuSelect--;
					}
					else if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
						m_MenuSelect++;
					}
					Button::CheckOverIndex(m_MenuSelect);

					Button::SelectButton(m_MenuSelect);

				}
				else if (IsOpenMenu()) {
					if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
						//���j���[����
						Button::Function(m_MenuSelect);
						SoundManager::Instance().PlaySE(L"BUTTON_SD");
					}
					//�I��
					if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
						m_MenuSelect--;
					}
					else if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
						m_MenuSelect++;
					}
					Button::CheckOverIndex(m_MenuSelect);

					Button::SelectButton(m_MenuSelect);
				}
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
		m_MenuBackGround = AddGameObject<BCSprite>(L"MENU_BACKGROUND_UI", Vec3(0, 50, 0), Vec2(800, 950), true);
		m_MenuText = AddGameObject<BCSprite>(L"MENU_TEXT_UI", Vec3(0, 250, 0), Vec2(256, 64), true);

		m_SendStageNumber = make_shared<int>(m_StageNumber);
		auto button = AddGameObject<Button>(L"SELECT_TEXT_UI", Vec3(0.0f, 160.0f, 0.0f), Vec2(400, 80));
		button->AddSelectEffect(SelectEffect::ChangeSprite);
		button->SetFunction([](shared_ptr<Stage> stage) {stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToSelectStage"); });
		button->SetSelectTex(L"SELECT_TEXT_SELECT_UI");

		button = AddGameObject<Button>(L"TITLE_TEXT_UI", Vec3(0.0f, 0.0f, 0.0f), Vec2(400, 80));
		button->AddSelectEffect(SelectEffect::ChangeSprite);
		button->SetFunction([](shared_ptr<Stage> stage) {stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToTitleStage"); });
		button->SetSelectTex(L"TITLE_TEXT_SELECT_UI");
		
		button = AddGameObject<Button>(L"RESTART_TEXT_UI", Vec3(0.0f, -160.0f, 0.0f), Vec2(400, 80));
		button->AddSelectEffect(SelectEffect::ChangeSprite);
		button->SetFunction([](shared_ptr<Stage> stage) {
			auto currentStage = static_pointer_cast<GameStage>(stage);
			//stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToGameStage", currentStage->GetStageNumPtr());
			currentStage->InitializeStage();
			});
		button->SetSelectTex(L"RESTART_TEXT_SELECT_UI");
		CloseMenu();
	}
	void GameStage::CreateFinishButton(bool flag) {
		Button::Clear();
		Vec3 drawPos = Vec3();
		
		auto button = AddGameObject<Button>(L"RESTART_TEXT_UI", Vec3(-400.0f, -160.0f, 0.0f), Vec2(300, 60));
		button->AddSelectEffect(SelectEffect::ChangeSprite);

		button->SetFunction([](shared_ptr<Stage> stage) {
			auto currentStage = static_pointer_cast<GameStage>(stage);
			stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToGameStage", currentStage->GetStageNumPtr());
			//currentStage->PlayerRespawn();
			});
		button->SetSelectTex(L"RESTART_TEXT_SELECT_UI");

		if (flag) {
			drawPos = Vec3(0.0f, -160.0f, 0.0f);
		}
		else {
			drawPos = Vec3(400.0f, -160.0f, 0.0f);
		}
		button = AddGameObject<Button>(L"TITLE_TEXT_UI", drawPos, Vec2(300, 60));
		button->AddSelectEffect(SelectEffect::ChangeSprite);

		button->SetFunction([](shared_ptr<Stage> stage) {
			stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			});
		button->SetSelectTex(L"TITLE_TEXT_SELECT_UI");
		
		if (!flag) return;

		if (m_StageNumber >= MAX_STAGE - 1) {
			AddGameObject<BCSprite>(L"NEXT_TEXT_UI", Vec3(400.0f, -160.0f, 0.0f), Vec2(300, 60), true);
		}
		else {
			auto button = AddGameObject<Button>(L"NEXT_TEXT_UI", Vec3(400.0f, -160.0f, 0.0f), Vec2(300, 60));
			button->AddSelectEffect(SelectEffect::ChangeSprite);

			button->SetFunction([](shared_ptr<Stage> stage) {
				auto currentStage = static_pointer_cast<GameStage>(stage);
				auto nextStageNumber = currentStage->GetStageNumPtr().get();
				stage->PostEvent(0.0f, stage, App::GetApp()->GetScene<Scene>(), L"ToGameStage", make_shared<int>(*nextStageNumber + 1));
				});
			button->SetSelectTex(L"NEXT_TEXT_SELECT_UI");
		}
	}
	void GameStage::CreateMap() {
		
		auto& mapVec = m_CsvMap.GetCsvVec();
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
				m_MapRightBottom = Vec3(cells.size() / 2.0f - 1, -0.5f,0.0f);
			}
			for (int x = 0; x < cells.size(); x++) {
				vector<wstring> numStr;
				Util::WStrToTokenVector(numStr, cells[x], L'>');
				if (numStr[0] == L"") {
					continue;
				}
				if (all_of(numStr[0].cbegin(), numStr[0].cend(),isdigit)) {
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
					else{
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
		AddGameObject<StageLengthBar>(mapSize.y,m_Player,m_Goal);
	}
	void GameStage::NewCreateMap() {
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
			auto addNumStr = mapData.GetData(L"add");
			int addNum = 2;
			if (addNumStr != L"") {
				addNum = BlockData::WstrToInt(addNumStr);
			}
			obj = AddGameObject<BombItem>(pos, addNum);
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
		Vec3 playerPos = playerTrans->GetPosition();

		Vec3 mapIndex = GetMapIndex(camera->GetAt());
		int maxLoadIndexY = mapIndex.y + m_LoadStageSize.y;
		int minLoadIndexY = mapIndex.y - m_LoadStageSize.y;
		//�v���C���[�̎��ӂ܂ł͍Œ�ł���������
		Vec3 playerIndex = GetMapIndex(playerPos);
		maxLoadIndexY = max(playerIndex.y, maxLoadIndexY);
		minLoadIndexY = min(playerIndex.y - 2, minLoadIndexY);
		//�}�b�v�̍ő�ŏ����z���Ȃ��悤�ɂ���
		maxLoadIndexY = min(m_MapData.size() - 1, maxLoadIndexY);
		minLoadIndexY = max(0, minLoadIndexY);

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
		for (int i = 0; i < m_MapData.size(); i++) {
			for (int j = 0; j < m_MapData[i].size(); j++) {
				RemoveGameObject<GameObject>(m_MapData[i][j].m_Obj);
				m_MapData[i][j] = m_InitMapData[i][j];
			}
		}
		LoadMap();
		PlayerRespawn();
		CloseMenu();
		Button::Clear();
		CreateMenu();
		m_MenuSelect = 0;
		NewRespawnPosition(GetRespawnPosition() + Vec3(1, 0, 0));
		auto camera = GetView()->GetTargetCamera();
		auto myCamera = static_pointer_cast<MyCamera>(camera);
		myCamera->RespawnCamera();

		
	}
	void GameStage::InitializeStage() {

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
		auto sprite = AddGameObject<BCSprite>(L"GOALCLEAR_TEX", Vec3(-250,50,0), Vec2(500,100));
		CreateFinishButton(true);
		
		AddGameObject<BCSprite>(L"DPAD_NEXT_UI", Vec3(338.4f, -230, 0), Vec2(281.6f, 140.8f));

		ChangeMode(GameMode::Clear);

	}
	void GameStage::GameOver() {
		if (!IsPlaying()) return;
		
		SoundManager::Instance().PlaySE(L"LOSER_SD");
		SoundManager::Instance().StopBGM();
		auto sprite = AddGameObject<BCSprite>(L"GAMEOVER_TEX", Vec3(-250, 50, 0), Vec2(500, 100));
		CreateFinishButton(false);
		AddGameObject<BCSprite>(L"DPAD_NEXT_UI", Vec3(338.4f, -230, 0), Vec2(281.6f, 140.8f));

		ChangeMode(GameMode::Over);

	}

	void GameStage::OpenMenu() {
		ChangeMode(GameMode::Menu);
		Button::SetActive(true);
		m_MenuBackGround->GetComponent<SpriteBaseDraw>()->SetDrawActive(true);
		m_MenuText->GetComponent<SpriteBaseDraw>()->SetDrawActive(true);
	}

	void GameStage::CloseMenu() {
		ChangeMode(GetBeforeMode());
		Button::SetActive(false);
		m_MenuBackGround->GetComponent<SpriteBaseDraw>()->SetDrawActive(false);
		m_MenuText->GetComponent<SpriteBaseDraw>()->SetDrawActive(false);
	}
}
//end basecross
