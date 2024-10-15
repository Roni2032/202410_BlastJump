/*!
@file MovementComponents.h
@brief ˆÚ“®—p
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Movement : public Component {
		Vec3 m_targetPosition;
		vector<Vec3> m_targetList;
		float m_speed;
	public:
		explicit Movement(const shared_ptr<GameObject>& ObjPtr) : Movement(ObjPtr,5,{}) {}
		explicit Movement(const shared_ptr<GameObject>& ObjPtr,float speed) :Movement(ObjPtr, speed, {}) {}
		explicit Movement(const shared_ptr<GameObject>& ObjPtr,vector<Vec3> targetList) :Movement(ObjPtr, 5, targetList) {}

		explicit Movement(const shared_ptr<GameObject>& ObjPtr,float speed,vector<Vec3> targetList) :Component(ObjPtr),m_speed(speed),m_targetList(targetList) {}

		virtual ~Movement() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override {}

		void AddTarget(int order, Vec3 pos);
		void AddTarget(Vec3 pos);

		void SetSpeed(float speed);
	};

}
//end basecross
