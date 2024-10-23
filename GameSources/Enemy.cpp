/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr,
		const Vec3& Position,
		const Vec3& Scale
	) :
		GameObject(StagePtr),
		m_pos(Position),
		m_scale(Scale),
		m_MeshName(L"DEFAULT_CAPSULE"),
		m_hp(0),
		m_speed(3.0f),
		m_velo1(1.0f, 0.0f, 0.0f),
		m_velo2(0.0f, 0.0f, 1.0f)
	{}

	void Enemy::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		//m_ptrTrans->SetScale(Vec3(1.0f));
		m_ptrTrans->SetPosition(Vec3(0.0f,3.0f,0.0f));

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(m_MeshName);

		//m_ptrShadow->SetMeshResource(m_MeshName);
		
		//当たり判定(仮)
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetDrawActive(true);
		//重力適用
		//auto Gra = AddComponent<Gravity>();

		m_StateEnemy.reset(new StateMachine<Enemy>(GetThis<Enemy>()));
		m_StateEnemy->ChangeState(SearchFarState::Instance());
	}

	void Enemy::OnUpdate() {
		/*auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();*/
		m_StateEnemy->Update();
		/*if (m_hp = 0)
		{
			OnDestroy();
		}*/
		//Move();
	}

	void Enemy::Move() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//マップの情報を取得	
		auto& MapVec = m_Csvmap.GetCsvVec();
		//自分の進行方向の下のセルを持って来る
		m_forward = m_ptrTrans->GetForward();

		//落ちる前に進行方向を変えるため

		auto thisPos = m_ptrTrans->GetPosition();
		m_velo1.normalize();
		thisPos += m_velo1 * m_speed * delta;
		m_ptrTrans->SetPosition(thisPos);
	}
	shared_ptr<SearchFarState> SearchFarState::Instance() {
		static shared_ptr<SearchFarState> instance(new SearchFarState);
		return instance;
	}
	void SearchFarState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void SearchFarState::Execute(const shared_ptr<Enemy>& Obj) {
		Obj->Move();
	}
	void SearchFarState::Exit(const shared_ptr<Enemy>& Obj) {
	}

}

//end basecross

