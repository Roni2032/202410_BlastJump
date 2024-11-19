/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class BCGravity : public Component {
		Vec3 m_Velocity;
		Vec3 m_GravitySpeed;
	public:
		BCGravity(const shared_ptr<GameObject>& ptr, const float gravity = -9.8f) : Component(ptr), m_GravitySpeed(0,gravity,0), m_Velocity(0, 0, 0) {}
		virtual ~BCGravity() {}

		virtual void OnCreate() override;
		virtual void OnUpdate();
		virtual void OnDraw() override {}

		void Jump(Vec3 jumpSpeed) {
			m_Velocity = jumpSpeed;
		}

		void SetGravity(float gravity) {
			m_GravitySpeed.y = gravity;
		}

		Vec3 GetVelocity() {
			return m_Velocity;
		}
		void SetVelocity(Vec3 velocity) {
			m_Velocity = velocity;
		}
	};
}
//end basecross
