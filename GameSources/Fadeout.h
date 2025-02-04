/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Sprite;

	class Fade : public GameObject {
		shared_ptr<Sprite> m_Sprite;
		Col4 m_FadeColor;
		float m_Alpha;
		float m_FadeOutSpeed;

		bool m_IsFinished;
		bool m_IsFadeOut;
		bool m_IsDestroy;
	public:
		Fade(const shared_ptr<Stage>& ptr,float speed,const bool fadeout = true):
			GameObject(ptr),
			m_Alpha(1.0f),
			m_FadeOutSpeed(speed),
			m_IsFadeOut(fadeout),
			m_IsFinished(false),
			m_IsDestroy(false)
		{}
		virtual ~Fade(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetFadeColor(Col4 color) {
			m_FadeColor = color;
		}
		void SetDestroy(bool flag) {
			m_IsDestroy = flag;
		}
		bool IsFinished() {
			return m_IsFinished;
		}
	};
}
//end basecross
