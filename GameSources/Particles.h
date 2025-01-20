/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"
#include "BCParticle.h"

namespace basecross{
	class ExplodeParticle : public BCParticle {
	public:
		ExplodeParticle(const shared_ptr<Stage>& ptr) : BCParticle(ptr) {}
		virtual ~ExplodeParticle() {}

		virtual void AddParticleData()override;

	};
	
	class BlockDestroyParticle : public BCParticle {
	public:
		BlockDestroyParticle(const shared_ptr<Stage>& ptr) : BCParticle(ptr) {}
		virtual ~BlockDestroyParticle() {}

		virtual void AddParticleData()override;

	};

	class ExplodeAoE : public BCParticle {
	public:
		ExplodeAoE(const shared_ptr<Stage>& ptr) : BCParticle(ptr) {}
		virtual ~ExplodeAoE() {}

		virtual void AddParticleData()override;

	};

	class ParticleRunDust : public BCParticle
	{
	public:
		ParticleRunDust(const shared_ptr<Stage>& ptr) : BCParticle(ptr) {}
		virtual ~ParticleRunDust() {}

		virtual void AddParticleData() override;

	};

	class ParticleGoal : public BCParticle
	{
	public:
		ParticleGoal(const shared_ptr<Stage>& ptr) : BCParticle(ptr) {}
		virtual ~ParticleGoal() {}

		virtual void AddParticleData() override;


	};
}
//end basecross
