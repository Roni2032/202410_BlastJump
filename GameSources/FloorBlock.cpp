/*!
@file FloorBlock.cpp
@brief 地面の実体
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

	//テクスチャ付き床ブロック
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
