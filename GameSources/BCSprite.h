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

		bool m_IsUseCenterSprite;
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
		BCSprite(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,Vec2 size,const bool useCenter = false) : BCSprite(ptr,texKey,pos,size,{1,1},useCenter,1,-1,false) {}
		BCSprite(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec2 size,Vec2 cutUV, const bool useCenter = false,const float changeTime = 0.5f,const int useIndex = -1,const bool isAnimation = true) :
			GameObject(ptr),
			m_TexKey(texKey),
			m_Pos(pos),m_Size(size),
			m_cutUV(cutUV),
			m_IsUseCenterSprite(useCenter),
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
		
		void SetDiffuse(Col4 color);
		Col4 GetDiffuse();

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
			m_DisplayDigit(displayDigit),m_DisplayNumber(1234), m_CutNum(cutNum)
		{}
		virtual ~BCNumber(){}

		virtual void OnCreate();
		virtual void OnUpdate();
		
		void UpdateNumber(int number);
	};

	//----------------------------------------------------------
	//																																
	//	Sprite操作コンポーネントクラス																										
	//																																
	//----------------------------------------------------------
	class SpriteAction : public Component {
		bool m_IsPlay;
	protected:
		shared_ptr<SpriteBaseDraw> m_Draw;
		shared_ptr<Transform> m_Trans;
	public:
		SpriteAction(const shared_ptr<GameObject>& ptr) : Component(ptr),m_IsPlay(true){}
		virtual ~SpriteAction() {}

		virtual void OnCreate()override;
		virtual void OnDraw()override {}

		void Play() {
			m_IsPlay = true;
		}
		void Stop() {
			m_IsPlay = false;
		}

		bool GetIsPlay() {
			return m_IsPlay;
		}
	};
	//----------------------------------------------------------
	//																																
	//	Sprite操作 : 点滅																								
	//																																
	//----------------------------------------------------------
	class SpriteFlash : public SpriteAction {
		float m_FlashSpeed;
	public:
		SpriteFlash(const shared_ptr<GameObject>& ptr,float flashSpeed) : SpriteAction(ptr),
			m_FlashSpeed(flashSpeed){}
		virtual ~SpriteFlash(){}

		virtual void OnUpdate()override;

		void SetFlashSpeed(float flashSpeed) {
			m_FlashSpeed = flashSpeed;
		}

	};
	//----------------------------------------------------------
	//																																
	//	Sprite操作 : 拡大縮小																								
	//																																
	//----------------------------------------------------------
	class SpriteScaling : public SpriteAction {
		float m_ScalingSpeed;
		Vec3 defaultSize;
		float m_Ratio;
		float m_MaxRatio;
		float m_MinRatio;

	public:
		SpriteScaling(const shared_ptr<GameObject>& ptr, float scalingSpeed, float max, float min) : SpriteAction(ptr), 
			m_ScalingSpeed(scalingSpeed), m_MaxRatio(max), m_MinRatio(min),defaultSize(0,0,0),m_Ratio(1.0f) {}
		virtual ~SpriteScaling() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetScalingSpeed(float scalingSpeed) {
			m_ScalingSpeed = scalingSpeed;
		}
		void SetMax(float max) {
			m_MaxRatio = max;
		}
		void SetMin(float min) {
			m_MinRatio = min;
		}

	};
	//----------------------------------------------------------
	//																																
	//	Sprite操作 : フェードイン・フェードアウト																								
	//																																
	//----------------------------------------------------------
	class SpriteFade : public SpriteAction {
		float m_FadeSpeed;
		bool m_IsFadeOut;
		bool m_IsFinished;
	public:
		SpriteFade(const shared_ptr<GameObject>& ptr,float fadeSpeed) : SpriteAction(ptr),m_FadeSpeed(fadeSpeed),m_IsFadeOut(true),m_IsFinished(false){}
		virtual ~SpriteFade(){}

		virtual void OnUpdate()override;

		void FadeOut() {
			m_IsFadeOut = true;
		}
		void FadeIn() {
			m_IsFadeOut = false;
		}
		bool IsFinish() {
			return m_IsFinished;
		}
	};
}
//end basecross
