/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class BombThrowArrow : public GameObject {
		weak_ptr<GameObject> m_player;
		shared_ptr<Transform> m_Trans;
		shared_ptr<PNTStaticDraw> m_Draw;

		float testDeg = 0;
	public:
		BombThrowArrow(const shared_ptr<Stage>& ptr,shared_ptr<GameObject> player) : GameObject(ptr),m_player(player){}
		virtual ~BombThrowArrow(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
