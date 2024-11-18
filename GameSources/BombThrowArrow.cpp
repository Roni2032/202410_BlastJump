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
			//player->SetBombVec(Vec3(cos(testDeg),sin(testDeg),0));
			//testDeg += XM_PIDIV2 / 60.0f;
			Vec3 throwVec = player->GetBombVec().normalize();
			if (throwVec.length() != 0) {
				if (!m_Draw->GetDrawActive()) {
					m_Draw->SetDrawActive(true);
				}
				float rad = atan2f(-throwVec.x, throwVec.y);
				m_Trans->SetPosition(throwVec);
				m_Trans->SetRotation(Vec3(0,0,rad));
			}
			else {
				m_Draw->SetDrawActive(false);
			}
		}
	}

}
//end basecross
