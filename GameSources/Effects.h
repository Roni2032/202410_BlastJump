/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	using Scope = AABB;

	struct Effect {
		int m_InsertParticles;
		wstring m_TexKey;
		float m_drawTime;
		Vec3 m_LocalScale;
		Col4 m_Color;
		Scope m_VelocityScope;
		Scope m_StartPosScope;
		

		Effect() : Effect(L"",0,0.0f,{1,1,1},{1,1,1,1},{{0,0,0},{1,1,1}},{{0,0,0},{1,1,1}}) {}
		Effect(const wstring& texKey,int insertParticles,float drawTime,Vec3 localScale,Col4 color, Scope randStart, Scope randVelocity) :
			m_TexKey(texKey),
			m_InsertParticles(insertParticles),
			m_drawTime(drawTime),
			m_LocalScale(localScale),m_StartPosScope(randStart),m_VelocityScope(randVelocity),
			m_Color(color)
		{}
	};
	class DefaultEffect : public MultiParticle {
		bool m_IsTracking;

		float m_AlphaStart;
		float m_AlphaEnd;
	protected:
		vector<Effect> m_Effects;
		virtual void AddEffects();
	public:
		//構築と破棄
		DefaultEffect(shared_ptr<Stage>& ptr,bool isTracking, const float start = 1.0f, const float end = 1.0f):
			MultiParticle(ptr),m_IsTracking(isTracking),
			m_AlphaStart(start),
			m_AlphaEnd(end)
		{}
		virtual ~DefaultEffect() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos);
	};


	class BombEffect : public DefaultEffect {
	protected:
		virtual void AddEffects()override;
	public:
		BombEffect(shared_ptr<Stage>& ptr, bool isTracking, const float start = 1.0f, const float end = 1.0f) :
			DefaultEffect(ptr,isTracking,start,end)
		{}
		virtual ~BombEffect() {}
	};
}
//end basecross
