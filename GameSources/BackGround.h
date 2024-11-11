/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class BackGround : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Pos;
	public:
		BackGround(const shared_ptr<Stage>& ptr,Vec3 pos,Vec3 scale) : GameObject(ptr),m_Pos(pos),m_Scale(scale){}
		virtual ~BackGround(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetActive(bool flag);
	};

	class BackGroundManager : public GameObject {
		vector<shared_ptr<BackGround>> m_BackGrounds;
		weak_ptr<Camera> m_Camera;

		float m_LoopDistance;
	public:
		BackGroundManager(const shared_ptr<Stage>& ptr,float distance) : GameObject(ptr),m_LoopDistance(distance) {}
		virtual ~BackGroundManager() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
