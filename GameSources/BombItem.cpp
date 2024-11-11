/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void BombItem::OnCreate() {
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SPHERE");
		AddTag(L"Stage");
		auto col = AddComponent<CollisionSphere>();
		col->SetAfterCollision(AfterCollision::None);
		
		
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_Pos);
		trans->SetScale(Vec3(0.5f) + Vec3(0.2f) * (m_AddBombNum - DEFAULT_BOMB_NUM));
	}
	void BombItem::OnUpdate() {

	}
	void BombItem::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			//所持数を増やす
			static_pointer_cast<Player>(Other)->AddHasBomb();
			GetStage()->RemoveGameObject<BombItem>(GetThis<BombItem>());
		}
	}
}
//end basecross
