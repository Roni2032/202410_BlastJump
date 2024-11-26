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

	void Orbit::OnCreate() {
		m_Draw = AddComponent<PNTStaticDraw>();
		m_Draw->SetMeshResource(L"DEFAULT_SQUARE");
		//m_Draw->SetTextureResource(L"BOMB_THROW_TEX");
		m_Draw->SetDiffuse(Col4(1, 1, 1, 1));
		SetAlphaActive(true);

		m_Trans = GetComponent<Transform>();
		m_Trans->SetScale(Vec3(0.1f));
		
	}
	void Orbit::SetPosition(Vec3 pos) {
		m_Trans->SetPosition(pos);
	}
	void Orbit::OnUpdate() {
		
	}

	void BombThrowOrbit::OnCreate() {
		m_Trans = GetComponent<Transform>();
		auto player = m_player.lock();
		if (player != nullptr) {
			for (int i = 0; i < m_OrbitNum; i++) {
				auto orbit = GetStage()->AddGameObject<Orbit>();
				orbit->GetComponent<Transform>()->SetParent(player);
				m_Orbits.push_back(orbit);
			}
			m_Trans->SetParent(player);
		}
		
	}

	void BombThrowOrbit::OnUpdate() {
		float renderTime = 1.0f / m_Orbits.size();
		Vec3 bombGravity = Vec3(0, - 9.8f,0);
		auto player = m_player.lock();
		Vec3 firstVelocity = Vec3(0);
		bool isHit = false;
		if (player != nullptr) {
			firstVelocity = player->GetBombVec();

			for (int i = 0; i < m_Orbits.size(); i++) {
				float time = renderTime * i;
				if (firstVelocity.length() == 0 || isHit) {
					m_Orbits[i]->SetDrawActive(false);
					continue;
				}
				else {
					m_Orbits[i]->SetDrawActive(true);
				}
				Vec3 pos = firstVelocity * time + bombGravity * (time * time) / 2.0f;
				
				m_Orbits[i]->SetPosition(pos);
				/*Vec3 worldPos = m_Orbits[i]->GetComponent<Transform>()->GetWorldPosition();

				if (GetTypeStage<GameStage>()->GetBlock(worldPos) != 0) {
					isHit = true;
				}*/
			}
		}
	}

}
//end basecross
