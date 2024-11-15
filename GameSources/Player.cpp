/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Player::OnCreate()
	{
		//初期位置などの設定
		m_Transform = GetComponent<Transform>();
		m_Transform->SetScale(0.5f, 0.5f, 0.5f);	//直径25センチの球体
		m_Transform->SetRotation(0.0f, 0.0f, 0.0f);
		m_Transform->SetPosition(Vec3(0, 1.0f, 0));
		//描画コンポーネントの設定
		m_Draw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		m_Draw->SetMultiMeshResource(L"PLAYER_MD");
		m_Draw->SetTextureResource(L"PLAYER_MD_TEX");
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f),//スケール
			Vec3(0.0f, 0.0f, 0.0f),//回転の中心
			Vec3(0.0f, 0.0f, 0.0f),//回転のベクトル
			Vec3(0.0f, -2.0f, 0.0f) //移動
		);		
		m_Draw->SetMeshToTransformMatrix(spanMat);

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 510.0f, 200.0f));
		ptrString->SetBackColor(m_ColBlack);
		ptrString->GetFontSize();

		m_Velo = AddComponent<BCGravity>();

		//各パフォーマンスを得る
		m_Collision = AddComponent<CollisionCapsule>();
		m_Collision->SetMakedRadius(0.25f);
		m_Collision->SetDrawActive(true);

		AddTag(L"Player");
	}

	void Player::OnUpdate()
	{
		DrawString();

		m_Pos = m_Transform->GetPosition();

		m_KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		m_Controler = App::GetApp()->GetInputDevice().GetControlerVec();

		m_State->HandleInput(GetThis<Player>());
		m_State->PlayerUpdate(GetThis<Player>());

		m_Transform->SetPosition(m_Pos);

		//m_Draw->SetDiffuse(m_State->GetDiffColor());

		if (GetThrowCoolTime() > 0.0f) { m_ThrowCoolTime -= 0.1f; }

		if (m_KeyState.m_bPressedKeyTbl[VK_SPACE]) { AddHasBombV2(4); }

		if (m_Pos.y < OnGetDrawCamera()->GetEye().y - 5) m_IsDead = true;
		else m_IsDead = false;

		if (m_IsDead)
		{
			auto myCamera = static_pointer_cast<MyCamera>(OnGetDrawCamera());
			GetTypeStage<GameStage>()->NewRespawnPosition(Vec3(0.0f, 3.0f, 0.0f));
			m_Transform->SetPosition(GetTypeStage<GameStage>()->GetRespawnPosition());
			myCamera->SetEye(Vec3(-0.5f, 4.0f, -110.0f));
			myCamera->SetAt(Vec3(-0.5f, 4.0f, 0.0f));
		}
	}

	//void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	//{
	//	if (Other->FindTag(L"Stage")) { Other->OnCollisionEnter(GetThis<GameObject>()); }
	//}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other)
	{
		if (Other->FindTag(L"Stage"))
		{			
			//Other->OnCollisionExcute(GetThis<GameObject>());

			auto block = Other->GetComponent<Transform>();
			auto blockPosition = block->GetPosition();
			auto blockScale = block->GetScale();

			auto player = GetComponent<Transform>();
			auto playerPosition = player->GetPosition();
			auto playerScale = player->GetScale();

			if ((playerPosition.y > blockPosition.y) && ((playerPosition.x + playerScale.x * 0.5f) > blockPosition.x) && 
				((playerPosition.x + playerScale.x * 0.5f) < (blockPosition.x + blockScale.x)))
			{
				SetIsJumping(false);
			}
		}

	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		//if (Other->FindTag(L"Stage")) { Other->OnCollisionExit(GetThis<GameObject>()); }
		if (Other->FindTag(L"Stage")) { SetIsJumping(true); }
	}

	void Player::DrawString()
	{
		const uint8_t numberOfDecimalPlaces = 2;

		auto pos = GetComponent<Transform>()->GetPosition();
		wstring positionStr(L"Position: ");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";

		wstring stateName;
		stateName = m_State->GetStateName() + L"\n";

		auto velocity = m_Velo->GetVelocity();
		wstring velocityStr(L"Velocity: ");
		velocityStr += L"VX=" + Util::FloatToWStr(velocity.x, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		velocityStr += L"VY=" + Util::FloatToWStr(velocity.y, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		velocityStr += L"VZ=" + Util::FloatToWStr(velocity.z, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";

		auto hasBomb = GetHasBomb();
		wstring hasBombStr(L"HasBomb: ");
		hasBombStr += L"HB=" + Util::IntToWStr(hasBomb) + L"\n";

		//auto camera = OnGetDrawCamera();
		auto camera = static_pointer_cast<MyCamera>(OnGetDrawCamera());
		wstring cameraStr(L"Camera: ");
		cameraStr += L"CEX=" + Util::FloatToWStr(camera->GetEye().x, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		cameraStr += L"CEY=" + Util::FloatToWStr(camera->GetEye().y, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		cameraStr += L"CEZ=" + Util::FloatToWStr(camera->GetEye().z, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";
		cameraStr += L"CAX=" + Util::FloatToWStr(camera->GetAt().x, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		cameraStr += L"CAY=" + Util::FloatToWStr(camera->GetAt().y, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		cameraStr += L"CAZ=" + Util::FloatToWStr(camera->GetAt().z, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L", ";
		cameraStr += L"CH=" + Util::FloatToWStr(camera->GetHeight(), numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";

		bool isDead = false;
		if (pos.y < camera->GetEye().y - 5) isDead = true;
		else isDead = false;
		wstring deadStr(L"");
		if (isDead) deadStr = L"DIED\n";
		else deadStr = L"LIVED\n";

		uint32 fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring fpsStr(L"FPS: ");
		fpsStr += L"FPS=" + Util::FloatToWStr(fps, numberOfDecimalPlaces, Util::FloatModify::Fixed) + L"\n";

		wstring str = positionStr + stateName + velocityStr + hasBombStr + cameraStr + deadStr + fpsStr;

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
		float m_ThrowCoolTime = player->GetThrowCoolTime();
		Vec3 m_BombVec = player->GetBombVec();
		float m_BombShotSpeed = 8.0f;
		uint8_t m_HasBomb = player->GetHasBomb();

		if (player->InputKey(player->keyPush, VK_RIGHT)) m_BombVec.x = m_BombShotSpeed;
		if (player->InputKey(player->keyPush, VK_LEFT)) m_BombVec.x = -m_BombShotSpeed;
		if (player->InputKey(player->keyPush, VK_UP)) m_BombVec.y = m_BombShotSpeed;
		if (player->InputKey(player->keyPush, VK_DOWN)) m_BombVec.y = -m_BombShotSpeed;

		if (player->InputButton(0, player->b_Push, XINPUT_GAMEPAD_DPAD_RIGHT)) m_BombVec.x = m_BombShotSpeed;
		if (player->InputButton(0, player->b_Push, XINPUT_GAMEPAD_DPAD_LEFT)) m_BombVec.x = -m_BombShotSpeed;
		if (player->InputButton(0, player->b_Push, XINPUT_GAMEPAD_DPAD_UP)) m_BombVec.y = m_BombShotSpeed;
		if (player->InputButton(0, player->b_Push, XINPUT_GAMEPAD_DPAD_DOWN)) m_BombVec.y = -m_BombShotSpeed;

		if ((m_IsBombCreate == false) && (m_HasBomb > 0) && (m_ThrowCoolTime <= 0.0f))
		{
			m_Pos = player->GetPlayerPos();

			m_Stage = player->GetStage();
			m_Stage->AddGameObject<Bomb>(m_Pos, m_BombVec, 3.0f, 3.0f, 18.0f);

			player->SubtractHasBomb();

			player->SetThrowCoolTime(3.0f);
			player->SetIsBombCreate(true);
		}

		player->SetState(make_shared<PlayerStateIdle>());
	}

}
//end basecross

