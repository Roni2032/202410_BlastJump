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
			SoundManager::Instance().PlaySE(L"BOMB_GET_SD",0.5f);
			//所持数を増やす
			static_pointer_cast<Player>(Other)->AddHasBomb(m_AddBombNum);
			GetStage()->AddGameObject<AddBombBoard>(Other->GetComponent<Transform>()->GetPosition() + Vec3(0, 1, 0));
			GetTypeStage<GameStage>()->DestroyBlock(m_Pos,GetThis<GameObject>());
			GetStage()->RemoveGameObject<BombItem>(GetThis<BombItem>());
			
		}
	}

	void AddBombBoard::OnCreate() {
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SQUARE");
		draw->SetTextureResource(L"BOMB_PLUS");
		SetAlphaActive(true);

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_StartPos);
		trans->SetScale(Vec3(1.0f,0.5f,1.0f));
	}
	void AddBombBoard::OnUpdate() {
		auto trans = GetComponent<Transform>();
		float elapsed = App::GetApp()->GetElapsedTime();
		m_DeleteTimer += elapsed;
		if (m_DeleteTimer > m_DeleteTime) {
			GetStage()->RemoveGameObject<AddBombBoard>(GetThis<AddBombBoard>());
		}
		Vec3 move = Vec3(1, 1, 0);

		Vec3 pos = trans->GetPosition();
		pos += move * elapsed;
		trans->SetPosition(pos);
	}
}
//end basecross
