/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Goal : public GameObject {
		Vec3 m_Pos;
	public:
		Goal(const shared_ptr<Stage>& ptr,Vec3 pos) : GameObject(ptr),m_Pos(pos){}
		virtual ~ Goal(){}

		virtual void OnCreate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};

	class CheckPoint : public GameObject {
		Vec3 m_Pos;
	public:
		CheckPoint(const shared_ptr<Stage>& ptr, Vec3 pos) : GameObject(ptr),m_Pos(pos) {}
		virtual ~CheckPoint() {}

		virtual void OnCreate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};
}
//end basecross
