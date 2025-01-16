/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	struct BCParticleSpriteData {
		Mat4x4 matrix;
		Vec3 m_StartPos;
		Vec3 m_BaseVelocity;
		Vec3 m_Velocity;
		Vec3 m_Size;

		BCParticleSpriteData() : 
			matrix(Mat4x4()),m_StartPos(0,0,0),m_BaseVelocity(0,0,0),m_Velocity(0,0,0),m_Size(1,1,1)
		{}
		void SetVelocity(Vec3 velocity) {
			m_Velocity = velocity;
			m_BaseVelocity = velocity;
		}
		void SetSize(Vec3 size) {
			m_Size = size;
		}
		void SetStartPos(Vec3 start) {
			m_StartPos = start;
		}
	};
	class BCParticleInstance : public GameObject {
		shared_ptr<PNTStaticInstanceDraw> m_Draw;
		shared_ptr<Camera> m_Camera;
		shared_ptr<Transform> m_Trans;
		weak_ptr<Transform> m_ParentTrans;

		wstring m_TexKey;
		vector<BCParticleSpriteData> spriteData;
		int dataNum;
		Col4 m_Color;
		BetWeen m_Alpha;
		float m_MaxTime;
		float m_TotalTime;
		float m_Gravity;

		bool m_IsActive;
		void Init();
	public:
		BCParticleInstance(const shared_ptr<Stage>& ptr, const wstring& key,int num) :
			GameObject(ptr),
			m_TexKey(key),
			m_Alpha(BetWeen(1.0f, 0.0f)),
			m_MaxTime(2.0f), m_TotalTime(0.0f), m_Gravity(0.0f),
			m_IsActive(false),
			spriteData({}),
			dataNum(num)
		{}
		virtual ~BCParticleInstance() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		vector<BCParticleSpriteData> GetSpriteDate() {
			return spriteData;
		}
		void StartParticle(const Vec3 pos);
		void SetActive(bool active);

		void SetTexture(const wstring& key) {
			m_TexKey = key;
		}
		void SetMaxTime(float time) {
			m_MaxTime = time;
		}
		void SetColor(Col4 color);

		void SetGravity(float gravity);
		void SetParent(shared_ptr<Transform> transform) {
			m_ParentTrans = transform;
		}
	};
	class BCParticleSprite : public GameObject {
		shared_ptr<PNTStaticDraw> m_Draw;
		vector<VertexPositionNormalTexture> m_Vertexes;
		shared_ptr<Camera> m_Camera;
		shared_ptr<Transform> m_Trans;
		weak_ptr<Transform> m_ParentTrans;

		wstring m_TexKey;
		Vec3 m_BaseStartPos;
		Vec3 m_StartPos;
		Vec3 m_BaseVelocity;
		Col4 m_BaseColor;
		Vec3 m_BaseScaleVelocity;
		Vec3 m_Velocity;
		Vec3 m_ScaleVelocity;
		Col4 m_TargetColor;
		Col4 m_StartColor;
		Vec3 m_Size;
		Col4 m_Color;
		BetWeen m_Alpha;
		float m_MaxTime;
		float m_TotalTime;
		float m_Gravity;
		float m_DecelerationRate;
		float m_ColorChangeTime;
		float m_DelayTime;
		float m_DelayTimer;

		bool m_IsAnimation;
		float m_AnimationTimer;
		float m_AnimationTime;
		int m_RenderIndex;
		vector<vector<Vec2>> m_AnimationUV;

		bool m_IsActive;
		bool m_IsLoop;
		bool m_IsRotateMovement;
		void Init();
	public:
		BCParticleSprite(const shared_ptr<Stage>& ptr,const wstring& key):
			GameObject(ptr),
			m_TexKey(key),
			m_Alpha(BetWeen(1.0f, 0.0f)),
			m_StartPos(0,0,0),m_BaseStartPos(0,0,0), m_BaseVelocity(0, 0, 0), m_Velocity(0, 0, 0), m_Size(1, 1, 1),
			m_Color(1,1,1,1),
			m_MaxTime(2.0f),m_TotalTime(0.0f),m_Gravity(0.0f),
			m_IsActive(false),
			m_AnimationTime(0.0f),m_AnimationTimer(0.0f),m_RenderIndex(0), m_IsAnimation(false),
			m_DecelerationRate(1.0f),
			m_TargetColor(Col4(1,1,1,1)),m_StartColor(Col4(1,1,1,1)), m_ColorChangeTime(0.0f),
			m_IsRotateMovement(true),
			m_DelayTime(0.0f),m_DelayTimer(0.0f),
			m_IsLoop(false)
		{}
		virtual ~BCParticleSprite(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void StartParticle(const Vec3 pos);
		void SetActive(bool active);

		void SetTexture(const wstring& key) {
			m_TexKey = key;
		}
		vector<vector<Vec2>> GetAnimationUV() {
			return m_AnimationUV;
		}
		void AutoCutAnimationUV(Vec2 cut);
		void SetAnimationUV(vector<vector<Vec2>> uv) {
			m_AnimationUV = uv;
		}
		void AddAnimationUV(vector<Vec2> uv) {
			m_AnimationUV.push_back(uv);
		}
		void UpdateAnimationUV(int index);
		bool GetPlayAnimation() {
			return m_IsAnimation;
		}
		void SetPlayAnimation(bool flag) {
			m_IsAnimation = flag;
		}
		float GetAnimationTime() {
			return m_AnimationTime;
		}
		void SetAnimationTime(float time) {
			m_AnimationTime = time;
		}
		float GetMaxTime() {
			return m_MaxTime;
		}
		void SetMaxTime(float time) {
			m_MaxTime = time;
		}

		void SetColor(Col4 color);

		void SetBaseColor(Col4 color) {
			SetColor(color);
			m_BaseColor = color;
		}
		
		Vec3 GetVelocity() {
			return m_Velocity;
		}
		void SetVelocity(Vec3 velocity) {
			m_Velocity = velocity;
			m_BaseVelocity = velocity;
		}
		Vec3 GetScaleVelocity() {
			return m_ScaleVelocity;
		}
		void SetScaleVelocity(Vec3 scaleVelocity) {
			m_ScaleVelocity = scaleVelocity;
			m_BaseScaleVelocity = scaleVelocity;
		}
		Col4 GetTargetColor() {
			return m_TargetColor;
		}
		void SetTargetColor(Col4 targetColor) {
			m_TargetColor = targetColor;
		}
		float GetColorChangeTime() {
			return m_ColorChangeTime;
		}
		void SetColorChangeTime(float time) {
			m_ColorChangeTime = time;
		}
		void SetSize(Vec3 size);
		void SetStartPos(Vec3 start) {
			m_BaseStartPos = start;
			m_StartPos = start;
		}
		void SetGravity(float gravity);
		void SetParent(shared_ptr<Transform> transform) {
			m_ParentTrans = transform;
		}
		float GetDecelerationRate() {
			return m_DecelerationRate;
		}
		void SetDecelerationRate(float rate) {
			m_DecelerationRate = rate;
		}

		bool GetRotateMovement() {
			return m_IsRotateMovement;
		}
		void SetRotateMovement(bool flag) {
			m_IsRotateMovement = flag;
		}

		void SetDelay(float time) {
			m_DelayTime = time;
		}

		void SetLoop(bool flag) {
			m_IsLoop = flag;
		}
	};

	class BCParticle : public GameObject {

		vector<shared_ptr<BCParticleSprite>> m_ParticleSprites;
		vector<shared_ptr<BCParticleInstance>> m_ParticleInstance;
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
		shared_ptr<BCParticleInstance> AddParticleInstance(int num, const wstring& key);
		vector<shared_ptr<BCParticleInstance>> GetAllParticleInstance() {
			return m_ParticleInstance;
		}
		void SetLoop(bool flag);
		virtual void AddParticleData(){}
		void Shot(const Vec3 pos = Vec3(0,0,0));

		void SetParent(shared_ptr<Transform>& parent) {
			m_Parent = parent;
		}
	};
}
//end basecross
