/*!
@file Bomb.cpp
@brief ”š’eŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Bomb::OnCreate() {
		auto drawComp = AddComponent<BcPTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		AddComponent<CollisionSphere>();

		auto gravity = AddComponent<BCGravity>();
		gravity->Jump(m_ThrowVelocity);

		GetComponent<Transform>()->SetPosition(m_Pos);

		m_GameStage = GetTypeStage<GameStageK>();
	}

	void Bomb::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_ExplodeTimer += elapsedTime;

		if (m_ExplodeTimer > m_ExplodeTime) {
			Explode();
		}
	}

	void Bomb::Explode() {
		m_GameStage->AddGameObject<ExplodeCollider>(GetComponent<Transform>()->GetPosition(), GetThis<Bomb>());
		
		//m_GameStage->PlayParticle(L"EXPLODE_PCL", GetComponent<Transform>()->GetPosition());
		
		m_GameStage->RemoveGameObject<Bomb>(GetThis<Bomb>());
	}
	void Bomb::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto otherTrans = Other->GetComponent<Transform>();
		if (Other->FindTag(L"Stage")) {
			//RemoveComponent<Gravity>();
		}

		if (otherTrans->GetPosition().y - otherTrans->GetScale().y >= GetComponent<Transform>()->GetPosition().y) {
			auto gravity = GetComponent<BCGravity>();
			Vec3 velo = gravity->GetVelocity();
			gravity->SetVelocity(Vec3(velo.x, 0, velo.z));
		}
	}


	void ExplodeCollider::OnCreate() {
		auto col = AddComponent<CollisionSphere>();
		col->SetAfterCollision(AfterCollision::None);
		col->SetDrawActive(true);
		auto trans = GetComponent<Transform>();

		trans->SetPosition(m_Pos);
		float range = m_Bomb->GetRange();
		trans->SetScale(Vec3(range,range,range));
	}
	void ExplodeCollider::OnUpdate() {
		GetStage()->RemoveGameObject<ExplodeCollider>(GetThis<ExplodeCollider>());
	}
	void ExplodeCollider::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto otherTrans = Other->GetComponent<Transform>();
		if (Other->FindTag(L"Floor")) {
			auto block = static_pointer_cast<FloorBlock>(Other);
			if (block != nullptr) {
				block->HitExplode(40);
			}
			//int block = GetTypeStage<GameStage>()->GetBlock(otherTrans->GetPosition());
			//GetTypeStage<GameStage>()->DestroyBlock(otherTrans->GetPosition(), Other);
			
		}
		auto gravity = Other->GetComponent<BCGravity>(false);
		if (gravity != nullptr) {
			float range = m_Bomb->GetRange();
			Vec3 otherPos = otherTrans->GetPosition();
			Vec3 ExplodeCorePos = GetComponent<Transform>()->GetPosition();

			Vec3 diff = otherPos - ExplodeCorePos;

			float distance = sqrtf(pow(diff.x, 2) + pow(diff.y, 2));
			float reboundRate = distance / range;
			if (reboundRate < m_MinReboundRate) {
				reboundRate = m_MinReboundRate;
			}
			gravity->Jump(diff.normalize() * reboundRate * m_Bomb->GetPower());
		}

		
	}
}
//end basecross
