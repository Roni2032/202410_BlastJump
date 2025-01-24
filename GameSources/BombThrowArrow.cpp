/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void BombThrowArrow::OnCreate() {
		m_Draw = AddComponent<PNTStaticDraw>();
		m_Draw->SetMeshResource(L"DEFAULT_SQUARE");
		m_Draw->SetTextureResource(L"BOMB_THROW_TEX");
		SetAlphaActive(true);

		m_Trans = GetComponent<Transform>();
		auto player = m_player.lock();
		if (player != nullptr) {
			m_Trans->SetParent(player);
			m_Trans->SetPosition(0, 2, 0);
		}
	}

	void BombThrowArrow::OnUpdate() {
		auto gPlayer = m_player.lock();
		if (gPlayer != nullptr) {
			auto player = static_pointer_cast<Player>(gPlayer);
			if (player == nullptr) return;
			Vec3 throwVec = player->GetBombVec().normalize();
			if (throwVec.length() != 0) {
				if (!m_Draw->GetDrawActive()) {
					m_Draw->SetDrawActive(true);
				}
				float rad = atan2f(-throwVec.x, throwVec.y);
				m_Trans->SetPosition(Vec3(0,0,-1) + throwVec);
				m_Trans->SetRotation(Vec3(0,0,rad));
			}
			else {
				m_Draw->SetDrawActive(false);
			}
		}
	}

	void BombThrowOrbit::OnCreate() {
		auto draw = AddComponent<PNTStaticInstanceDraw>();
		draw->SetMeshResource(L"DEFAULT_SQUARE");
		draw->ClearMatrixVec();
		m_Trans = GetComponent<Transform>();
	}

	void BombThrowOrbit::OnUpdate() {
		auto draw = GetComponent<PNTStaticInstanceDraw>();

		draw->ClearMatrixVec();
		float renderTime = 1.0f / m_OrbitNum;
		Vec3 bombGravity = Vec3(0, - 9.8f,0);
		auto player = m_player.lock();
		Vec3 firstVelocity = Vec3(0);
		bool isHit = false;
		if (player != nullptr) {
			firstVelocity = player->GetBombVec();
			if (firstVelocity.length() == 0) return;
			for (int i = 0; i < m_OrbitNum; i++) {
				float time = renderTime * i;
				
				Vec3 pos = firstVelocity * time + bombGravity * (time * time) / 2.0f;
				pos.z -= 0.5f;
				time += renderTime;
				Vec3 nextPos = firstVelocity * time + bombGravity * (time * time) / 2.0f;

				Vec3 diff = nextPos - pos;
				diff = diff.normalize();

				float rad = atan2f(-diff.x, diff.y);

				Vec3 worldPos = pos + player->GetComponent<Transform>()->GetWorldPosition() + Vec3(0.0f,0.7f,0.0f);
				Mat4x4 matrix;
				matrix.affineTransformation(
					Vec3(0.1f),
					Vec3(0),
					Vec3(0,0,rad),
					worldPos
				);
				draw->AddMatrix(matrix);

				
				float bombRadius = 0.25f;
				vector<shared_ptr<GameObject>> findObj;
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						auto obj = GetTypeStage<GameStage>()->GetBlock(worldPos + Vec3(j, i, 0));
						if (obj != nullptr) {
							findObj.push_back(obj);
						}
					}
				}
				bool isCollision = false;
				for (auto obj : findObj) {
					if (obj->GetComponent<Collision>(false) == nullptr) continue;
					auto objTrans = obj->GetComponent<Transform>();
					Vec3 objPos = objTrans->GetPosition();
					Vec3 objScale = objTrans->GetScale();

					if (abs(objPos.x - worldPos.x) < bombRadius + objScale.x / 2.0f &&
						abs(objPos.y - worldPos.y) < bombRadius + objScale.y / 2.0f) {
						isCollision = true;
						break;
					}
				}
				if (isCollision) break;
			}
		}
	}

}
//end basecross
