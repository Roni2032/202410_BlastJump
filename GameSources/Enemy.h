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
		unique_ptr<StateMachine<Enemy>> m_StateEnemy;
		//hp
		int m_hp;
		//speed
		float m_speed;
		Vec3 m_velo1; 
		Vec3 m_velo2;
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_forward;
		float m_StateChangeSize;

	public:
		Enemy(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale);
		virtual ~Enemy() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void Move();

		//ステート系
		const unique_ptr<StateMachine<Enemy>>& GetStateMachine() {
			return m_StateEnemy;
		}
		float GetStateChangesize() const {
			return m_StateChangeSize;
		}

		//virtual void On 
	};

	class SearchFarState : public ObjState<Enemy> {

		SearchFarState() {}
	public:
		static shared_ptr<SearchFarState>Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;

	};
	class SearchNearState : public ObjState<Enemy> {

		SearchNearState() {}
	public:
		static shared_ptr<SearchNearState>Instance();
		virtual void Enter(const shared_ptr<Enemy>& Obj)override;
		virtual void Execute(const shared_ptr<Enemy>& Obj)override;
		virtual void Exit(const shared_ptr<Enemy>& Obj)override;

	};

}
//end basecross

