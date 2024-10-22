/*!
@file Enemy.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {


//---------------------------------------------------- ----------------------------------
//	Enemyクラス
//--------------------------------------------------------------------------------------
	class Enemy :public GameObject {
		wstring m_MeshName;
		shared_ptr<Shadowmap> m_ptrShadow;
		shared_ptr<Transform> m_ptrTrans;
		CsvFile m_Csvmap;
		//hp
		int m_hp;
		//speed
		float m_speed;
		Vec3 m_velo1; 
		Vec3 m_velo2;
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_forward;

	public:
		Enemy(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale);
		virtual ~Enemy() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Move();

		//virtual void On 
	};


}
//end basecross
