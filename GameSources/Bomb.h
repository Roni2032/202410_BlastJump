/*!
@file Bomb.h
@brief ”š’e
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	
	struct Explosion {
		float m_Power;
		float m_Range;

		Explosion() : Explosion(0, 0){}
		Explosion(float power,float range) : m_Power(power),m_Range(range){}

	};
	class Bomb : public GameObject {
		Vec3 rotateSpeed;
		float m_ExplodeTime;
		float m_ExplodeTimer;

		Explosion m_ExplodeStatus;
		//float m_ExplodeRange;
		//float m_ExplodePower;

		Vec3 m_ThrowVelocity;
		Vec3 m_Pos;
		shared_ptr<GameStage> m_GameStage;
		weak_ptr<GameObject> m_Player;
	public:
		Bomb(const shared_ptr<Stage>& ptr,Vec3 pos) : 
			Bomb(ptr,pos, Vec3(0, 0, 0), 1.0f)
		{}
		Bomb(const shared_ptr<Stage>& ptr, Vec3 pos, Vec3 velocity) :
			Bomb(ptr, pos, velocity, 1.0f)
		{}
		Bomb(const shared_ptr<Stage>& ptr, Vec3 pos, Vec3 velocity, float explodeTime) :
			Bomb(ptr,pos, velocity, explodeTime,3.0f)
		{}
		Bomb(const shared_ptr<Stage>& ptr, Vec3 pos, Vec3 velocity, float explodeTime,float explodeRange) :
			Bomb(ptr,pos, velocity, explodeTime,explodeRange,10.0f)
		{}
		Bomb(const shared_ptr<Stage>& ptr, Vec3 pos, Vec3 velocity, float explodeTime, float explodeRange, float explodePower) :
			GameObject(ptr),
			m_ExplodeTime(explodeTime), m_ExplodeTimer(0.0f),
			//m_ExplodeRange(explodeRange), m_ExplodePower(explodePower),
			m_ExplodeStatus(Explosion(explodePower,explodeRange)),
			m_Pos(pos), m_ThrowVelocity(velocity)
		{}
		virtual ~Bomb(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;

		void Explode();

	};

	class ExplodeCollider : public GameObject {
		//shared_ptr<Bomb> m_Bomb;
		Explosion m_Explosion;
		Vec3 m_Pos;
		int m_Tick;

		float m_MinReboundRate;
	public:
		ExplodeCollider(const shared_ptr<Stage>& ptr,Vec3 pos,Explosion explosion):
			GameObject(ptr),
			m_Pos(pos),
			m_Explosion(explosion), m_MinReboundRate(0.5f),
			m_Tick(0)
		{}

		virtual ~ExplodeCollider() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};
}
//end basecross
