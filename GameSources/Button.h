/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	enum SelectEffect {
		Expand,
		Animation,
	};
	class Button : public GameObject {
		shared_ptr<BCSprite> m_Sprite;
		wstring m_TexKey;
		Vec3 m_Pos;
		Vec2 m_Size;
		vector<SelectEffect> m_Effect;

		bool m_IsSelect;
	public:
		static vector<shared_ptr<Button>> Buttons;

		Button(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,Vec2 size) : 
			GameObject(ptr),
			m_TexKey(texKey),m_Pos(pos),m_Size(size),
			m_IsSelect(false)
		{}
		virtual ~Button(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void AddSelectEffect(SelectEffect mode) {
			m_Effect.push_back(mode);
		}
		void NotSelect() {
			m_IsSelect = false;
		}
		void Select() {
			for (auto& button : Button::Buttons) {
				button->NotSelect();
			}
			m_IsSelect = true;
		}


		static void SetActive(bool flag) {
			for (auto& button : Button::Buttons) {
				button->SetDrawActive(flag);
			}
		}

		static void SelectButton(int select) {
			if (select < Button::Buttons.size()) {
				Button::Buttons[select]->Select();
			}
		}
	};
}
//end basecross
