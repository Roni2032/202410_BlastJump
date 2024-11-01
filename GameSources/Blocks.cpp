/*!
@file FloorBlock.cpp
@brief ínñ ÇÃé¿ëÃ
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
	void InstanceBlock::DrawMap(const Vec2 max, const Vec2 min) {
		Vec2 drawSize(0);
		Vec2 minCell = min;
		if (max.length() == 0) {
			drawSize.x = m_Maps[0].size();
			drawSize.y = m_Maps.size();
		}
		else {
			drawSize = max;
		}
		if (minCell.y < 0) {
			minCell.y = 0;
		}
		m_Draw->ClearMatrixVec();
		for (int i = minCell.y; i < drawSize.y;i++) {
			for (int j = 0; j < drawSize.x; j++) {
				if (m_Maps[m_Maps.size() - i - 1][j] == 0) continue;

				float x = m_StartPos.x + j;
				float y = i;

				Mat4x4 matrix;
				matrix.translation(Vec3(x, y, 0));

				m_Draw->AddMatrix(matrix);
				
			}
		}

		for (int i = m_DrawMaxHeight + 1; i <= max.y; i++) {
			for (int j = 0; j < drawSize.x; j++) {
				if (m_Maps[m_Maps.size() - i - 1][j] == 0) continue;

				float x = m_StartPos.x + j;
				float y = i;

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

					if (m_Maps[around.y][around.x] == 0) {
						isCollider = true;
					}
				}

				if (isCollider) {
					m_CollisionObjects.push_back(GetStage()->AddGameObject<Block>(L"", Vec3(x, y, 0), Vec3(1.0f)));
				}
			}
		}
		m_DrawMaxHeight = max.y;
		for (int i = 0; i < m_CollisionObjects.size();i++) {
			auto trans = m_CollisionObjects[i]->GetComponent<Transform>();
			if (trans->GetPosition().y < minCell.y) {
				GetStage()->RemoveGameObject<GameObject>(m_CollisionObjects[i]);
				m_CollisionObjects.erase(m_CollisionObjects.begin() + i);
			}
		}
	}

	vector<weak_ptr<Transform>> Block::m_MoveObjects = {};

	void Block::OnCreate() {
		if (m_TexKey == L"" || m_TexKey == L"null") {
			
		}
		else {
			auto drawComp = AddComponent<BcPNTStaticDraw>();
			drawComp->SetMeshResource(L"DEFAULT_CUBE");
			drawComp->SetTextureResource(m_TexKey);
			drawComp->SetDiffuse(Col4(1, 1, 1, 1));
			//ÉÇÉfÉãÇÃê›íË
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
		}
	}

	void FloorBlock::CheckDurability() {
		auto drawComp = GetComponent<BcPNTStaticDraw>();
		if (m_Durability < 33) {
			drawComp->SetTextureResource(L"TEST33_TEX");
		}
		else if (m_Durability < 66) {
			drawComp->SetTextureResource(L"TEST66_TEX");
		}
		else {
			drawComp->SetTextureResource(L"TEST100_TEX");
		}
	}
}
//end basecross
