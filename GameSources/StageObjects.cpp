/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Goal::OnCreate() {
		auto draw = AddComponent<PNTStaticModelDraw>();

		draw->SetMultiMeshResource(L"GOAL_MD");
		draw->SetTextureResource(L"GOAL_MD_TEX");

		draw->SetSamplerState(SamplerState::LinearWrap);
		Mat4x4 matrix;
		matrix.affineTransformation(
			Vec3(0.3f,0.3f,0.3f),Vec3(0.0f,0.0f,0.0f),Vec3(0.0f,0.0f,0.0f),Vec3(0.0f,-0.5f,0.0f)
		);
		draw->SetMeshToTransformMatrix(matrix);

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
		if (Other->FindTag(L"Player") && !m_IsActuated) {
			GetTypeStage<GameStage>()->NewRespawnPosition(GetComponent<Transform>()->GetPosition());
			m_IsActuated = true;
		}
	}
}
//end basecross
