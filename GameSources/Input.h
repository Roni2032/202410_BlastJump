/*!
@file Input.h
@brief “ü—Í‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class InputKeyboard
	{
	private:

		InputKeyboard() {}

		~InputKeyboard() {}

		KEYBOARD_STATE m_KeyState;

	public:

		enum KeyPushState
		{
			keyPush = 0,
			keyPressed,
			keyUp,
		};

		static InputKeyboard& GetInstance()
		{
			static InputKeyboard instance;
			return instance;
		}

		void UpdateKeyState(const KEYBOARD_STATE& newKeyState)
		{
			m_KeyState = newKeyState;
		}

		bool InputKey(const int keyPushState, const int keyCord)
		{
			switch (keyPushState)
			{
			case 1:

				return m_KeyState.m_bPressedKeyTbl[keyCord];

				break;

			case 2:

				return m_KeyState.m_bUpKeyTbl[keyCord];

				break;

			default:

				return m_KeyState.m_bPushKeyTbl[keyCord];

				break;
			}
		}
	};

	class InputController
	{
	private:

		InputController() {}

		~InputController() {}

		vector<CONTROLER_STATE> m_Controller;
		const float m_Zero = 0.0f;

	public:

		enum ButtonPushState
		{
			buttonPush = 0,
			buttonPressed,
			buttonUp,
		};

		static InputController& GetInstance()
		{
			static InputController instance;
			return instance;
		}

		void UpdateCntlState(const vector<CONTROLER_STATE>& newCntlState)
		{
			m_Controller = newCntlState;
		}

		bool InputButton(const int useController, const int buttonState, const int button)
		{
			if (m_Controller[useController].bConnected == false) { return false; }

			switch (buttonState)
			{
			case 1:

				return m_Controller[useController].wPressedButtons & button;

				break;

			case 2:

				return m_Controller[useController].wReleasedButtons & button;

				break;

			default:

				return m_Controller[useController].wButtons & button;

				break;
			}			
		}

		Vec2 InputStick(const int useController, const int stick)
		{
			if (m_Controller[useController].bConnected == false) { return Vec2(m_Zero); }

			Vec2 cntlLVec = Vec2(m_Controller[useController].fThumbLX, m_Controller[useController].fThumbLY);
			Vec2 cntlRVec = Vec2(m_Controller[useController].fThumbRX, m_Controller[useController].fThumbRY);

			switch (stick)
			{
			case 1:

				if (cntlLVec.length() == 0) { return Vec2(m_Zero); }

				return cntlLVec;

				break;

			case 2:

				if (cntlRVec.length() == 0) { return Vec2(m_Zero); }

				return cntlRVec;

				break;

			default:

				if (cntlLVec.length() == 0) { return Vec2(m_Zero); }

				return cntlLVec;

				break;
			}
		}
	};

}