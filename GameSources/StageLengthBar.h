/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class StageLengthBar : public GameObject {
		const float BAR_MIN_POSITION_Y = 150.0f;
		const float BAR_MAX_POSITION_Y = 350.0f;
		float m_StageLength;
		float m_BarLength;
		weak_ptr<GameObject> m_Player;
		weak_ptr<GameObject> m_Goal;
		
		shared_ptr<BCSprite> m_PlayerSprite;
		shared_ptr<BCSprite> m_GoalSprite;
		wstring m_BarTexKey;
		wstring m_PlayerTexKey;
		wstring m_GoalTexKey;
	public:
		StageLengthBar(const shared_ptr<Stage>& ptr,float length,const shared_ptr<GameObject>& player,const shared_ptr<GameObject>& goal):
			GameObject(ptr),
			m_StageLength(length),
			m_Player(player),m_Goal(goal)
		{}
		virtual ~StageLengthBar(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetBarLength(float length) {
			m_BarLength = length;
		}
	};
}
//end basecross
