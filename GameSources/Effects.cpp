/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void DefaultEffect::OnCreate() {
		SetAddType(true);
		AddEffects();
	}
	void DefaultEffect::AddEffects() {
		Effect testEffect = {
			L"NUMBER_TEX",
			32,1.0f,
			Vec3(1,1,1),Col4(1,1,1,1),
			Scope(Vec3(-1,-1,-1),Vec3(1,1,1)),
			Scope(Vec3(-5,-5,-5),Vec3(5,5,5))
		};

		m_Effects.push_back(testEffect);
	}
	void DefaultEffect::InsertFire(const Vec3& Pos) {
		for (auto& effect : m_Effects) {
			if (effect.m_TexKey == L"") continue;

			auto ptrParticle = InsertParticle(effect.m_InsertParticles);
			ptrParticle->SetEmitterPos(Pos);
			ptrParticle->SetTextureResource(effect.m_TexKey);
			ptrParticle->SetMaxTime(effect.m_drawTime);
			for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
				rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * (effect.m_StartPosScope.m_Max.x - effect.m_StartPosScope.m_Min.x) + effect.m_StartPosScope.m_Min.x;
				rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * (effect.m_StartPosScope.m_Max.y - effect.m_StartPosScope.m_Min.y) + effect.m_StartPosScope.m_Min.y;
				rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * (effect.m_StartPosScope.m_Max.z - effect.m_StartPosScope.m_Min.z) + effect.m_StartPosScope.m_Min.z;

				rParticleSprite.m_LocalScale = effect.m_LocalScale;

				rParticleSprite.m_Velocity = Vec3(
					Util::RandZeroToOne() * (effect.m_VelocityScope.m_Max.x - effect.m_VelocityScope.m_Min.x) + effect.m_VelocityScope.m_Min.x,
					Util::RandZeroToOne() * (effect.m_VelocityScope.m_Max.y - effect.m_VelocityScope.m_Min.y) + effect.m_VelocityScope.m_Min.y,
					Util::RandZeroToOne() * (effect.m_VelocityScope.m_Max.z - effect.m_VelocityScope.m_Min.z) + effect.m_VelocityScope.m_Min.z);

				rParticleSprite.m_Color = effect.m_Color;
			}
		}
	}
}
//end basecross
