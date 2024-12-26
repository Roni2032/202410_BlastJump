/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	vector<shared_ptr<Button>> Button::Buttons = {};
	void Button::OnCreate() {
		m_Sprite = GetStage()->AddGameObject<BCSprite>(m_TexKey, m_Pos, m_Size,true);
		Button::Buttons.push_back(GetThis<Button>());
	}
	void Button::OnUpdate() {
		for (auto& mode : m_Effect) {
			if (m_IsSelect) {
				switch (mode) {
				case SelectEffect::Expand:
					m_Sprite->UpdateSize(m_Size * 1.1f);
					break;
				case SelectEffect::Animation:
					break;
				}
			}
			else {
				m_Sprite->UpdateSize(m_Size);
			}
		}
		
	}
}
//end basecross
