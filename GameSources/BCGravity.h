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
		float m_DefaultGravity;
		
	public:
		enum GRAVITY {
			X, Y, Z
		};
		GRAVITY m_GravityDirection;
		BCGravity(const shared_ptr<GameObject>& ptr, const float gravity = -9.8f) :
			Component(ptr),
			m_GravitySpeed(0,gravity,0),m_DefaultGravity(gravity),
			m_Velocity(0, 0, 0),m_GravityDirection(GRAVITY::Y) {}
		virtual ~BCGravity() {}

		virtual void OnCreate() override;
		virtual void OnUpdate();
		virtual void OnDraw() override {}

		void Jump(Vec3 jumpSpeed) {
			m_Velocity = jumpSpeed;
		}
		void SetDirection(GRAVITY direction) {
			switch (direction) {
			case GRAVITY::X:
				m_GravitySpeed = Vec3(m_DefaultGravity, 0,0);
				break;
			case GRAVITY::Y:
				m_GravitySpeed = Vec3(0, m_DefaultGravity, 0);
				break;
			case GRAVITY::Z:
				m_GravitySpeed = Vec3(0, 0,m_DefaultGravity);
				break;
			}
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
