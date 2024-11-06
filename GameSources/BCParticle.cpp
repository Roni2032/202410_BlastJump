/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void BCParticleInstance::OnCreate() {
		spriteData.resize(dataNum);
		for (int i = 0; i < dataNum; i++) {
			spriteData.push_back(BCParticleSpriteData());
		}

		m_Draw = AddComponent<PNTStaticInstanceDraw>();

		m_Draw->SetMeshResource(L"DEFAULT_SQUARE");
		m_Draw->SetTextureResource(m_TexKey);


		SetAlphaActive(true);

		m_Camera = OnGetDrawCamera();

		m_Trans = GetComponent<Transform>();
		Init();
		SetActive(false);
	}
	void BCParticleInstance::OnUpdate() {
		float elapsed = App::GetApp()->GetElapsedTime();
		if (m_IsActive) {
			auto parent = m_ParentTrans.lock();
			m_Draw->ClearMatrixVec();
			for (auto& sprite : spriteData) {
				Vec3 pos = sprite.matrix.getTranslation();
				if (sprite.m_Velocity.y > m_Gravity) {
					sprite.m_Velocity.y += m_Gravity * elapsed;
				}
				pos += sprite.m_Velocity * elapsed;

				if (parent != nullptr) {
					sprite.matrix.translation(pos + parent->GetPosition());
				}
				else {
					sprite.matrix.translation(pos);
				}

				m_Draw->AddMatrix(sprite.matrix);
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
	void BCParticleInstance::StartParticle(const Vec3 pos) {
		auto parent = m_ParentTrans.lock();
		for (auto& sprite : spriteData) {
			sprite.m_StartPos = pos;
			if (parent != nullptr) {
				sprite.matrix.translation(sprite.m_StartPos + parent->GetPosition());
			}
			else {
				sprite.matrix.translation(sprite.m_StartPos);
			}
		}
				
		SetActive(true);
	}
	void BCParticleInstance::Init() {
		m_TotalTime = 0.0f;
		m_Color.w = 1.0f;
		for (auto& sprite : spriteData) {
			sprite.m_Velocity = sprite.m_BaseVelocity;
		}
		SetColor(m_Color);
	}
	void BCParticleInstance::SetActive(bool active) {
		if (m_IsActive != active) {
			m_IsActive = active;
		}
		m_Draw->SetDrawActive(m_IsActive);

		if (m_IsActive) {
			Init();
		}
	}
	void BCParticleInstance::SetColor(Col4 color) {
		if (m_Color != color) {
			m_Color = color;
		}
		m_Draw->SetDiffuse(m_Color);
	}
	void BCParticleInstance::SetGravity(float gravity) {
		m_Gravity = gravity;
	}

	void BCParticleSprite::OnCreate() {
		
		m_Draw = AddComponent<PNTStaticDraw>();
		
		
		m_Draw->SetMeshResource(L"DEFAULT_SQUARE");
		m_Draw->SetTextureResource(m_TexKey);
		
		
		SetAlphaActive(true);

		m_Camera = OnGetDrawCamera();

		m_Trans = GetComponent<Transform>();
		Init();
		SetActive(false);
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

			//------------------------------------------------------------------
			//	スプライトをビルボード化
			//------------------------------------------------------------------
			
			//Vec3 cameraPos = m_Camera->GetEye();
			//Vec3 spritePos = m_Trans->GetPosition();
			//
			//Vec3 diff = cameraPos - spritePos;
			//diff = diff.normalize();
			//float radXZ = atan2f(diff.z, diff.x);
			//float radXY = atan2f(diff.y, diff.x);
			//Vec3 sideVec = Vec3(cos(radXZ + XM_PI / 2.0f), 0.0f, sin(radXZ + XM_PI / 2.0f));

			//Quat q = m_Trans->GetQuaternion().rotationY(radXZ);
			////Quat q = (Quat)XMQuaternionRotationAxis(diff,radXZ);

			////
			//////Quat q2 = (Quat)XMQuaternionRotationAxis(sideVec, radXY);

			//m_Trans->SetQuaternion(q);
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
	
	shared_ptr<BCParticleInstance> BCParticle::AddParticleInstance(int num, const wstring& key) {
		shared_ptr<BCParticleInstance> particleSprite;

		particleSprite = GetStage()->AddGameObject<BCParticleInstance>(key,num);
		m_ParticleInstance.push_back(particleSprite);

		return particleSprite;
	}
	void BCParticle::Shot(const Vec3 pos) {
		auto particles = GetAllParticle();
		for (auto& particle : particles) {
			particle->StartParticle(pos);
		}
	}
}
//end basecross
