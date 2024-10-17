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

		auto gravity = AddComponent<Gravity>();
		gravity->StartJump(m_ThrowVelocity);
		GetComponent<Transform>()->SetPosition(0, 5, 0);
	}

	void Bomb::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_ExplodeTimer += elapsedTime;

		if (m_ExplodeTimer > m_ExplodeTime) {
			Explode();
		}
	}

	void Bomb::Explode() {
		GetStage()->AddGameObject<ExplodeCollider>(GetComponent<Transform>()->GetPosition(), GetThis<Bomb>());
		GetStage()->RemoveGameObject<Bomb>(GetThis<Bomb>());
	}
	void Bomb::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Stage")) {
			RemoveComponent<Gravity>();
		}
	}


	void ExplodeCollider::OnCreate() {
		auto col = AddComponent<CollisionSphere>();
		auto trans = GetComponent<Transform>();

		trans->SetPosition(m_Pos);
		float range = m_Bomb->GetRange();
		trans->SetScale(Vec3(range,range,range));
	}
	void ExplodeCollider::OnUpdate() {
		if (m_Tick > 2) {
			GetStage()->RemoveGameObject<ExplodeCollider>(GetThis<ExplodeCollider>());
		}
		m_Tick++;
	}
	void ExplodeCollider::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Floor")) {
			GetStage()->RemoveGameObject<FloorBlock>(Other);
		}
	}
}
//end basecross
