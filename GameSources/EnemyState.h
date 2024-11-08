/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	template<class type>
	class State {
	public:
		virtual void Enter(shared_ptr<type>&){}
		virtual void Execute(shared_ptr<type>&){}
		virtual void Exit(shared_ptr<type>&){}
	};


	class JumpToNextFloor : public State<TrackingEnemy> {
		float m_MoveInterval;
		float m_Timer;
	public:
		virtual void Enter(shared_ptr<TrackingEnemy>& enemy);
		virtual void Execute(shared_ptr<TrackingEnemy>& enemy);
		virtual void Exit(shared_ptr<TrackingEnemy>& enemy);
	};

	class WalkToJumpPoint : public State<TrackingEnemy> {
		float speed;
		Vec3 targetPos;
	public:
		virtual void Enter(shared_ptr<TrackingEnemy>& enemy);
		virtual void Execute(shared_ptr<TrackingEnemy>& enemy);
		virtual void Exit(shared_ptr<TrackingEnemy>& enemy);
	};
}
//end basecross
