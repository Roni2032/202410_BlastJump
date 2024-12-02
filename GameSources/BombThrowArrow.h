/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player;

	class BombThrowArrow : public GameObject {
		weak_ptr<GameObject> m_player;
		shared_ptr<Transform> m_Trans;
		shared_ptr<PNTStaticDraw> m_Draw;

		float testDeg = 0;
	public:
		BombThrowArrow(const shared_ptr<Stage>& ptr,shared_ptr<GameObject> player) : GameObject(ptr),m_player(player){}
		virtual ~BombThrowArrow(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	class Orbit : public GameObject {
		shared_ptr<PNTStaticDraw> m_Draw;
		shared_ptr<Transform> m_Trans;

	public:
		Orbit(const shared_ptr<Stage>& ptr) : GameObject(ptr) {}
		virtual ~Orbit() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetPosition(Vec3 pos);
	};
	class BombThrowOrbit : public GameObject {
		weak_ptr<Player> m_player;
		shared_ptr<Transform> m_Trans;
		vector<shared_ptr<Orbit>> m_Orbits;
		int m_OrbitNum;
	public:
		BombThrowOrbit(const shared_ptr<Stage>& ptr, shared_ptr<Player> player,const int& num = 10) :
			GameObject(ptr), m_player(player),m_OrbitNum(num) {}
		virtual ~BombThrowOrbit() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
