/*!
@file FloorBlock.cpp
@brief ínñ ÇÃé¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Block::OnCreate() {
		if (m_TexKey == L"" || m_TexKey == L"null") {
			auto drawComp = AddComponent<BcPNTStaticDraw>();
			drawComp->SetMeshResource(L"DEFAULT_CUBE");
			drawComp->SetTextureResource(L"TEST_TEX");
			drawComp->SetDiffuse(Col4(1, 1, 1, 1));
		}
		else {
			//ÉÇÉfÉãÇÃê›íË
		}

		auto col = AddComponent<CollisionObb>();
		col->SetFixed(true);
		AddTag(L"Stage");

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_Pos);
		trans->SetScale(m_Scale);
		trans->SetRotation(m_Rot);

		Start();
	}

	void Block::OnUpdate() {
		Update();
	}

	void FloorBlock::Start() {
		AddTag(L"Floor");
	}
}
//end basecross
