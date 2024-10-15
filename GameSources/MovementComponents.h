/*!
@file MovementComponents.h
@brief ˆÚ“®—p
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Movement : public Component {
		Vec3 m_targetPosition;
		vector<Vec3> m_targetList;
		float m_speed;
	public:
		explicit Movement(const shared_ptr<GameObject>& ObjPtr) : Movement(ObjPtr,5,{}) {}
		explicit Movement(const shared_ptr<GameObject>& ObjPtr,float speed) :Movement(ObjPtr, speed, {}) {}
		explicit Movement(const shared_ptr<GameObject>& ObjPtr,vector<Vec3> targetList) :Movement(ObjPtr, 5, targetList) {}

		explicit Movement(const shared_ptr<GameObject>& ObjPtr,float speed,vector<Vec3> targetList) :Component(ObjPtr),m_speed(speed),m_targetList(targetList) {}

		virtual ~Movement() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override {}

		void AddTarget(int order, Vec3 pos);
		void AddTarget(Vec3 pos);

		void SetSpeed(float speed);
	};

	class BCSprite : public GameObject {
		wstring m_TexKey;

		bool m_IsAnimation;
		float m_AnimationChangeTime;
		float m_AnimationTimer;

		int m_UseIndex;
		int m_Index;

		Vec2 m_cutUV;
		vector<vector<Vec2>> m_AnimationUV;
		
		vector<VertexPositionColorTexture> m_Vertices;
		shared_ptr<PCTSpriteDraw> m_Draw;
		shared_ptr<Transform> m_Transform;
	public:
		BCSprite(const shared_ptr<Stage>& ptr,wstring& texKey) : BCSprite(ptr,texKey,{1,1},1) {}
		BCSprite(const shared_ptr<Stage>& ptr, wstring& texKey,Vec2 cutUV,const int useIndex ,float changeTime ,const bool isAnimation = true) : 
			GameObject(ptr),
			m_TexKey(texKey),
			m_cutUV(cutUV),
			m_Index(0), m_UseIndex(useIndex), 
			m_IsAnimation(isAnimation),
			m_AnimationChangeTime(changeTime),m_AnimationTimer(0.0f)
			{}
		virtual ~BCSprite(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Animation();
		void UpdateUV(vector<Vec2> uv);
	};

}
//end basecross
