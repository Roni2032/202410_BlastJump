/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void JumpToNextFloor::Enter(shared_ptr<TrackingEnemy>& enemy) {

	}
	void JumpToNextFloor::Execute(shared_ptr<TrackingEnemy>& enemy) {
		float elapsed = App::GetApp()->GetElapsedTime();
		m_Timer += elapsed;
		if (m_Timer > m_MoveInterval) {
			//�s��

			m_Timer = 0;
		}
	}
	void JumpToNextFloor::Exit(shared_ptr<TrackingEnemy>& enemy) {

	}


	void WalkToJumpPoint::Enter(shared_ptr<TrackingEnemy>& enemy) {

	}
	void WalkToJumpPoint::Execute(shared_ptr<TrackingEnemy>& enemy) {
		float elapsed = App::GetApp()->GetElapsedTime();
		auto trans = enemy->GetComponent<Transform>();

		Vec3 direction = targetPos - trans->GetPosition();
		direction = direction.normalize();

		Vec3 pos = trans->GetPosition();
		pos.x += direction.x * speed * elapsed;
		if ((targetPos - pos).length() < 0.2f) {
			pos = targetPos; 
			trans->SetPosition(pos);
			//�X�e�[�g�ڍs

		}
		trans->SetPosition(pos);
	}
	void WalkToJumpPoint::Exit(shared_ptr<TrackingEnemy>& enemy) {

	}
}
//end basecross
