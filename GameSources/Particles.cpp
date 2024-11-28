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
		/*auto particles = AddParticleInstance(32, L"EXPLODE1_TEX");
		particles->SetMaxTime(1.0f);
		particles->SetColor(Col4(1, 0.485f, 0.276f, 1));
		for (auto& particle : particles->GetSpriteDate()) {
			particle.SetVelocity(Vec3(
				Util::RandZeroToOne() * 2.0f - 1.0f,
				Util::RandZeroToOne() * 2.0f - 1.0f,
				Util::RandZeroToOne() * 2.0f - 1.0f
			));
		}
		particles = AddParticleInstance(32, L"EXPLODE2_TEX");
		particles->SetMaxTime(1.0f);
		particles->SetColor(Col4(1, 0.0f, 0.0f, 1));
		for (auto& particle : particles->GetSpriteDate()) {
			particle.SetVelocity(Vec3(
				Util::RandZeroToOne() * 1.0f - 0.5f,
				Util::RandZeroToOne() * 1.0f - 0.5f,
				Util::RandZeroToOne() * 1.0f - 0.5f
			));
		}*/
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

		particles = AddParticle(32, L"EXPLODE_SPARK_TEX");
		for (auto& particle : particles) {
			particle->SetMaxTime(0.75f);
			particle->SetBaseColor(Col4(1, 1, 0, 1));
			particle->SetTargetColor(Col4(1, 0, 0, 1));
			particle->SetColorChangeTime(0.5f);
			particle->SetScaleVelocity(Vec3(0, -1.25f, 0));
			particle->SetDecelerationRate(0.2f);
			particle->SetGravity(-2.0f);

			float sizeY = Util::RandZeroToOne() * 1.0f + 0.2f;
			particle->SetSize(Vec3(0.2f, sizeY, 0.2f));
			Vec3 velocity = Vec3(
				Util::RandZeroToOne() * 5.0f - 2.5f,
				Util::RandZeroToOne() * 5.0f - 2.5f,
				Util::RandZeroToOne() * 5.0f - 2.5f
			);
			particle->SetVelocity(velocity);

			float distance = Util::RandZeroToOne() * 0.5f;

			particle->SetStartPos(distance * velocity.normalize());
		}
	}

	void BlockDestroyParticle::AddParticleData() {
		auto particles = AddParticle(16, L"TEST_TEX");
		for (auto& particle : particles) {
			particle->SetMaxTime(1.0f);
			particle->SetColor(Col4(1, 1.0f, 1.0f, 1));
			particle->SetSize(Vec3(0.2f,0.1f,0.2f));
			particle->SetGravity(-4.9f);
			particle->SetVelocity(Vec3(
				Util::RandZeroToOne() * 4.0f - 2.0f,
				Util::RandZeroToOne() * 4.0f - 2.0f,
				Util::RandZeroToOne() * 4.0f - 2.0f
			));
		}
	}

	void ExplodeAoE::AddParticleData() {

	}
}
//end basecross
