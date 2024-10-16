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
	public:
		Bomb(const shared_ptr<Stage>& ptr) : 
			GameObject(ptr),
			m_ExplodeTime(2.0f),m_ExplodeTimer(0.0f),
			m_ExplodeRange(3.0f),m_ExplodePower(3.0f)
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
	public:
		ExplodeCollider(const shared_ptr<Stage>& ptr,Vec3 pos,const shared_ptr<Bomb>& bomb):
			GameObject(ptr),
			m_Pos(pos),
			m_Bomb(bomb),
			m_Tick(0)
		{}

		virtual ~ExplodeCollider() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};
}
//end basecross
