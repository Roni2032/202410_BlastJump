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
		float m_ScrollSpeed;

		Vec3 m_StartAt;
		Vec3 m_StartEye;
		weak_ptr<Transform> m_player;

		shared_ptr<GameStage> m_Stage;
	public:
		MyCamera(const shared_ptr<GameStage>& ptr,const float scrollSpeed):
			Camera(),
			m_HighY(0),m_CameraHight(9),m_CameraWidth(14),
			m_Stage(ptr),
			m_ScrollSpeed(scrollSpeed),
			m_StartAt(0.0f),
			m_StartEye(0.0f)
		{}
		virtual ~MyCamera(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetPlayer(weak_ptr<Player> player);
		void SetStageAt(float hight);
		void SetStartAt(Vec3 at) {
			m_StartAt = at;
		}
		void SetStartEye(Vec3 eye) {
			m_StartEye = eye;
		}
		void StartCamera();
	};
}
//end basecross
