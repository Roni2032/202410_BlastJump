/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class BCParticleSprite : public GameObject {
		shared_ptr<PNTStaticDraw> m_Draw;
		shared_ptr<Camera> m_Camera;
		shared_ptr<Transform> m_Trans;
		weak_ptr<Transform> m_ParentTrans;

		wstring m_TexKey = L"";
		Vec3 m_StartPos = Vec3(0,0,0);
		Vec3 m_BaseVelocity = Vec3(0,0,0);
		Vec3 m_Velocity = Vec3(0,0,0);
		Vec3 m_Size = Vec3(1,1,1);
		Col4 m_Color = Col4(1.0f,1.0f,1.0f,1.0f);
		BetWeen m_Alpha;
		float m_MaxTime = 2.0f;
		float m_TotalTime = 0.0f;
		float m_Gravity = 0.0f;

		bool m_IsActive = false;
		void Init();
	public:
		BCParticleSprite(const shared_ptr<Stage>& ptr,const wstring& key):GameObject(ptr),m_TexKey(key), m_Alpha(BetWeen(1.0f, 0.0f)) {}
		virtual ~BCParticleSprite(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void StartParticle(const Vec3 pos);
		void SetActive(bool active);

		void SetTexture(const wstring& key) {
			m_TexKey = key;
		}
		void SetMaxTime(float time) {
			m_MaxTime = time;
		}
		void SetColor(Col4 color);
		
		void SetVelocity(Vec3 velocity) {
			m_Velocity = velocity;
			m_BaseVelocity = velocity;
		}
		void SetSize(Vec3 size);
		void SetStartPos(Vec3 start) {
			m_StartPos = start;
		}
		void SetGravity(float gravity);
		void SetParent(shared_ptr<Transform> transform) {
			m_ParentTrans = transform;
		}
	};

	class BCParticle : public GameObject {

		vector<shared_ptr<BCParticleSprite>> m_ParticleSprites;
		shared_ptr<Transform> m_Trans;
	protected:
		shared_ptr<Transform> m_Parent;
	public:
		BCParticle(const shared_ptr<Stage>& ptr,const shared_ptr<Transform>& parent = nullptr) : GameObject(ptr),m_Parent(parent){}
		virtual ~BCParticle(){}

		virtual void OnCreate();
		vector<shared_ptr<BCParticleSprite>> AddParticle(int num,const wstring& key);
		//void ClearParticle();
		vector<shared_ptr<BCParticleSprite>> GetAllParticle() {
			return m_ParticleSprites;
		}
		virtual void AddParticleData();
		void Shot(const Vec3 pos = Vec3(0,0,0));
	};
}
//end basecross
