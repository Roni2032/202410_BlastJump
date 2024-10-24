/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class ExplodeParticle : public BCParticle {
	public:
		ExplodeParticle(const shared_ptr<Stage>& ptr,const shared_ptr<Transform>& parent) : BCParticle(ptr,parent) {}
		virtual ~ExplodeParticle() {}

		virtual void AddParticleData()override;

	};
	
}
//end basecross
