/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void ExplodeParticle::AddParticleData() {
		vector<Col4> colorPattern = {
			Col4(1, 0, 0, 1),
			Col4(1, 0.2f, 0.2f, 1),
			Col4(1, 0.5f, 0, 1),
		};

		auto particles = AddParticle(128, L"EXPLODE1_TEX");
		for (auto& particle : particles) {
			float time = Util::RandZeroToOne() * 0.5f;
			particle->SetDelay(0.1f);
			particle->SetMaxTime(time);
			particle->SetSize(Vec3(0.2f));
			particle->SetScaleVelocity(Vec3(2.0f));
			particle->AutoCutAnimationUV(Vec2(3, 2));
			particle->SetAnimationTime(time);
			particle->SetDecelerationRate(0.3f);
			int rnd = rand() % 3;
			particle->SetBaseColor(colorPattern[rnd]);
			particle->SetTargetColor(Col4(0.627f, 0.627f, 0.627f, 1));
			particle->SetColorChangeTime(0.4f);
			particle->SetRotateMovement(false);
			particle->SetVelocity(Vec3(
				Util::RandZeroToOne() * 3.0f - 1.5f,
				Util::RandZeroToOne() * 3.0f - 1.5f,
				Util::RandZeroToOne() * 3.0f - 1.5f
			));
		}

	}

	void BlockDestroyParticle::AddParticleData() {
		auto particles = AddParticle(16, L"TEST_TEX");
		for (auto& particle : particles) {
			particle->SetMaxTime(0.5f);
			float uvSize = Util::RandZeroToOne() * 0.5f + 0.5f;
			float startUv = Util::RandZeroToOne();
			particle->AddAnimationUV({{ startUv,startUv },{ startUv + uvSize,startUv },{ startUv, startUv + uvSize },{ startUv + uvSize,startUv + uvSize }
				});

			particle->SetColor(Col4(1, 1.0f, 1.0f, 1));
			particle->SetSize(Vec3(0.2f,0.1f,0.2f));
			particle->SetGravity(-4.9f);
			particle->SetVelocity(Vec3(
				Util::RandZeroToOne() * 4.0f - 2.0f,
				Util::RandZeroToOne() * 4.0f - 1.0f,
				Util::RandZeroToOne() * 4.0f - 2.0f
			));
		}

	}

	void ExplodeAoE::AddParticleData() {

	}

	void ParticleRunDust::AddParticleData()
	{
		auto particles = AddParticle(128, L"EXPLODE1_TEX");
		for (auto& particle : particles) 
		{
			float time = Util::RandZeroToOne() * 0.5f;
			particle->SetDelay(0.1f);
			particle->SetMaxTime(time);
			particle->SetSize(Vec3(0.2f));
			particle->SetScaleVelocity(Vec3(0.35f));
			particle->AutoCutAnimationUV(Vec2(3, 2));
			particle->SetAnimationTime(time);
			particle->SetDecelerationRate(0.3f);
			int rnd = rand() % 3;
			particle->SetTargetColor(Col4(0.627f, 0.627f, 0.627f, 1.0f));
			particle->SetColorChangeTime(0.4f);
			particle->SetRotateMovement(false);
			particle->SetVelocity(Vec3
			(
				Util::RandZeroToOne() * 3.0f - 1.5f,
				Util::RandZeroToOne() * 3.0f - 1.5f,
				Util::RandZeroToOne() * 3.0f - 1.5f
			));

		}

	}

	void ParticleGoal::AddParticleData()
	{
		vector<Col4> colorPattern = 
		{
			Col4(1.0, 0.0, 0.0, 1.0),
			Col4(1.0, 0.5, 0.0, 1.0),
			Col4(1.0, 1.0, 0.0, 1.0),
			Col4(0.0, 0.5, 0.0, 1.0),
			Col4(0.0, 0.0, 1.0, 1.0),
			Col4(0.5, 0.0, 0.5, 1.0) 
		};

		auto particles = AddParticle(128, L"EXPLODE1_TEX");
		for (auto& particle : particles) {
			float time = Util::RandZeroToOne() * 0.5f;
			particle->SetDelay(0.1f);
			particle->SetMaxTime(time);
			particle->SetSize(Vec3(0.2f));
			particle->SetScaleVelocity(Vec3(5.0f));
			particle->AutoCutAnimationUV(Vec2(3, 2));
			particle->SetAnimationTime(time);
			particle->SetDecelerationRate(0.3f);
			int rnd = rand() % 3;
			particle->SetBaseColor(colorPattern[rnd]);
			particle->SetTargetColor(Col4(0.627f, 0.627f, 0.627f, 1.0f));
			particle->SetColorChangeTime(0.4f);
			particle->SetRotateMovement(false);
			particle->SetVelocity(Vec3(
				Util::RandZeroToOne() * 3.0f - 1.5f,
				Util::RandZeroToOne() * 3.0f - 1.5f,
				Util::RandZeroToOne() * 3.0f - 1.5f
			));
		}

	}

}
//end basecross
