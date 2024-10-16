/*!
@file MovementComponents.cpp
@brief 移動用コンポーネント
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void BCSprite::OnCreate() {

		for (int y = 0; y < m_cutUV.y; y++) {
			for (int x = 0; x < m_cutUV.x; x++) {
				m_AnimationUV.push_back({
					{(1.0f / m_cutUV.x) * x,(1.0f / m_cutUV.y) * y},
					{(1.0f / m_cutUV.x) * (x + 1),(1.0f / m_cutUV.y) * y},
					{(1.0f / m_cutUV.x) * x,(1.0f / m_cutUV.y) * (y + 1)},
					{(1.0f / m_cutUV.x) * (x + 1),(1.0f / m_cutUV.y) * (y + 1)}
					}
				);
			}
		}
		if (m_UseIndex == -1) {
			m_UseIndex = m_cutUV.x * m_cutUV.y;
		}
		m_Vertices = { 
			{Vec3(0, 0, 0),Col4(1,1,1,1), m_AnimationUV[0][0]},
			{Vec3(m_Size.x, 0, 0),Col4(1,1,1,1), m_AnimationUV[0][1]},
			{Vec3(0, -m_Size.y, 0),Col4(1,1,1,1), m_AnimationUV[0][2]},
			{Vec3(m_Size.x, -m_Size.y, 0),Col4(1,1,1,1), m_AnimationUV[0][3]}
		};
		vector<uint16_t> indices = { 
			0, 1, 2,
			2, 1, 3
		};


		m_Draw = AddComponent<PCTSpriteDraw>(m_Vertices, indices);
		m_Draw->SetTextureResource(m_TexKey);
		m_Draw->SetSamplerState(SamplerState::LinearWrap);
		m_Draw->SetDiffuse(Col4(1, 1, 1, 1));

		m_Transform = GetComponent<Transform>();
		m_Transform->SetPosition(m_Pos);
		//GetComponent<Transform>()->SetRotation(m_rot);
		SetAlphaActive(true);
	}
	void BCSprite::OnUpdate() {
		if (m_IsAnimation) {
			Animation();
		}
	}
	void BCSprite::Animation() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_AnimationTimer += elapsedTime;

		if (m_AnimationTimer > m_AnimationChangeTime) {
			m_Index++;
			if (m_Index >= m_UseIndex || m_Index >= m_AnimationUV.size()) {
				m_Index = 0;
			}
			UpdateUV(m_AnimationUV[m_Index]);

			m_AnimationTimer = 0.0f;
		}
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
	void BCSprite::UpdateSize(Vec3 size) {
		m_Transform->SetScale(size);
	}
	void BCSprite::UpdateSize(Vec2 size) {
		if (m_Draw) {
			m_Size = size;

			m_Vertices = {
				{Vec3(0, 0, 0),Col4(1,1,1,1), m_AnimationUV[m_Index][0]},
				{Vec3(m_Size.x, 0, 0),Col4(1,1,1,1), m_AnimationUV[m_Index][1]},
				{Vec3(0, -m_Size.y, 0),Col4(1,1,1,1), m_AnimationUV[m_Index][2]},
				{Vec3(m_Size.x, -m_Size.y, 0),Col4(1,1,1,1), m_AnimationUV[m_Index][3]}
			};
			m_Draw->UpdateVertices(m_Vertices);
		}
	}

	void BCSprite::SetPos(Vec3 pos) {
		m_Transform->SetPosition(pos);
	}
	
	void BCSprite::SetInterval(float interval) {

	}
	void BCSprite::SetUseIndex(int useIndex) {

	}
}
//end basecross
