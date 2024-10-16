/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void FloorBlock::OnCreate() {
		auto drawComp = AddComponent<BcPTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(1, 0, 0, 1));

		AddComponent<CollisionObb>();
		AddTag(L"Floor");
		AddTag(L"Stage");

		GetComponent<Transform>()->SetPosition(m_Pos);
	}

	void FloorBlock::OnUpdate() {

	}

}
//end basecross
