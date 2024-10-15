/*!
@file MovementComponents.cpp
@brief 移動用コンポーネント
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void BCSprite::OnCreate() {

	}
	void BCSprite::OnUpdate() {
		if (m_IsAnimation) {
			Animation();
		}
	}
	void BCSprite::Animation() {

	}
	void BCSprite::UpdateUV(vector<Vec2> uv) {
		if (uv.empty()) return;
		if (m_Draw) {
			for (int i = 0; i < m_Vertices.size(); i++)
			{

				m_Vertices[i].textureCoordinate = uv[i];
			}

			m_Draw->UpdateVertices(m_Vertices);
		}
	}
}
//end basecross
