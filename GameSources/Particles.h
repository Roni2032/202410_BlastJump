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
}
//end basecross
