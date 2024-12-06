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
		Flash
	};
	class Button : public GameObject {
		shared_ptr<BCSprite> m_Sprite;
		wstring m_TexKey;
		Vec3 m_Pos;
		Vec2 m_Size;
		vector<SelectEffect> m_Effect;
		int m_Num;

		bool m_IsSelect;
		bool m_IsNumber;
	public:
		static vector<shared_ptr<Button>> Buttons;

		Button(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,Vec2 size,const bool& isNumber = false,const int& num = 0) : 
			GameObject(ptr),
			m_TexKey(texKey),m_Pos(pos),m_Size(size),
			m_IsSelect(false),
			m_IsNumber(isNumber),m_Num(num)
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
