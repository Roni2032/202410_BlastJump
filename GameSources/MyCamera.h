/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class MyCamera : public Camera {
		weak_ptr<Transform> m_player;
	public:
		MyCamera():Camera(){}
		virtual ~MyCamera(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetPlayer(weak_ptr<GameObject>& player);
	};
}
//end basecross
