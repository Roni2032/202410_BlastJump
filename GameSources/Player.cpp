/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	void Player::OnCreate()
	{
		//初期位置などの設定
		m_Transform = GetComponent<Transform>();
		m_Transform->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		m_Transform->SetRotation(0.0f, 0.0f, 0.0f);
		m_Transform->SetPosition(Vec3(0, 0.0f, 0));
		//描画コンポーネントの設定
		m_Draw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		m_Draw->SetMeshResource(L"DEFAULT_CAPSULE");
		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 510.0f, 120.0f));
		ptrString->SetBackColor(m_ColBlack);
		ptrString->GetFontSize();

		m_Grav = AddComponent<BCGravity>();

		//各パフォーマンスを得る
		m_Collision = AddComponent<CollisionCapsule>();
		m_Collision->SetDrawActive(true);
	}

	void Player::OnUpdate()
	{
		DrawString();
		m_Pos = m_Transform->GetPosition();

		m_KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		m_Controler = App::GetApp()->GetInputDevice().GetControlerVec();

		m_State->HandleInput(GetThis<Player>());
		m_State->PlayerUpdate(GetThis<Player>());

		//Raycast3D(m_Pos, Vec3(0.0f, -1.0f, 0.0f), 1.0f, Vec3(0.0f, -0.87f, 0.0f));

		m_Transform->SetPosition(m_Pos);
		m_Draw->SetDiffuse(m_State->GetDiffColor());
	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other)
	{
		if (Other->FindTag(L"Stage"))
		{
			SetIsJumping(false);
		}

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
		stateName = m_State->GetStateName() + L"\n";

		auto gravity = m_Grav->GetVelocity();
		wstring gravityStr(L"Gravity:\t");
		gravityStr += L"GX=" + Util::FloatToWStr(gravity.x, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L",\t";
		gravityStr += L"GY=" + Util::FloatToWStr(gravity.y, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L",\t";
		gravityStr += L"GZ=" + Util::FloatToWStr(gravity.z, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";

		auto collision = m_Collision->FindExcludeCollisionTag(L"Stage");
		wstring collisionStr(L"Collision:\t");
		collisionStr += L"CO=" + Util::FloatToWStr(collision, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";

		float test = m_ThrowTime;
		wstring testStr(L"Test:\t");
		testStr += L"T=" + Util::FloatToWStr(test, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";

		wstring str = positionStr + stateName + gravityStr + collisionStr + testStr;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
		ptrString->SetDrawActive(true);
	}

	void PlayerStateIdle::HandleInput(shared_ptr<Player> player)
	{

		float m_WalkSpeed = player->GetWalkSpeed();

		if (player->InputKey(player->keyPressed, VK_RIGHT) || player->InputKey(player->keyPush, VK_RIGHT))
		{
			player->SetState(make_shared<PlayerStateWalk>(m_WalkSpeed));
		}
		if (player->InputKey(player->keyPressed, VK_LEFT) || player->InputKey(player->keyPush, VK_LEFT))
		{
			player->SetState(make_shared<PlayerStateWalk>(-m_WalkSpeed));
		}

		if (player->InputButton(0, player->b_Pressed, XINPUT_GAMEPAD_DPAD_RIGHT) || player->InputButton(0, player->b_Push, XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			player->SetState(make_shared<PlayerStateWalk>(m_WalkSpeed));
		}
		if (player->InputButton(0, player->b_Pressed, XINPUT_GAMEPAD_DPAD_LEFT) || player->InputButton(0, player->b_Push, XINPUT_GAMEPAD_DPAD_LEFT))
		{
			player->SetState(make_shared<PlayerStateWalk>(-m_WalkSpeed));
		}

		if (player->InputKey(player->keyPressed, 0x58))
		{
			player->SetState(make_shared<PlayerStateThrow>());
		}

		if (player->InputButton(0, player->b_Pressed, XINPUT_GAMEPAD_X))
		{
			player->SetState(make_shared<PlayerStateThrow>());
		}

		if (player->InputKey(player->keyPressed, 0x5A) && (player->GetIsJumping() == false))
		{
			player->PlayerJump(player->GetJumpPower());
			player->SetIsJumping(true);			
		}

		if (player->InputButton(0, player->b_Pressed, XINPUT_GAMEPAD_A) && (player->GetIsJumping() == false))
		{
			player->PlayerJump(player->GetJumpPower());
			player->SetIsJumping(true);		
		}
	}

	void PlayerStateWalk::HandleInput(shared_ptr<Player> player)
	{
		if (player->InputKey(player->keyPressed, 0x58))
		{
			player->SetState(make_shared<PlayerStateThrow>());
		}

		if (player->InputButton(0, player->b_Pressed, XINPUT_GAMEPAD_X))
		{
			player->SetState(make_shared<PlayerStateThrow>());
		}

		if (player->InputKey(player->keyUp, VK_RIGHT))
		{
			player->SetState(make_shared<PlayerStateIdle>());
		}
		if (player->InputKey(player->keyUp, VK_LEFT))
		{
			player->SetState(make_shared<PlayerStateIdle>());
		}

		if (player->InputButton(0, player->b_Up, XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			player->SetState(make_shared<PlayerStateIdle>());
		}
		if (player->InputButton(0, player->b_Up, XINPUT_GAMEPAD_DPAD_LEFT))
		{
			player->SetState(make_shared<PlayerStateIdle>());
		}

		if (player->InputKey(player->keyPressed, 0x5A) && (player->GetIsJumping() == false))
		{
			player->PlayerJump(player->GetJumpPower());
			player->SetIsJumping(true);			
		}

		if (player->InputButton(0, player->b_Pressed, XINPUT_GAMEPAD_A) && (player->GetIsJumping() == false))
		{
			player->PlayerJump(player->GetJumpPower());
			player->SetIsJumping(true);			
		}
	}

	void PlayerStateThrow::PlayerUpdate(shared_ptr<Player> player) 
	{
		Vec3 m_Pos;

		float m_WalkSpeed = player->GetWalkSpeed();

		bool m_IsBombCreate = player->GetIsBombCreate();
		float m_ThrowTime = player->GetThrowTime();
		Vec3 m_BombVec = player->GetBombVec();
		float m_BombShotSpeed = 8.0f;

		if (player->InputKey(player->keyPush, VK_RIGHT)) m_BombVec.x = m_BombShotSpeed;
		if (player->InputKey(player->keyPush, VK_LEFT)) m_BombVec.x = -m_BombShotSpeed;
		if (player->InputKey(player->keyPush, VK_UP)) m_BombVec.y = m_BombShotSpeed;
		if (player->InputKey(player->keyPush, VK_DOWN)) m_BombVec.y = -m_BombShotSpeed;

		if (player->InputButton(0, player->b_Push,XINPUT_GAMEPAD_DPAD_RIGHT)) m_BombVec.x = m_BombShotSpeed;
		if (player->InputButton(0, player->b_Push,XINPUT_GAMEPAD_DPAD_LEFT)) m_BombVec.x = -m_BombShotSpeed;
		if (player->InputButton(0, player->b_Push,XINPUT_GAMEPAD_DPAD_UP)) m_BombVec.y = m_BombShotSpeed;
		if (player->InputButton(0, player->b_Push,XINPUT_GAMEPAD_DPAD_DOWN)) m_BombVec.y = -m_BombShotSpeed;

		if (m_IsBombCreate == false)
		{
			m_Pos = player->GetPlayerPos();

			m_Stage = player->GetStage();
			m_Stage->AddGameObject<Bomb>(m_Pos, m_BombVec, 3.0f, 3.0f, 3.0f);

			player->SetIsBombCreate(true);
		}		

		if (m_ThrowTime <= 0.0f)
		{
			player->SetState(make_shared<PlayerStateIdle>());
		}
		else
		{
			m_ThrowTime -= 0.1f;
			player->SetThrowTime(m_ThrowTime);
		}
	}

}
//end basecross

