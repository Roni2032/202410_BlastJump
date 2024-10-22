/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	/*Player::Player(const shared_ptr<Stage>& ptr, std::unique_ptr<PlayerState> initialState) :
		GameObject(ptr),
		state(std::make_unique<PlayerStateIdle>())
	{}*/

	void Player::OnCreate()
	{
		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0, 0.0f, 0));
		//描画コンポーネントの設定
		m_Draw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		m_Draw->SetMeshResource(L"DEFAULT_SPHERE");
		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 510.0f, 36.0f));
		ptrString->SetBackColor(m_ColBlack);
		ptrString->GetFontSize();
		//auto gravPtr = AddComponent<Gravity>();
		//gravPtr->SetGravityVerocity(Vec3(0.0f, -9.8f, 0.0f));
	}

	void Player::OnUpdate()
	{
		DrawString();

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		m_Transform = GetComponent<Transform>();

		if (KeyState.m_bPushKeyTbl[VK_RIGHT])
		{
			SetState(make_shared<PlayerStateWalk>(0.1f));
		}
		if (KeyState.m_bPushKeyTbl[VK_LEFT])
		{
			SetState(make_shared<PlayerStateWalk>(-0.1f));
		}
		if (KeyState.m_bPushKeyTbl[0x58])
		{
			SetState(make_shared<PlayerStateThrow>());
		}

		if (KeyState.m_bUpKeyTbl[VK_RIGHT] || KeyState.m_bUpKeyTbl[VK_LEFT])
		{
			SetState(make_shared<PlayerStateIdle>());
		}

		m_State->PlayerUpdate(GetThis<Player>());

		m_Transform->SetPosition(m_Pos);
		m_Draw->SetDiffuse(m_State->GetDiffColor());
	}

	void Player::DrawString()
	{
		const uint8_t numberOfDecimalPlaces = 2;

		auto pos = GetComponent<Transform>()->GetPosition();
		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";

		wstring stateName;
		stateName += m_State->GetStateName();

		wstring str = positionStr + stateName;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
		ptrString->SetDrawActive(true);
	}

	void PlayerStateThrow::PlayerUpdate(shared_ptr<Player> player) 
	{
		
		if (m_IsCreate == false)
		{
			m_Stage = player->GetStage();
			m_Stage->AddGameObject<Bomb>();

			m_IsCreate = true;
		}		
	}

}
//end basecross

