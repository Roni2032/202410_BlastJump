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

		m_Camera = OnGetDrawCamera();
		m_CameraAtY = m_Camera->GetAt().y;
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

		float cameraHight = m_Camera->GetHeight();
		float atY = m_Camera->GetAt().y;

		m_Draw->ClearMatrixVec();
		for (int i = minCell.y; i <= drawSize.y;i++) {
			for (int j = 0; j < drawSize.x; j++) {
				if (m_Maps[m_Maps.size() - i - 1][j] == 0) continue;

				float x = m_StartPos.x + j;
				float y = i;

				y = floor(y, 0);

				Mat4x4 matrix;
				matrix.translation(Vec3(x, y, 0));

				m_Draw->AddMatrix(matrix);
				
			}
		}
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
				float y = i;

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

					if (m_Maps[around.y][around.x] == 0) {
						isCollider = true;
						break;
					}
				}

				if (isCollider) {
					m_CollisionObjects.push_back(GetStage()->AddGameObject<Block>(L"", Vec3(x, y, 0), Vec3(1.0f)));
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
		//col->SetAfterCollision(AfterCollision::None);
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
	void Block::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		return;
		auto col = Other->GetComponent<Collision>(false);
		if (col != nullptr) {
			if (col->GetAfterCollision() != AfterCollision::Auto) return;

			auto otherTrans = Other->GetComponent<Transform>();
			auto trans = GetComponent<Transform>();

			Vec3 otherSize = otherTrans->GetScale();
			Vec3 size = trans->GetScale();

			Vec3 otherPos = otherTrans->GetWorldPosition();
			Vec3 pos = trans->GetPosition();
			Vec3 otherVelocity = otherTrans->GetVelocity();

			float immersion = 10000.0f;
			/*if (pos.x > otherPos.x + otherSize.x) {
				float nneImersion
			}
			else if (pos.x + size.x < otherPos.x) {
				otherPos.x = pos.x;
			}

			if (pos.y + otherSize.y < otherPos.y + otherSize.y) {
				otherPos.y = pos.y - otherSize.y;
			}
			else if (pos.y > otherPos.y + otherSize.y) {
				otherPos.y = pos.y + otherSize.y;
			}*/

			otherTrans->SetPosition(otherPos);
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

	void MoveBlock::Start() {
		FloorBlock::Start();

		m_Trans = GetComponent<Transform>();

		m_TargetPos = m_MoveStartPos;
	}

	void MoveBlock::Update() {
		FloorBlock::Update();

		float elapsed = App::GetApp()->GetElapsedTime();
		Vec3 pos = m_Trans->GetPosition();
		Vec3 velocity = m_TargetPos - pos;
		velocity = velocity.normalize();

		pos += m_MoveSpeed * velocity * elapsed;

		if ((m_TargetPos - pos).length() < 0.1f) {
			pos = m_TargetPos;

			m_TargetPos = m_TargetPos == m_MoveStartPos ? m_MoveEndPos : m_MoveStartPos;
		}
		m_Trans->SetPosition(pos);
	}

	void MoveBlock::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			Other->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
		}
	}
	void MoveBlock::OnCollisionExit(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			Other->GetComponent<Transform>()->SetParent(nullptr);
		}
	}
}
//end basecross
