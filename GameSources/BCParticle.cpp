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

		SetDrawLayer(1);
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
		m_Draw->SetOriginalMeshUse(true);
		vector<uint16_t> indexes;
		MeshUtill::CreateSquare(1.0f, m_Vertexes, indexes);
		m_Draw->CreateOriginalMesh(m_Vertexes, indexes);
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
			//------------------------------------------------------------------
			//	遅延
			//------------------------------------------------------------------
			if (m_DelayTime != 0) {
				if (m_DelayTimer > m_DelayTime) {
					SetDrawActive(true);
				}
				else {
					m_DelayTimer += elapsed;
					SetDrawActive(false);
					return;
				}
			}
			//------------------------------------------------------------------
			//	移動
			//------------------------------------------------------------------
			Vec3 pos = m_Trans->GetPosition();
			if (m_Velocity.y > m_Gravity) {
				m_Velocity.y += m_Gravity * elapsed;
			}
			pos += m_Velocity * elapsed;
			m_Velocity -= m_Velocity * (1.0f - m_DecelerationRate) * elapsed;

			auto parent = m_ParentTrans.lock();
			if (parent != nullptr) {
				m_Trans->SetPosition(pos + parent->GetPosition());
			}
			else {
				m_Trans->SetPosition(pos);
			}
			
			//------------------------------------------------------------------
			//	サイズ
			//------------------------------------------------------------------
			Vec3 scale = m_Trans->GetScale();
			scale += m_ScaleVelocity * elapsed;
			if (scale.x < 0) {
				scale.x = 0;
			}
			if (scale.y < 0) {
				scale.y = 0;
			}
			if (scale.z < 0) {
				scale.z = 0;
			}
			m_Trans->SetScale(scale);
			//------------------------------------------------------------------
			//	表示時間
			//------------------------------------------------------------------
			m_TotalTime += elapsed;
			if (m_TotalTime > m_MaxTime) {
				SetActive(false);
			}
			//------------------------------------------------------------------
			//	色変化
			//------------------------------------------------------------------
			Col4 targetLengthColor = m_TargetColor - m_Color;
			targetLengthColor.w = 0.0f;
			if (targetLengthColor.length() > 0.1f) {
				m_Color += (m_TargetColor - m_StartColor) * elapsed / m_ColorChangeTime;
			}


			if (m_Color.w <= 1.0f && m_Color.w >= 0.0f) {
				m_Color.w += elapsed * (m_Alpha.m_Low - m_Alpha.m_High) / m_MaxTime;
			}
			SetColor(m_Color);
			//------------------------------------------------------------------
			//	アニメーション
			//------------------------------------------------------------------
			if (m_IsAnimation) {
				m_AnimationTimer += elapsed;
				if (m_AnimationTimer > m_AnimationTime / m_AnimationUV.size()) {
					m_RenderIndex++;
					if (m_RenderIndex >= m_AnimationUV.size()) {
						m_RenderIndex = 0;
					}
					UpdateAnimationUV(m_RenderIndex);
					m_AnimationTimer = 0;
				}
			}
			else {
				m_AnimationTimer = 0;
			}
			//------------------------------------------------------------------
			//	ビルボード化
			//------------------------------------------------------------------
			Quat q = Quat();
			Vec3 cameraPos = m_Camera->GetEye();
			Vec3 spritePos = m_Trans->GetWorldPosition();

			Vec3 fwd = Vec3(0, 0, -1);
			fwd = fwd.normalize();

			Vec3 diff = cameraPos - spritePos;
			diff = diff.normalize();

			if (diff.length() != 0) {
				diff = diff.normalize();

				float inner = (diff.x * fwd.x + diff.y * fwd.y + diff.z * fwd.z) / (diff.length() * fwd.length());
				float rad = acos(inner);

				Vec3 verticalVec = Vec3(diff.y * fwd.z - diff.z * fwd.y, diff.z * fwd.x - diff.x * fwd.z, diff.x * fwd.y - diff.y * fwd.x);

				Quat newQ = Quat(verticalVec.x * sin(rad / 2.0f), verticalVec.y * sin(rad / 2.0f), verticalVec.z * sin(rad / 2.0f), cos(rad / 2.0f));

				q *= newQ;
			}
			m_Trans->SetQuaternion(q);
			//------------------------------------------------------------------
			//	回転
			//------------------------------------------------------------------
			/*if (m_IsRotateMovement) {
				float rad = atan2f(m_Velocity.y, m_Velocity.x);
				Quat newQ = Quat(diff.x * sin(rad / 2.0f), diff.y * sin(rad / 2.0f), diff.z * sin(rad / 2.0f), cos(rad / 2.0f));

				q *= newQ;
			}
			*/
		}
	}
	void BCParticleSprite::UpdateAnimationUV(int index) {
		for (int i = 0; i < m_Vertexes.size(); i++) {
			m_Vertexes[i].textureCoordinate = m_AnimationUV[index][i];
		}
		m_Draw->UpdateVertices(m_Vertexes);
	}
	void BCParticleSprite::AutoCutAnimationUV(Vec2 cut) {
		for (int i = 0; i < cut.y; i++) {
			for (int j = 0; j < cut.x; j++) {
				vector<Vec2> uv = {
					{(1.0f / cut.x) * j,(1.0f / cut.y) * i},
					{(1.0f / cut.x) * (j + 1),(1.0f / cut.y) * i},
					{(1.0f / cut.x) * j,(1.0f / cut.y) * (i + 1)},
					{(1.0f / cut.x) * (j + 1),(1.0f / cut.y) * (i + 1)}
				};

				m_AnimationUV.push_back(uv);
			}
		}
		m_IsAnimation = true;
	}

	void BCParticleSprite::StartParticle(const Vec3 pos) {
		m_StartPos = m_BaseStartPos + pos;
		auto parent = m_ParentTrans.lock();
		if (parent != nullptr) {
			m_Trans->SetPosition(m_StartPos + parent->GetPosition());
		}
		else {
			m_Trans->SetPosition(m_StartPos);
		}
		Init();
	}
	void BCParticleSprite::Init() {
		m_TotalTime = 0.0f;
		m_Color = m_BaseColor;
		m_Velocity = m_BaseVelocity;
		m_ScaleVelocity = m_BaseScaleVelocity;
		SetColor(m_Color);
		SetSize(m_Size);
		m_StartColor = m_Color;

		if (m_AnimationUV.size() != 0) {
			UpdateAnimationUV(0);
			m_RenderIndex = 0;
		}
		SetActive(true);
	}
	void BCParticleSprite::SetActive(bool active) {
		if (m_IsActive != active) {
			m_IsActive = active;
		}
		m_Draw->SetDrawActive(m_IsActive);

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
	void BCParticle::SetLoop(bool flag) {
		auto particles = GetAllParticle();
		for (auto& particle : particles) {
			particle->SetLoop(flag);
		}
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
