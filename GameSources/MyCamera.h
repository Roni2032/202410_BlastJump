/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class MyCamera : public Camera {
		float m_HighY;
		weak_ptr<Transform> m_player;
	public:
		MyCamera():Camera(),m_HighY(0){}
		virtual ~MyCamera(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetPlayer(weak_ptr<GameObject>& player);
	};
}
//end basecross
