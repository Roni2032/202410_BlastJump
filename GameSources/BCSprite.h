/*!
@file BCSprite.h
@brief スプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	struct SpriteAnimation {
		int m_OrderCount;
		float m_AnimationTime;
		float m_UpdateInterval;
		bool m_IsLoop;
		bool m_IsReverse;

		vector<int> m_Order;
		void EndAnimation() {
			if (m_IsReverse) {
				m_OrderCount = m_Order.size() - 1;
			}
			else {
				m_OrderCount = 0;
			}
		}
		SpriteAnimation() {
			m_Order = {};
			m_OrderCount = 0;
			m_AnimationTime = 0;
			m_UpdateInterval = 0;
			m_IsLoop = false;
			m_IsReverse = false;
		}
		SpriteAnimation(vector<int> order, float time, float interval, const bool isLoop = false, const bool isReverse = false){
			m_Order = order;
			m_OrderCount = 0;
			m_AnimationTime = time;
			m_UpdateInterval = interval;
			m_IsLoop = isLoop;
			m_IsReverse = isReverse;
		}

		SpriteAnimation(int startOrder,int endOrder,float time,float interval,const bool isLoop = false,const bool isReverse = false){
			vector<int> order;
			for (int i = startOrder;i <= endOrder;i++) {
				order.push_back(i);
			}
			m_Order = order;
			m_OrderCount = 0;
			m_AnimationTime = time;
			m_UpdateInterval = interval;
			m_IsLoop = isLoop;
			m_IsReverse = isReverse;
		}
	};
	//----------------------------------------------------------
	//
	//	画像表示クラス						
	//																																
	//----------------------------------------------------------
	class BCSprite : public GameObject {
		//テクスチャキー
		wstring m_TexKey;
		//サイズ
		Vec2 m_Size;
		//位置
		Vec3 m_Pos;
		//表示基を中心にするか
		bool m_IsUseCenterSprite;
		//アニメーションがあるか
		bool m_IsAnimation;
		//アニメーション切り替え時間
		float m_AnimationChangeTime;
		//アニメーション切り替え時間計測
		float m_AnimationTimer;
		//使用するアニメーションのコマ数
		int m_UseIndex;
		//現在のコマ
		int m_Index;
		//画像の切り取り数
		Vec2 m_cutUV;
		//アニメーションのUV
		vector<vector<Vec2>> m_AnimationUV;
		//頂点
		vector<VertexPositionColorTexture> m_Vertices;
		//描画コンポーネント
		shared_ptr<PCTSpriteDraw> m_Draw;
		//位置コンポーネント
		shared_ptr<Transform> m_Transform;
		//スクリーンサイズ
		Vec2 m_ScreenSize;

		map<wstring, SpriteAnimation> m_Animations;
		SpriteAnimation m_CurrentAnimation;
		SpriteAnimation m_BeforeAnimation;

		//アニメーション処理
		void Animation();
		void NewAnimation();
	public:
		BCSprite(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,Vec2 size,const bool useCenter = false) : BCSprite(ptr,texKey,pos,size,{1,1},useCenter,1,-1,false) {}
		BCSprite(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec2 size, Vec2 cutUV, const bool useCenter = false, const float changeTime = 0.5f, const int useIndex = -1, const bool isAnimation = true) :
			GameObject(ptr),
			m_TexKey(texKey),
			m_Pos(pos), m_Size(size),
			m_cutUV(cutUV),
			m_IsUseCenterSprite(useCenter),
			m_Index(0), m_UseIndex(useIndex),
			m_IsAnimation(isAnimation),
			m_AnimationChangeTime(changeTime), m_AnimationTimer(0.0f),
			m_ScreenSize(0, 0)
			{}
		virtual ~BCSprite(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		//UVの切り替え
		void UpdateUV(vector<Vec2> uv);
		//サイズの切り替え
		void UpdateSize(Vec3 size);
		void UpdateSize(Vec2 size);
		//位置の切り替え
		void SetPos(Vec3 pos);
		
		void SetDiffuse(Col4 color);
		Col4 GetDiffuse();
		//----------------------------------------------------------
		//
		//	アニメーション操作		
		//																																
		//----------------------------------------------------------
		SpriteAnimation GetBeforeAnimation() {
			return m_BeforeAnimation;
		}
		SpriteAnimation GetCurrentAnimation() {
			return m_CurrentAnimation;
		}
		SpriteAnimation GetAnimation(const wstring& key) {
			if (m_Animations.find(key) != m_Animations.end()) {
				return m_Animations[key];
			}
			return SpriteAnimation();
		}
		void SetCurrentAnimation(const wstring& key) {
			if (m_Animations.find(key) != m_Animations.end()) {
				m_CurrentAnimation.EndAnimation();
				m_BeforeAnimation = m_CurrentAnimation;
				m_CurrentAnimation = m_Animations[key];
			}
		}
		void AddAnimation(const wstring& key, int startOrder, int endOrder, float time, float interval, const bool isLoop = false, const bool isReverse = false) {
			SpriteAnimation animation = SpriteAnimation(startOrder, endOrder, time, interval, isLoop, isReverse);
			m_Animations.insert(pair<wstring, SpriteAnimation>(key, animation));
		}
		void AddAnimation(const wstring& key, vector<int> order, float time, float interval, const bool isLoop = false, const bool isReverse = false) {
			SpriteAnimation animation = SpriteAnimation(order, time, interval, isLoop, isReverse);
			m_Animations.insert(pair<wstring, SpriteAnimation>(key, animation));
		}
		void UpdateAnimationData(const wstring& key, SpriteAnimation newAnimation) {
			if (m_Animations.find(key) != m_Animations.end()) {
				m_Animations[key] = newAnimation;
			}
		}
		//----------------------------------------------------------
		//
		//	位置設定テンプレート		
		//																																
		//----------------------------------------------------------
		void ScreenCenter(const Vec2 diff = Vec2(0,0));
		void ScreenTop(const Vec2 diff = Vec2(0, 0));
		void ScreenTopLeft(const Vec2 diff = Vec2(0, 0));
		void ScreenTopRight(const Vec2 diff = Vec2(0, 0));
		void ScreenBottom(const Vec2 diff = Vec2(0, 0));
		void ScreenBottomLeft(const Vec2 diff = Vec2(0, 0));
		void ScreenBottomRight(const Vec2 diff = Vec2(0, 0));
		void ScreenLeft(const Vec2 diff = Vec2(0, 0));
		void ScreenRight(const Vec2 diff = Vec2(0, 0));
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
	//	< 使い方 >
	//  AddComponentで使いたい派生クラスを設定
	//  Play() : 更新
	//  Stop() : 停止																				
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

		bool IsPlay() {
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

		bool IsFadeOut() {
			return m_IsFadeOut;
		}
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
