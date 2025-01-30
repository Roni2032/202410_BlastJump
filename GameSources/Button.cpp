/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	vector<shared_ptr<Button>> Button::Buttons = {};
	void Button::OnCreate() {
		m_Sprite = GetStage()->AddGameObject<Sprite>(m_TexKey, m_Pos, m_Size,true);
		Button::Buttons.push_back(GetThis<Button>());
	}
	void Button::OnUpdate() {
		for (auto& mode : m_Effect) {
			if (m_IsSelect) {
				switch (mode) {
				case SelectEffect::Expand:
					m_Sprite->UpdateSize(m_Size * 1.1f);
					for (auto& sprite : m_InterLockSprite) {
						if (m_InterLockedSpriteSize.size() == 0) {
							Vec2 size = sprite->GetSize();
							m_InterLockedSpriteSize.push_back(size);
							sprite->UpdateSize(size * 1.1f);
						}
					}
					break;
				case SelectEffect::Animation:
					break;
				case SelectEffect::ChangeSprite:
					m_Sprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(m_SelectTexKey);
					break;
				}
			}
			else {
				for (int i = 0; i < m_InterLockSprite.size();i++) {
					if (m_InterLockedSpriteSize.size() != 0) {
						m_InterLockSprite[i]->UpdateSize(m_InterLockedSpriteSize[i]);
					}
				}
				m_Sprite->UpdateSize(m_Size);
				m_Sprite->GetComponent<PCTSpriteDraw>()->SetTextureResource(m_TexKey);
			}
		}
		
	}
}
//end basecross
