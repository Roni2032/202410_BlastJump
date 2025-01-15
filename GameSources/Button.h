/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	enum SelectEffect {
		Expand,
		ChangeSprite,
		Animation,
		Flash
	};
	class Button : public GameObject {

		function<void(shared_ptr<Stage>& stage)> m_Func;
		shared_ptr<BCSprite> m_Sprite;
		wstring m_TexKey;
		wstring m_SelectTexkey;
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
		void SetSelectTex(const wstring key) {
			m_SelectTexkey = key;
		}
		void Function(){
			m_Func(GetStage());
		}
		void SetFunction(function<void(shared_ptr<Stage>& stage)> func) {
			m_Func = func;
		}
		shared_ptr<PCTSpriteDraw> GetDrawComponent() {
			return m_Sprite->GetComponent<PCTSpriteDraw>();
		}
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

		static void Function(int select) {
			Button::Buttons[select]->Function();
		}
		static void SetActive(bool flag) {
			for (auto& button : Button::Buttons) {
				button->GetDrawComponent()->SetDrawActive(flag);
			}
		}
		static void CheckOverIndex(int& select) {
			if (select < 0) {
				select = 0;
			}
			if (select >= Button::Buttons.size()) {
				select = Button::Buttons.size() - 1;
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
