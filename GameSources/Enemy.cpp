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
		m_velo2(-1.0f, 0.0f, 0.0f),
		m_time(0)
	{}

	void Enemy::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_scale);
		m_ptrTrans->SetPosition(m_pos);
		m_forward = m_ptrTrans->GetForward();


		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(m_MeshName);

		//m_ptrShadow->SetMeshResource(m_MeshName);

		//m_velo1.normalize();
		//m_velo2.normalize();
		//当たり判定(仮)
		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetDrawActive(true);
		//重力適用
		auto Gra = AddComponent<BCGravity>();

		m_StateEnemy.reset(new StateMachine<Enemy>(GetThis<Enemy>()));
		m_StateEnemy->ChangeState(SearchFarState::Instance());
	}

	void Enemy::OnUpdate() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		m_time += delta;

		if (m_move)
		{
			m_StateEnemy->Update();
		}
	}

	void Enemy::Move() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		auto thisPos = m_ptrTrans->GetPosition();
		m_velo1.normalize();
		m_velo2.normalize();
		//ブロックの情報を取得
		int block = GetTypeStage<GameStage>()->GetBlock(thisPos + Vec3(m_forward.x, 1.0f, m_forward.z));
		if (block == 0)
		{
			//m_ptrTrans->SetRotation(Vec3(0.0f, 90.0f,0.0f));
			thisPos += m_velo2 * m_speed * delta;
			m_ptrTrans->SetPosition(thisPos);
		}
		if (block == 1) {
			thisPos += m_velo1 * m_speed * delta;
			m_ptrTrans->SetPosition(thisPos); 
		}
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		Other->FindTag(L"Floor");
		m_move = true;
	}
	void Enemy::OnCollisionExit(shared_ptr<GameObject>& Other){
		m_move = false;
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

