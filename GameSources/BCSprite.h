/*!
@file BCSprite.h
@brief スプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	//----------------------------------------------------------
	//
	//	画像表示クラス						
	//																																
	//----------------------------------------------------------
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


	//----------------------------------------------------------
	//																																
	//	数値表示クラス																												
	//																																
	//----------------------------------------------------------
	class BCNumber : public GameObject {
		vector<shared_ptr<BCSprite>> m_Numbers;
		int m_CutNum;
		int m_DisplayNumber;
		int m_DisplayDigit;

		wstring m_TexKey;
		Vec3 m_Pos;
		Vec2 m_Size;

		vector<Vec2> GetUV(int displayDigit);
	public:
		BCNumber(const shared_ptr<Stage>& ptr,const wstring& texKey) : BCNumber(ptr,texKey,Vec3(0,0,0),Vec2(200,100),8){}
		BCNumber(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,Vec2 size,int displayDigit) : BCNumber(ptr, texKey, pos, size, displayDigit,10) {}
		BCNumber(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec2 size, int displayDigit,int cutNum) : 
			GameObject(ptr) ,
			m_TexKey(texKey),
			m_Pos(pos),m_Size(size),
			m_DisplayDigit(displayDigit),m_DisplayNumber(0), m_CutNum(cutNum)
		{}
		virtual ~BCNumber(){}

		virtual void OnCreate();
		virtual void OnUpdate();
		
		void UpdateNumber(int number);
	};
}
//end basecross
