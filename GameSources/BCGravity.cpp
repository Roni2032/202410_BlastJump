/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void BCGravity::OnCreate() {

	}
	void BCGravity::OnUpdate() {
		
		auto objPtr = GetGameObject();
		auto objTrans = objPtr->GetComponent<Transform>();

		Vec3 objPos = objTrans->GetPosition();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		
		m_Velocity += m_GravitySpeed * elapsedTime;
		
		objPos += m_Velocity * elapsedTime;
		
		objTrans->SetPosition(objPos);


		switch (m_GravityDirection) {
		case GRAVITY::X:
			if (m_Velocity.x <= m_GravitySpeed.x) {
				m_Velocity.x = m_GravitySpeed.x;
			}
		case GRAVITY::Y:
			if (m_Velocity.y <= m_GravitySpeed.y) {
				m_Velocity.y = m_GravitySpeed.y;
			}
			break;
		case GRAVITY::Z:
			if (m_Velocity.z <= m_GravitySpeed.z) {
				m_Velocity.z = m_GravitySpeed.z;
			}
			break;
		}
		
		
	}
}
//end basecross
