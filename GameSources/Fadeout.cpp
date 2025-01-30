/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Fade::OnCreate() {
		m_Sprite = GetStage()->AddGameObject<Sprite>(L"FADE_TEX", Vec3(-640, 400, 0), Vec2(1280, 800));
		if (m_IsFadeOut) {
			m_FadeColor = Col4(1, 1, 1, 0);
		}
		else {
			m_FadeColor = Col4(1, 1, 1, 1);
		}
		m_Sprite->SetDiffuse(m_FadeColor);
	}

	void Fade::OnUpdate() {
		float elapsed = App::GetApp()->GetElapsedTime();
		m_Alpha = m_Sprite->GetDiffuse().w;
		if (m_IsFinished) {
			if (m_IsDestroy) {
				GetStage()->RemoveGameObject<Fade>(GetThis<Fade>());
			}
			else {
				return;
			}
		}

		if (!m_IsFadeOut) {
			m_Alpha -= m_FadeOutSpeed * elapsed;
			if (m_Alpha < 0.0f) {
				m_Alpha = 0.0f;
				m_IsFinished = true;
			}
		}
		else {
			m_Alpha += m_FadeOutSpeed * elapsed;
			if (m_Alpha > 1.0f) {
				m_Alpha = 1.0f;
				m_IsFinished = true;
			}
		}
		m_FadeColor.w = m_Alpha;
		m_Sprite->SetDiffuse(m_FadeColor);
	}

}
//end basecross
