/*!
@file BCSprite.cpp
@brief スプライト
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
		if (m_UseIndex == -1 || m_UseIndex < m_AnimationUV.size()) {
			m_UseIndex = static_cast<int>(m_AnimationUV.size());
		}
		if (m_IsUseCenterSprite) {
			m_Vertices = {
				{Vec3(-m_Size.x / 2.0f, m_Size.y / 2.0f, 0),Col4(1,1,1,1), m_AnimationUV[0][0]},
				{Vec3(m_Size.x / 2.0f, m_Size.y / 2.0f, 0),Col4(1,1,1,1), m_AnimationUV[0][1]},
				{Vec3(-m_Size.x / 2.0f, -m_Size.y / 2.0f, 0),Col4(1,1,1,1), m_AnimationUV[0][2]},
				{Vec3(m_Size.x / 2.0f, -m_Size.y / 2.0f, 0),Col4(1,1,1,1), m_AnimationUV[0][3]}
			};
		}
		else {
			m_Vertices = {
				{Vec3(0, 0, 0),Col4(1,1,1,1), m_AnimationUV[0][0]},
				{Vec3(m_Size.x, 0, 0),Col4(1,1,1,1), m_AnimationUV[0][1]},
				{Vec3(0, -m_Size.y, 0),Col4(1,1,1,1), m_AnimationUV[0][2]},
				{Vec3(m_Size.x, -m_Size.y, 0),Col4(1,1,1,1), m_AnimationUV[0][3]}
			};
		}
		vector<uint16_t> indices = { 
			0, 1, 2,
			2, 1, 3
		};


		m_Draw = AddComponent<PCTSpriteDraw>(m_Vertices, indices);
		if (m_TexKey != L"") {
			m_Draw->SetTextureResource(m_TexKey);
		}
		SetAlphaActive(true);
		m_Draw->SetSamplerState(SamplerState::LinearWrap);
		m_Draw->SetDiffuse(Col4(1, 1, 1, 1));

		m_Transform = GetComponent<Transform>();
		m_Transform->SetPosition(m_Pos);
		//GetComponent<Transform>()->SetRotation(m_rot);
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

			if (m_IsUseCenterSprite) {
				m_Vertices = {
					{Vec3(-m_Size.x / 2.0f, m_Size.y / 2.0f, 0),Col4(1,1,1,1), m_AnimationUV[0][0]},
					{Vec3(m_Size.x / 2.0f, m_Size.y / 2.0f, 0),Col4(1,1,1,1), m_AnimationUV[0][1]},
					{Vec3(-m_Size.x / 2.0f, -m_Size.y / 2.0f, 0),Col4(1,1,1,1), m_AnimationUV[0][2]},
					{Vec3(m_Size.x / 2.0f, -m_Size.y / 2.0f, 0),Col4(1,1,1,1), m_AnimationUV[0][3]}
				};
			}
			else {
				m_Vertices = {
					{Vec3(0, 0, 0),Col4(1,1,1,1), m_AnimationUV[0][0]},
					{Vec3(m_Size.x, 0, 0),Col4(1,1,1,1), m_AnimationUV[0][1]},
					{Vec3(0, -m_Size.y, 0),Col4(1,1,1,1), m_AnimationUV[0][2]},
					{Vec3(m_Size.x, -m_Size.y, 0),Col4(1,1,1,1), m_AnimationUV[0][3]}
				};
			}
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
	void BCSprite::SetDiffuse(Col4 color) {
		m_Draw->SetDiffuse(color);
	}
	Col4 BCSprite::GetDiffuse() {
		return m_Draw->GetDiffuse();
	}

	void BCNumber::OnCreate() {
		int digits = static_cast<int>(pow(10, m_DisplayDigit - 1));
		float sizeX = m_Size.x / m_DisplayDigit;
		m_Numbers.reserve(m_DisplayDigit);
		for (int i = 0; i < m_DisplayDigit; i++) {
			shared_ptr<BCSprite> number = GetStage()->AddGameObject<BCSprite>(m_TexKey, Vec3(m_Pos.x + i * sizeX,m_Pos.y,m_Pos.z), Vec2(sizeX, m_Size.y));//ObjectFactory::Create<BCSprite>(GetStage(), m_TexKey, Vec3(0,0,0)/*m_Pos + i * sizeX*/, Vec2(sizeX, m_Size.y));
			int singleDigit = m_DisplayNumber / digits % 10;
			
			number->UpdateUV(GetUV(singleDigit));
			digits /= 10;
			m_Numbers.push_back(number);
		}
		auto trans = GetComponent<Transform>();
		trans->SetPosition(0,0,0);
	}

	void BCNumber::OnUpdate() {
		
	}

	vector<Vec2> BCNumber::GetUV(int displayDigit) {
		float uvX = 1.0f / m_CutNum;

		vector<Vec2> uv = {
				{uvX * displayDigit,0.0f},
				{uvX * (displayDigit + 1),0.0f},
				{uvX * displayDigit,1.0f},
				{uvX * (displayDigit + 1),1.0f}
		};

		return uv;
	}

	void BCNumber::UpdateNumber(int number) {
		m_DisplayNumber = number;
		int digits = static_cast<int>(pow(10, m_DisplayDigit - 1));
		for (auto& sprite : m_Numbers) {
			int singleDigit = m_DisplayNumber / digits % 10;

			sprite->UpdateUV(GetUV(singleDigit));
			digits /= 10;
		}
	}


	void SpriteAction::OnCreate() {
		m_Draw = GetGameObject()->GetComponent<SpriteBaseDraw>();
		m_Trans = GetGameObject()->GetComponent<Transform>();
	}

	void SpriteFlash::OnUpdate() {
		if (m_Draw != nullptr && GetIsPlay()) {
			float elapsed = App::GetApp()->GetElapsedTime();
			Col4 color = m_Draw->GetDiffuse();
			color.w += m_FlashSpeed * elapsed;
			if (color.w < 0 || color.w > 1) {
				m_FlashSpeed *= -1;
			}
			m_Draw->SetDiffuse(color);
		}
	}
	void SpriteScaling::OnCreate() {
		SpriteAction::OnCreate();

		defaultSize = m_Trans->GetScale();
	}
	void SpriteScaling::OnUpdate() {
		if (m_Trans != nullptr && GetIsPlay()) {
			float elapsed = App::GetApp()->GetElapsedTime();
			m_Ratio += m_ScalingSpeed * elapsed;
			if (m_Ratio < m_MinRatio || m_Ratio > m_MaxRatio) {
				m_ScalingSpeed *= -1;
			}
			m_Trans->SetScale(defaultSize * m_Ratio);
		}
	}

	void SpriteFade::OnUpdate() {
		if (m_Draw != nullptr && GetIsPlay()) {
			float elapsed = App::GetApp()->GetElapsedTime();
			if (!m_IsFadeOut) {
				elapsed *= -1;
			}
			Col4 color = m_Draw->GetDiffuse();
			if (!IsFinish()) {
				color.w += elapsed * m_FadeSpeed;
			}
			if (color.w < 0 || color.w > 1)
			{
				m_IsFinished = true;
			}
			else {
				m_IsFinished = false;
			}
			m_Draw->SetDiffuse(color);
		}
	}
}
//end basecross
