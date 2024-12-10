/*!
@file FloorBlock.cpp
@brief 地面の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void InstanceBlock::OnCreate() {
		m_Draw = AddComponent<PNTStaticInstanceDraw>();
		m_Draw->SetMeshResource(L"DEFAULT_CUBE");
		m_Draw->SetTextureResource(m_TexKey);

		m_Maps.reserve(m_SizeY);
		for (int i = 0; i < m_SizeY; i++) {
			m_Maps.push_back({});
		}
	}
	void InstanceBlock::AddBlock(int y, int cell) {
		if (y >= m_SizeY) return;
		m_Maps[y].push_back(cell);
	}
	void InstanceBlock::DrawMap(vector<vector<BlockData>>& map, Vec2 drawSize, Vec3 leftTop) {
		auto stage = GetTypeStage<GameStage>();
		m_Camera = OnGetDrawCamera();
		Vec3 at = stage->GetMapIndex(m_Camera->GetAt());

		float drawIndexMinY = at.y - drawSize.y;
		float drawIndexMaxY = at.y + drawSize.y;

		if (drawIndexMinY < 0) {
			drawIndexMinY = 0;
		}
		if (drawIndexMaxY >= map.size()) {
			drawIndexMaxY = map.size() - 1;
		}
		
		drawSize.x = map[0].size();

		m_Draw->ClearMatrixVec();
		for (int y = drawIndexMinY; y <= drawIndexMaxY; y++) {
			for (int x = 0; x < drawSize.x; x++) {
				if (map[y][x].GetID() != 2) continue;

				Mat4x4 matrix;
				matrix.translation(stage->GetWorldPosition(Vec2(x, y)));

				m_Draw->AddMatrix(matrix);

				if (map[y][x].GetIsLoaded()) continue;
				map[y][x].SetIsLoaded(true);

				bool isCollider = false;
				Vec2 aroundMap[] = {
					Vec2(x + 1,y),
					Vec2(x - 1,y),
					Vec2(x,y + 1),
					Vec2(x,y - 1)
				};
				for (Vec2 around : aroundMap) {
					if (around.x < 0 || around.x >= map[y].size()) continue;
					if (around.y < 0 || around.y >= map.size()) continue;

					if (map[static_cast<int>(around.y)][static_cast<int>(around.x)].GetID() != 2) {
						isCollider = true;
						break;
					}
				}

				if (isCollider) {
					auto obj = GetStage()->AddGameObject<Block>(L"", stage->GetWorldPosition(Vec2(x,y)), Vec3(1.0f));
					GetTypeStage<GameStage>()->RegisterBlock(Vec2(x, y), obj);
				}
			}
		}

		for (int y = 0; y < map.size(); y++) {
			for (int x = 0; x < map[y].size(); x++) {
				if (!map[y][x].GetIsLoaded()) continue;

				if (y < drawIndexMinY || y > drawIndexMaxY) {
					stage->RemoveGameObject<GameObject>(map[y][x].GetBlock());
					map[y][x].SetIsLoaded(false);
				}
			}
		}
	}
	void InstanceBlock::DrawMap(const Vec2 max, const Vec2 min) {
		Vec2 drawSize(0);
		Vec2 minCell = min;

		bool isCollision = true;
		if (max.length() == 0) {
			drawSize.x = static_cast<float>(m_Maps[0].size());
			drawSize.y = static_cast<float>(m_Maps.size());
			isCollision = false;
		}
		else {
			drawSize = max;
		}
		if (minCell.y < 0) {
			minCell.y = 0;
		}

		float cameraHight = m_Camera->GetHeight();
		float atY = m_Camera->GetAt().y;

		m_Draw->ClearMatrixVec();
		for (int i = minCell.y; i <= drawSize.y;i++) {
			for (int j = 0; j < drawSize.x; j++) {
				if (m_Maps[m_Maps.size() - i - 1][j] == 0) continue;

				float x = m_StartPos.x + j;
				float y = static_cast<float>(i) ;

				y = floor(y, 0);

				Mat4x4 matrix;
				matrix.translation(Vec3(x, y, 0));

				m_Draw->AddMatrix(matrix);
				
			}
		}
		if (!isCollision) return;
		/*int objectCount = m_CollisionObjects.size();
		for (const auto& matrix : m_Draw->GetMatrixVec()) {
			Vec3 translation = matrix.getTranslation();
			if (m_CameraAtY + cameraHight < translation.y || m_CameraAtY - cameraHight > translation.y || objectCount == 0) {
				Vec2 index = Vec2(translation.x - m_StartPos.x, m_StartPos.y - translation.y);
				index = index.floor(0);

				bool isCollider = false;

				Vec2 aroundMap[] = {
					Vec2(index.x + 1,m_Maps.size() - index.y - 1),
					Vec2(index.x - 1,m_Maps.size() - index.y - 1),
					Vec2(index.x,m_Maps.size() - index.y),
					Vec2(index.x,m_Maps.size() - index.y - 2)
				};
				for (Vec2 around : aroundMap) {
					if (around.x < 0 || around.x >= m_Maps[index.y].size()) continue;
					if (around.y < 0 || around.y >= m_Maps.size()) continue;

					if (m_Maps[around.y][around.x] == 0) {
						isCollider = true;
						break;
					}
				}

				if (isCollider) {
					m_CollisionObjects.push_back(GetStage()->AddGameObject<Block>(L"", translation, Vec3(1.0f)));
				}
			}
		}*/
		for (int i = m_DrawMaxHeight + 1/*m_CameraAtY + cameraHight + 1*/; i <= max.y; i++) {
			for (int j = 0; j < drawSize.x; j++) {
				if (m_Maps[m_Maps.size() - i - 1][j] == 0) continue;

				float x = m_StartPos.x + j;
				float y = static_cast<float>(i);

				y = floor(y, 0);

				bool isCollider = false;

				Vec2 aroundMap[] = {
					Vec2(j + 1,m_Maps.size() - i - 1),
					Vec2(j - 1,m_Maps.size() - i - 1),
					Vec2(j,m_Maps.size() - i),
					Vec2(j,m_Maps.size() - i - 2)
				};
				for (Vec2 around : aroundMap) {
					if (around.x < 0 || around.x >= m_Maps[i].size()) continue;
					if (around.y < 0 || around.y >= m_Maps.size()) continue;

					if (m_Maps[static_cast<int>(around.y)][static_cast<int>(around.x)] == 0) {
						isCollider = true;
						break;
					}
				}

				if (isCollider) {
					auto obj = GetStage()->AddGameObject<Block>(L"", Vec3(x, y, 0), Vec3(1.0f));
					GetTypeStage<GameStage>()->RegisterBlock(Vec2(j, i), obj);
					m_CollisionObjects.push_back(obj);
				}
			}
		}

		m_DrawMaxHeight = max.y;
		m_CameraAtY = atY;
		for (int i = 0; i < m_CollisionObjects.size();i++) {
			auto trans = m_CollisionObjects[i]->GetComponent<Transform>();
			if (trans->GetPosition().y < minCell.y) {
				GetStage()->RemoveGameObject<GameObject>(m_CollisionObjects[i]);
				m_CollisionObjects.erase(m_CollisionObjects.begin() + i);
			}
			if (trans->GetPosition().y > max.y) {
				GetStage()->RemoveGameObject<GameObject>(m_CollisionObjects[i]);
				m_CollisionObjects.erase(m_CollisionObjects.begin() + i);
			}
		}
	}

	vector<weak_ptr<Transform>> Block::CollisionObjects = {};

	void Block::OnCreate() {
		if (m_TexKey == L"" || m_TexKey == L"null") {
			
		}
		else {
			auto drawComp = AddComponent<BcPNTStaticDraw>();
			drawComp->SetMeshResource(L"DEFAULT_CUBE");
			drawComp->SetTextureResource(m_TexKey);
			drawComp->SetDiffuse(Col4(1, 1, 1, 1));
			//モデルの設定
		}

		auto col = AddComponent<CollisionObb>();
		col->SetFixed(true);
		col->SetDrawActive(true);
		
		AddTag(L"Stage");

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_Pos);
		trans->SetScale(m_Scale);
		trans->SetRotation(m_Rot);

		Start();
	}

	void Block::OnUpdate() {
		Update();
		GetComponent<Transform>()->SetScale(1, 1, 1);
	}
	void Block::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto col = Other->GetComponent<Collision>(false);
		if (col != nullptr) {
			if (col->GetAfterCollision() != AfterCollision::Auto) return;

		}
	}
	void Block::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		auto col = Other->GetComponent<Collision>(false);
		if (col != nullptr) {
			if (col->GetAfterCollision() != AfterCollision::Auto) return;

		}
	}
		
	void FloorBlock::Start() {
		AddTag(L"Floor");
		CheckDurability();
	}
	void FloorBlock::Update() {

	}
	void FloorBlock::HitExplode(int damage) {
		m_Durability -= damage;

		CheckDurability();
		if (m_Durability <= 0) {
			GetTypeStage<GameStage>()->DestroyBlock(GetComponent<Transform>()->GetPosition(), GetThis<GameObject>());
			//GetTypeStage<GameStage>()->PlayParticle<BlockDestroyParticle>(L"DESTROY_BLOCK_PCL", GetComponent<Transform>()->GetPosition());
		}
	}

	void FloorBlock::CheckDurability() {
		auto drawComp = GetComponent<BcPNTStaticDraw>();
		if (m_Durability <= 25) {
			drawComp->SetTextureResource(L"TEST25_TEX");
		}
		else if (m_Durability <= 50) {
			drawComp->SetTextureResource(L"TEST50_TEX");
		}
		else if(m_Durability <= 75){
			drawComp->SetTextureResource(L"TEST75_TEX");
		}
		else {
			drawComp->SetTextureResource(L"TEST100_TEX");
		}
	}

	void MoveBlock::Start() {
		Block::Start();

		m_Trans = GetComponent<Transform>();

		m_TargetPos = m_MoveStartPos;
	}

	void MoveBlock::Update() {
		Block::Update();

		float elapsed = App::GetApp()->GetElapsedTime();
		Vec3 pos = m_Trans->GetPosition();
		Vec3 velocity = m_TargetPos - pos;
		velocity = velocity.normalize();

		pos += m_MoveSpeed * velocity * elapsed;

		if ((m_TargetPos - pos).length() < 0.05f) {
			pos = m_TargetPos;

			m_TargetPos = m_TargetPos == m_MoveStartPos ? m_MoveEndPos : m_MoveStartPos;
		}
		m_Trans->SetPosition(pos);
	}

	void MoveBlock::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		Block::OnCollisionEnter(Other);
		if (Other->FindTag(L"Player")) {
			Other->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
		}
	}
	void MoveBlock::OnCollisionExit(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			Other->GetComponent<Transform>()->SetParent(nullptr);
		}
	}

	void ExplodeBlock::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			auto stage = GetTypeStage<GameStage>();
			stage->AddGameObject<ExplodeCollider>(GetComponent<Transform>()->GetWorldPosition() - Vec3(0,0.5f,0), Explosion(m_Power, m_Range), Other);

			auto otherCol = Other->GetComponent<BCCollisionObb>();
			Vec3 diff = Vec3();
			if (otherCol != nullptr) {
				auto data = otherCol->GetCollisionData(GetThis<GameObject>());
				switch (data.hitDir) {
				case HitDir::Up:
					diff = Vec3(0, 0.5f, 0);
					break;
				case HitDir::Down:
					diff = Vec3(0, -0.5f, 0);
					break;
				case HitDir::Right:
					diff = Vec3(0.5f, 0, 0);
					break;
				case HitDir::Left:
					diff = Vec3(-0.5f, 0, 0);
					break;

				}
			}
			stage->PlayParticle<ExplodeParticle>(L"EXPLODE_PCL", GetComponent<Transform>()->GetWorldPosition() + diff);

			SoundManager::Instance().PlaySE(L"BOMB_SD", 0.1f);

			//プレイヤーをスタン状態にする

		}
	}

	void ConditionalMoveBlock::Start() {
		MoveBlock::Start();
	}

	void ConditionalMoveBlock::Update() {
		bool isFunc = m_Func(GetTypeStage<GameStage>());
		if (isFunc) {
			MoveBlock::Update();
		}

		float elapsed = App::GetApp()->GetElapsedTime();
		
	}
}
//end basecross
