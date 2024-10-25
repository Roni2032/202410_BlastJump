/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void ExplodeParticle::AddParticleData() {
		auto particles = AddParticle(32, L"EXPLODE1_TEX");
		for (auto& particle : particles) {
			particle->SetMaxTime(1.0f);
			particle->SetColor(Col4(1, 0.485f, 0.276f, 1));
			//particle->SetGravity(-4.9f);
			particle->SetVelocity(Vec3(
				Util::RandZeroToOne() * 2.0f - 1.0f,
				Util::RandZeroToOne() * 2.0f - 1.0f,
				Util::RandZeroToOne() * 2.0f - 1.0f
			));
		}

		particles = AddParticle(32, L"EXPLODE2_TEX");
		for (auto& particle : particles) {
			particle->SetMaxTime(1.0f);
			particle->SetColor(Col4(1, 0.0f, 0.0f, 1));
			//particle->SetGravity(-4.9f);
			particle->SetVelocity(Vec3(
				Util::RandZeroToOne() * 1.0f - 0.5f,
				Util::RandZeroToOne() * 1.0f - 0.5f,
				Util::RandZeroToOne() * 1.0f - 0.5f
			));
		}
	}

	void BlockDestroyParticle::AddParticleData() {
		auto particles = AddParticle(16, L"TEST_TEX");
		for (auto& particle : particles) {
			particle->SetMaxTime(1.0f);
			particle->SetColor(Col4(1, 1.0f, 1.0f, 1));
			particle->SetSize(Vec3(0.25f));
			particle->SetGravity(-4.9f);
			particle->SetVelocity(Vec3(
				Util::RandZeroToOne() * 4.0f - 2.0f,
				Util::RandZeroToOne() * 4.0f - 2.0f,
				Util::RandZeroToOne() * 4.0f - 2.0f
			));
		}
	}
}
//end basecross
