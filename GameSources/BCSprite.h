/*!
@file MovementComponents.h
@brief ˆÚ“®—p
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class BCSprite : public GameObject {
		wstring m_TexKey;
		Vec2 m_Size;
		Vec3 m_Pos;

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
		BCSprite(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,Vec2 size) : BCSprite(ptr,texKey,pos,size,{1,1},1) {}
		BCSprite(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec2 size,Vec2 cutUV,const float changeTime = 0.5f,const int useIndex = -1,const bool isAnimation = true) :
			GameObject(ptr),
			m_TexKey(texKey),
			m_Pos(pos),m_Size(size),
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
		void UpdateSize(Vec3 size);
		void UpdateSize(Vec2 size);

		void SetPos(Vec3 pos);
		void SetInterval(float interval);
		void SetUseIndex(int useIndex);
		
	};

}
//end basecross
