/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Goal : public GameObject {
	public:
		Goal(const shared_ptr<Stage>& ptr) : GameObject(ptr){}
		virtual ~ Goal(){}

		virtual void OnCreate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};

	class CheckPoint : public GameObject {

	public:
		CheckPoint(const shared_ptr<Stage>& ptr) : GameObject(ptr) {}
		virtual ~CheckPoint() {}

		virtual void OnCreate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};
}
//end basecross
