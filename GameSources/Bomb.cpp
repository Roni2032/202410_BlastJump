/*!
@file Bomb.cpp
@brief ”š’eŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Bomb::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"BOMB_MD");
		drawComp->SetTextureResource(L"BOMB_MD_TEX");
		Mat4x4 matrix;
		matrix.affineTransformation(
			Vec3(1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, -0.5f, 0.0f)
		);
		drawComp->SetMeshToTransformMatrix(matrix);

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"BOMB_MD");
		shadow->SetMeshToTransformMatrix(matrix);

		auto col = AddComponent<CollisionSphere>();
		col->AddExcludeCollisionTag(L"Player");

		auto gravity = AddComponent<BCGravity>();
		gravity->Jump(m_ThrowVelocity);

		GetComponent<Transform>()->SetPosition(m_Pos);
		GetComponent<Transform>()->SetScale(Vec3(0.5f));

		m_GameStage = GetTypeStage<GameStage>();

		Block::CollisionObjects.push_back(GetComponent<Transform>());

		rotateSpeed = Vec3(0
			/*Util::RandZeroToOne() * 180.0f - 90.0f,
			Util::RandZeroToOne() * 180.0f - 90.0f,
			Util::RandZeroToOne() * 180.0f - 90.0f*/
		);
		auto parent = GetTypeStage<GameStage>()->m_Player->GetComponent<Transform>()->GetParent();
		if (parent != nullptr) {
			GetComponent<Transform>()->SetParent(parent);
		}

	}

	void Bomb::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_ExplodeTimer += elapsedTime;

		if (m_ExplodeTimer > m_ExplodeTime) {
			Explode();
		}

		Vec3 rot = GetComponent<Transform>()->GetRotation();
		rot += rotateSpeed * elapsedTime;
		GetComponent<Transform>()->SetRotation(rot);
	}

	void Bomb::Explode() {
		m_GameStage->AddGameObject<ExplodeCollider>(GetComponent<Transform>()->GetWorldPosition(),m_ExplodeStatus);
		
		m_GameStage->PlayParticle(L"EXPLODE_PCL", GetComponent<Transform>()->GetWorldPosition());
		
		m_GameStage->RemoveGameObject<Bomb>(GetThis<Bomb>());

		SoundManager::Instance().PlaySE(L"BOMB_SD",0.1f);

		if (m_GameStage->GetGameMode() == GameStage::GameMode::NotBomb) {
			m_GameStage->SetGameMode(GameStage::GameMode::InGame);
		}
	}
	void Bomb::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		Explode();
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
		//col->SetDrawActive(true);
		auto trans = GetComponent<Transform>();

		trans->SetPosition(m_Pos);
		trans->SetScale(Vec3(m_Explosion.m_Range));
	}
	void ExplodeCollider::OnUpdate() {
		GetStage()->RemoveGameObject<ExplodeCollider>(GetThis<ExplodeCollider>());
	}
	void ExplodeCollider::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto otherTrans = Other->GetComponent<Transform>();

		Vec3 otherPos = otherTrans->GetWorldPosition();
		Vec3 ExplodeCorePos = GetComponent<Transform>()->GetPosition();

		Vec3 diff = otherPos - ExplodeCorePos;

		float distance = sqrtf(static_cast<float>(pow(diff.x, 2) + pow(diff.y, 2)));
		float reboundRate = distance / m_Explosion.m_Range;
		if (reboundRate > 1.0f) {
			reboundRate = 1.0f;
		}
		if (reboundRate < m_MinReboundRate) {
			reboundRate = m_MinReboundRate;
		}
 		Vec3 reflectPower = diff.normalize() * (1.0f - reboundRate) * m_Explosion.m_Power;
		if (Other->FindTag(L"Floor")) {
			auto block = static_pointer_cast<FloorBlock>(Other);
			if (block != nullptr) {
				block->HitExplode(reflectPower.length() * 8.0f);
				//block->HitExplode(100);
			}
		}
		auto gravity = Other->GetComponent<BCGravity>(false);
		if (gravity != nullptr) {
			
			gravity->Jump(reflectPower);
		}

		
	}
}
//end basecross
