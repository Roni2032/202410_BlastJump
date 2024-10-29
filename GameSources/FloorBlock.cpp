/*!
@file FloorBlock.cpp
@brief �n�ʂ̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void FloorBlock::OnCreate() {
		auto drawComp = AddComponent<BcPTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(m_Color);

		AddComponent<CollisionObb>();
		AddTag(L"Floor");
		AddTag(L"Stage");

		GetComponent<Transform>()->SetPosition(m_Pos);
	}

	void FloorBlock::OnUpdate() {

	}

	//�e�N�X�`���t�����u���b�N
	void FloorBlockTex::OnCreate() {
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(m_Tex);

		AddComponent<CollisionObb>();
		AddTag(L"Floor");
		AddTag(L"Stage");

		GetComponent<Transform>()->SetPosition(m_Pos);
	}

	void FloorBlockTex::OnUpdate() {

	}

}
//end basecross
