/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void BombItem::OnCreate() {
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SQUARE");
		draw->SetTextureResource(L"BOMB_ITEM_TEX");
		SetAlphaActive(true);
		
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_Pos);
		trans->SetScale(Vec3(0.5f) + Vec3(0.2f) * (m_AddBombNum - DEFAULT_BOMB_NUM));

		AddTag(L"Item");
	}
	void BombItem::OnUpdate() {

	}
	void BombItem::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			//所持数を増やす
			static_pointer_cast<Player>(Other)->AddHasBomb(m_AddBombNum);
			GetTypeStage<GameStage>()->DestroyBlock(m_Pos,GetThis<GameObject>());
			GetStage()->RemoveGameObject<BombItem>(GetThis<BombItem>());
		}
	}
}
//end basecross
