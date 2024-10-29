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
	void InstanceBlock::DrawMap() {
		for (int i = 0; i < m_Maps.size();i++) {
			for (int j = 0; j < m_Maps[i].size(); j++) {
				if (m_Maps[i][j] == 0) continue;

				float x = m_StartPos.x + j;
				float y = m_StartPos.y - i;

				Mat4x4 matrix;
				matrix.translation(Vec3(x, y, 0));

				m_Draw->AddMatrix(matrix);
			}
		}
	}
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
		//col->SetDrawActive(true);
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
