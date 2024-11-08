/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Goal::OnCreate() {
		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);

		col->SetDrawActive(true);

		GetComponent<Transform>()->SetPosition(m_Pos);
	}
	void Goal::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			GetTypeStage<GameStage>()->GameClear();
		}
	}

	void CheckPoint::OnCreate() {
		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);

		col->SetDrawActive(true);
	}
	void CheckPoint::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {

		}
	}
}
//end basecross
