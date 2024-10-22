/*!
@file FloorBlock.h
@brief 地面など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class FloorBlock : public GameObject {
		bool m_IsCanDestroy;
		Vec3 m_Pos;

		Col4 m_Color = Col4();
	public:
		FloorBlock(const shared_ptr<Stage>& ptr,Vec3 pos): 
			GameObject(ptr),
			m_IsCanDestroy(true),
			m_Pos(pos)
		{}
		virtual ~FloorBlock(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//テクスチャ付き床ブロック
	class FloorBlockTex : public GameObject {
		bool m_IsCanDestroy;
		Vec3 m_Pos;
		wstring m_Tex;

	public:
		FloorBlockTex(const shared_ptr<Stage>& ptr,Vec3 pos,wstring tex): 
			GameObject(ptr),
			m_IsCanDestroy(true),
			m_Pos(pos),
			m_Tex(tex)
		{}
		virtual ~FloorBlockTex(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
