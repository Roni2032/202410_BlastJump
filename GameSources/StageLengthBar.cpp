/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void StageLengthBar::OnCreate() {
		m_PlayerSprite = GetStage()->AddGameObject<BCSprite>(L"ARROW_ORBIT_TEX", Vec3(525.0f,BAR_MIN_POSITION_Y + 25.0f,0), Vec2(25, 25));
		//m_GoalSprite = GetStage()->AddGameObject<BCSprite>(L"GOAL_SYMBLE_UI", Vec3(480.0f,BAR_MAX_POSITION_Y,0), Vec2(50, 50));

		GetStage()->AddGameObject<BCSprite>(L"HEIGHT_BAR_UI", Vec3(550.0f,BAR_MAX_POSITION_Y,0), Vec2(50, 200));
		m_BarLength = 200.0f;
	}
	void StageLengthBar::OnUpdate() {
		auto player = m_Player.lock();
		auto goal = m_Goal.lock();
		if (player == nullptr || goal == nullptr) return;

		auto playerTrans = player->GetComponent<Transform>();
		auto goalTrans = goal->GetComponent<Transform>();

		Vec3 playerPos = playerTrans->GetWorldPosition();
		Vec3 goalPos = goalTrans->GetWorldPosition();

		float diffY = goalPos.y - playerPos.y;

		float percent = (m_StageLength - diffY) / m_StageLength;

		m_PlayerSprite->SetPos(Vec3(525.0f,BAR_MIN_POSITION_Y + m_BarLength * percent,0));
	}
}
//end basecross
