/*!
@file Bomb.h
@brief ”š’e
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Bomb : public GameObject {
		float m_ExplodeTime;
		float m_ExplodeTimer;

		float m_ExplodeRange;
		float m_ExplodePower;

		Vec3 m_ThrowVelocity;
		Vec3 m_Pos;
		shared_ptr<GameStage> m_GameStage;
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
			m_ExplodeRange(explodeRange), m_ExplodePower(explodePower),
			m_Pos(pos), m_ThrowVelocity(velocity)
		{}
		virtual ~Bomb(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;

		void Explode();

		float GetRange() {
			return m_ExplodeRange;
		}
		float GetPower() {
			return m_ExplodePower;
		}
	};

	class ExplodeCollider : public GameObject {
		shared_ptr<Bomb> m_Bomb;
		Vec3 m_Pos;
		int m_Tick;

		float m_MinReboundRate;
	public:
		ExplodeCollider(const shared_ptr<Stage>& ptr,Vec3 pos,const shared_ptr<Bomb>& bomb):
			GameObject(ptr),
			m_Pos(pos),
			m_Bomb(bomb), m_MinReboundRate(0.5f),
			m_Tick(0)
		{}

		virtual ~ExplodeCollider() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};
}
//end basecross
