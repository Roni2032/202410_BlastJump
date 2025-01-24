/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class BombItem : public GameObject {
		const int DEFAULT_BOMB_NUM;
		Vec3 m_Pos;
		int m_AddBombNum;
	public:
		BombItem(const shared_ptr<Stage>& ptr,Vec3 pos,const int num = 2) : 
			GameObject(ptr),
			m_Pos(pos),m_AddBombNum(num),DEFAULT_BOMB_NUM(2)
		{}
		virtual ~BombItem(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};

	class AddBombBoard : public GameObject {
		Vec3 m_StartPos;

		float m_DeleteTime;
		float m_DeleteTimer;
	public:
		AddBombBoard(shared_ptr<Stage>& ptr,Vec3 pos) : GameObject(ptr),m_StartPos(pos),m_DeleteTime(1.0f),m_DeleteTimer(0.0f){}
		virtual ~AddBombBoard(){}


		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
