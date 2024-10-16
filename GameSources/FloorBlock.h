/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class FloorBlock : public GameObject {
		bool m_IsCanDestroy;
		Vec3 m_Pos;
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
}
//end basecross
