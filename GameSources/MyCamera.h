/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class OutOfCameraPlayerPos;

	class MyCamera : public Camera {
		int m_CameraWidth;
		int m_CameraHight;
		float m_ScrollSpeed;

		float m_DefaultFovY;
		float m_SkipY;
		shared_ptr<Sprite> m_Fade;

		Vec3 m_StartAt;
		Vec3 m_StartEye;
		weak_ptr<Transform> m_player;

		shared_ptr<GameStage> m_Stage;

		shared_ptr<OutOfCameraPlayerPos> m_PlayerPosArrow;
	public:
		MyCamera(const shared_ptr<GameStage>& ptr,const float scrollSpeed):
			Camera(),
			m_CameraHight(9),m_CameraWidth(14),
			m_Stage(ptr),
			m_ScrollSpeed(scrollSpeed),
			m_StartAt(0.0f),
			m_StartEye(0.0f),
			m_DefaultFovY(15.0f),
			m_SkipY(0.0f)
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
		void RespawnCamera();
	};

	class OutOfCameraPlayerPos : public GameObject {
		shared_ptr<Transform> m_Trans;
	public:
		OutOfCameraPlayerPos(shared_ptr<Stage>& ptr) : GameObject(ptr){}
		virtual ~OutOfCameraPlayerPos(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override{}

		void Draw(Vec2 pos,float dir);
		void UnDraw() {
			SetDrawActive(false);
		}
	};
}
//end basecross
