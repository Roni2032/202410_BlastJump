/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Goal::OnCreate() {
		auto draw = AddComponent<PNTBoneModelDraw>();

		draw->SetMeshResource(L"GOAL_MD");
		//draw->SetTextureResource(L"GOAL_MD_TEX");

		draw->SetSamplerState(SamplerState::LinearWrap);
		Mat4x4 matrix;
		matrix.affineTransformation(
			Vec3(0.3f,0.15f,0.3f),Vec3(0.0f,0.0f,0.0f),Vec3(0.0f,0.0f,0.0f),Vec3(0.0f,-0.25f,0.0f)
		);
		draw->SetMeshToTransformMatrix(matrix);
		draw->AddAnimation(L"OPEN_ANIM", 0, 60, false, 60.0f);
		draw->AddAnimation(L"DEFAULT_ANIM", 0, 1, true,60.0f);
		draw->ChangeCurrentAnimation(L"DEFAULT_ANIM");

		AddTag(L"Item");
		//auto col = AddComponent<CollisionObb>();
		//col->SetAfterCollision(AfterCollision::None);

		//col->SetDrawActive(true);

		GetComponent<Transform>()->SetPosition(m_Pos);
		GetComponent<Transform>()->SetScale(Vec3(1.0f,2.0f,1.0f));
	}
	void Goal::OnUpdate() {
		auto draw = GetComponent<PNTBoneModelDraw>();
		draw->UpdateAnimation(App::GetApp()->GetElapsedTime());
	}
	void Goal::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player")) {
			auto draw = GetComponent<PNTBoneModelDraw>();
			draw->ChangeCurrentAnimation(L"OPEN_ANIM");
			GetTypeStage<GameStage>()->GameClear();
		}
	}

	void CheckPoint::OnCreate() {
		auto col = AddComponent<CollisionObb>();
		col->SetAfterCollision(AfterCollision::None);

		col->SetDrawActive(true);
	}
	void CheckPoint::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Player") && !m_IsActuated) {
			GetTypeStage<GameStage>()->NewRespawnPosition(GetComponent<Transform>()->GetPosition());
			m_IsActuated = true;
		}
	}
}
//end basecross
