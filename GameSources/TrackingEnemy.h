/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class TrackingEnemy : public GameObject {

	public:
		TrackingEnemy(const shared_ptr<Stage>& ptr) :
			GameObject(ptr)
		{}
		virtual ~TrackingEnemy() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
	
}
//end basecross
