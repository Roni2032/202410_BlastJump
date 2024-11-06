/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class MyCamera : public Camera {
		float m_HighY;
		int m_CameraWidth;
		int m_CameraHight;

		weak_ptr<Transform> m_player;

		shared_ptr<GameStage> m_Stage;
	public:
		MyCamera(const shared_ptr<GameStage>& ptr):
			Camera(),
			m_HighY(0),m_CameraHight(9),m_CameraWidth(14),
			m_Stage(ptr){}
		virtual ~MyCamera(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetPlayer(weak_ptr<Player> player);
	};
}
//end basecross
