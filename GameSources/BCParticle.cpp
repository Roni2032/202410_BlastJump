/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void BCParticleSprite::OnCreate() {

		vector<VertexPositionColorTexture> vertex = {
			{Vec3(0, 0, 0),Col4(1,1,1,1), Vec2(0,0)},
			{Vec3(1, 0, 0),Col4(1,1,1,1), Vec2(1.0f,0)},
			{Vec3(0, -1, 0),Col4(1,1,1,1), Vec2(0,1.0f)},
			{Vec3(1, -1, 0),Col4(1,1,1,1), Vec2(1.0f,1.0f)}
		};
		vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		
		m_Draw = AddComponent<PNTStaticDraw>();
		
		
		m_Draw->SetMeshResource(L"DEFAULT_SQUARE");
		m_Draw->SetTextureResource(m_TexKey);
		
		
		SetAlphaActive(true);

		m_Camera = OnGetDrawCamera();

		m_Trans = GetComponent<Transform>();
		Init();
	}
	void BCParticleSprite::OnUpdate() {
		float elapsed = App::GetApp()->GetElapsedTime();
		if (m_IsActive) {
			Vec3 pos = m_Trans->GetPosition();
			if (m_Velocity.y > m_Gravity) {
				m_Velocity.y += m_Gravity * elapsed;
			}
			pos += m_Velocity * elapsed;

			auto parent = m_ParentTrans.lock();
			if (parent != nullptr) {
				m_Trans->SetPosition(pos + parent->GetPosition());
			}
			else {
				m_Trans->SetPosition(pos);
			}

			m_TotalTime += elapsed;
			if (m_TotalTime > m_MaxTime) {
				SetActive(false);
			}

			if (m_Color.w <= 1.0f && m_Color.w >= 0.0f) {
				m_Color.w += elapsed * (m_Alpha.m_Low - m_Alpha.m_High) / m_MaxTime;
				SetColor(m_Color);
			}
		}
	}
	void BCParticleSprite::StartParticle(const Vec3 pos) {
		m_StartPos = pos;
		auto parent = m_ParentTrans.lock();
		if (parent != nullptr) {
			m_Trans->SetPosition(m_StartPos + parent->GetPosition());
		}
		else {
			m_Trans->SetPosition(m_StartPos);
		}
		SetActive(true);
	}
	void BCParticleSprite::Init() {
		m_TotalTime = 0.0f;
		m_Color.w = 1.0f;
		m_Velocity = m_BaseVelocity;
		SetColor(m_Color);
	}
	void BCParticleSprite::SetActive(bool active) {
		if (m_IsActive != active) {
			m_IsActive = active;
		}
		m_Draw->SetDrawActive(m_IsActive);

		if (m_IsActive) {
			Init();
		}
	}
	void BCParticleSprite::SetColor(Col4 color) {
		if (m_Color != color) {
			m_Color = color;
		}
		m_Draw->SetDiffuse(m_Color);
	}
	void BCParticleSprite::SetSize(Vec3 size) {
		m_Size = size;
		m_Trans->SetScale(m_Size);
	}
	void BCParticleSprite::SetGravity(float gravity) {
		m_Gravity = gravity;
	}

	void BCParticle::OnCreate() {
		AddParticleData();
	}
	vector<shared_ptr<BCParticleSprite>> BCParticle::AddParticle(int num, const wstring& key) {
		vector<shared_ptr<BCParticleSprite>> particleSprite;
		for (int i = 0; i < num; i++) {
			auto particle = GetStage()->AddGameObject<BCParticleSprite>(key);
			particleSprite.push_back(particle);
			m_ParticleSprites.push_back(particle);
		}

		return particleSprite;
	}
	void BCParticle::AddParticleData() {
		
	}
	void BCParticle::Shot(const Vec3 pos) {
		auto particles = GetAllParticle();
		for (auto& particle : particles) {
			particle->StartParticle(pos);
		}
	}
}
//end basecross
