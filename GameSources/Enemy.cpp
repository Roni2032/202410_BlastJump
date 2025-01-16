/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr,
		const Vec3& Position,
		const Vec3& Scale
	) :
		GameObject(StagePtr),
		m_pos(Position),
		m_scale(Scale),
		m_MeshName(L"DEFAULT_CUBE"),
		m_hp(0),
		m_speed(1.0f),
		m_velo1(1.0f, 0.0f, 0.0f),
		m_velo2(-1.0f, 0.0f, 0.0f),
		m_time(0),
		m_BeforeVelo(0.0f)
	{}

	void Enemy::OnCreate() {
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(m_scale);
		m_ptrTrans->SetPosition(m_pos);
		m_forward = m_ptrTrans->GetForward();
		m_NowPos = m_ptrTrans->GetPosition();
		m_Blo = GetTypeStage<GameStage>()->GetBlockId(m_ptrTrans->GetPosition() + Vec3(0.0f, -1.0f, 0.0f));
		m_Blo1 = GetTypeStage<GameStage>()->GetBlockId(m_ptrTrans->GetPosition() + Vec3(1.0f, -1.0f, 0.0f));
		m_Blo2 = GetTypeStage<GameStage>()->GetBlockId(m_ptrTrans->GetPosition() + Vec3(-1.0f, -1.0f, 0.0f));
		//m_BeforeVelo = 0.0f;


		auto ptrString = AddComponent<StringSprite>();

		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 510.0f, 120.f));


		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(m_MeshName);

		//m_ptrShadow->SetMeshResource(m_MeshName);

		//m_velo1.normalize();
		//m_velo2.normalize();
		// 
		//当たり判定(仮)
		auto ptrColl = AddComponent<BCCollisionObb>(3.0f, L"Stage");
		ptrColl->SetSize(Vec3(1.0f));

		//ptrColl->SetGap();

		//重力適用
		auto Gra = AddComponent<BCGravity>(-9.0f);


		m_StateEnemy.reset(new StateMachine<Enemy>(GetThis<Enemy>()));
		m_StateEnemy->ChangeState(SearchFarState::Instance());
	}

	//vector<Vec2> Enemy::InternalMap() {
	//	auto& app = App::GetApp();
	//	wstring path = app->GetDataDirWString();
	//	wstring mappath = path + L"Maps";
	//	m_Csvmap.SetFileName(mappath + m_MapName);
	//	m_Csvmap.ReadCsv();
	//	auto& mapVec = m_Csvmap.GetCsvVec();
	//		cellY.clear();
	//		Util::WStrToTokenVector(cellY, mapVec[y + 1], L',');
	//		pos = Vec2(static_cast<float>(cellY.size()) / 2.0f, mapVec.size() - 2);
	//		for (int x = 0; x < cellY.size(); x++)
	//		{
	//			int cellX = stoi(cellY[x]);
	//			Gamestage
	//			return cellX[x],cellY[y];	
	// //		}
	//	}
	//}

	void Enemy::OnUpdate() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		m_time += delta;

		if (m_IsMove)
		{
			m_StateEnemy->Update();
		}
		String();

		m_BeforeVelo = m_ptrTrans->GetVelocity().x;
	}

	void Enemy::Move() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		auto thisPos = m_ptrTrans->GetPosition();
		///auto beforem = m_ptrTrans->GetVelocity().x;
		m_velo1.normalize();
		m_velo2.normalize();

		if(m_IsMoveLeft&&m_IsMoveRight) {
			thisPos += m_velo1 * m_speed * delta;
			m_ptrTrans->SetPosition(thisPos);
			//m_IsMoveLeft = false;
		}

		if (!m_IsMoveLeft&&m_IsMoveRight) {
			thisPos += m_velo2 * m_speed * delta;
			m_ptrTrans->SetPosition(thisPos);
			//m_IsMoveRight = false;
		}
	}
	//int velo = m_forwrd.x + 1.0f;	
			//自分の下の進行方向一個先のブロックをとる
			//int block1 = GetTypeStage<GameStage>()->GetBlock(thisPos + Vec3(1.0f, -1.0f, 0.0f));
			//下にも先にもある場合
			//if (block1 == 1 && block == 1) {
			//	thisPos += m_velo1 * m_speed * delta;
			//	m_ptrTrans->SetPosition(thisPos);
			//}
			////下にあり先にない場合
			//else if (block1 == 0 && block == 1) {
			//	m_ptrTrans->SetRotation(0.0f, 180.0f, 0.0f);
			//	thisPos += m_velo2 * m_speed * delta;
			//	m_ptrTrans->SetPosition(thisPos);
			//}
			////どっちもない場合
			//if (block == 0 && block1 == 0) return;
			//if (m_ptrTrans->GetVelocity().x< 0)
			//{
			//	//壁ガ２
			//	int velo = m_forward.x - 1.0f;
			//	int block = GetTypeStage<GameStage>()->GetBlock(thisPos + Vec3(-1.0f, 1.0f, 0.0f));
			//	if (block == 0)
			//	{
			//		m_ptrTrans->SetRotation(0.0f,180.0f,0.0f);
			//		thisPos += m_velo1* m_speed * delta;
			//		m_ptrTrans->SetPosition(thisPos);
			//	}
			//	if (block == 1) {
			//		thisPos += m_velo2 * m_speed * delta;
			//		m_ptrTrans->SetPosition(thisPos);
			//	}
			//}
		//}
	//}

	void Enemy::String() {
		wstring Pos(L"Position : ");
		Pos += L"PosX" + Util::FloatToWStr(m_ptrTrans->GetPosition().x, 3, Util::FloatModify::Fixed) + L"\t";
		Pos += L"PosY" + Util::FloatToWStr(m_ptrTrans->GetPosition().y, 3, Util::FloatModify::Fixed) + L"\t";
		Pos += L"PosZ" + Util::FloatToWStr(m_ptrTrans->GetPosition().z, 3, Util::FloatModify::Fixed) + L"\n";

		wstring blo(L"Block : ");
		blo += L"Blo" + Util::FloatToWStr(m_Blo, 1, Util::FloatModify::Fixed) + L"\t";
		blo += L"Blo1" + Util::FloatToWStr(m_Blo1, 1, Util::FloatModify::Fixed) + L"\t";
		blo += L"Blo2" + Util::FloatToWStr(m_Blo2, 1, Util::FloatModify::Fixed) + L"\n";

		wstring velo(L"Velocity : ");
		velo += L"Velo.x" + Util::FloatToWStr(m_ptrTrans->GetVelocity().x, 1, Util::FloatModify::Fixed) + L"\t";
		velo += L"Velo.y" + Util::FloatToWStr(m_ptrTrans->GetVelocity().y, 1, Util::FloatModify::Fixed) + L"\t";
		velo += L"Velo.z" + Util::FloatToWStr(m_ptrTrans->GetVelocity().z, 1, Util::FloatModify::Fixed) + L"\n";

		wstring str = Pos + blo + velo;
		auto sp = GetComponent<StringSprite>();
		sp->SetText(str);
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Floor")) {
			m_IsMove = true;
		}
		//if (Other->FindTag(L"Stage")) {
		//	Other->OnCollisionExcute(GetThis<GameObject>());

		//	auto coll = GetComponent<BCCollisionObb>();
		//	auto data = coll->GetCollisionData(Other);
		//	if (data.hitDir == HitDir::Up){
		//		m_IsMove = true;
		//	}
		//	if (data.hitDir == HitDir::Left) {

		//	}
		//	if (data.hitDir == HitDir::Right) {

		//	}

		//	
	
		//}
	}
	void Enemy::OnCollisionExit(shared_ptr<GameObject>& Other) {
		Other->OnCollisionExit(GetThis<GameObject>());
		auto coll = GetComponent<BCCollisionObb>();
		auto data = coll->GetCollisionData(Other);
		if (data.hitDir == !HitDir::Up) {
			m_IsMove = false;		}
	}

	void Enemy::OnCollisionExcute(shared_ptr<GameObject>& Other) {
		if (Other->FindTag(L"Stage")) {
			Other->OnCollisionExcute(GetThis<GameObject>());

			auto coll = GetComponent<BCCollisionObb>();
			auto data = coll->GetCollisionData(Other);
			if (data.hitDir == HitDir::Up) {
				m_IsMove = true;
			}
			if (m_IsMove) {
				if (m_BeforeVelo >= 0.0f) {
					if (data.hitDir == HitDir::Left) {
						m_IsMoveRight = false;
						m_IsMoveLeft = true;
					}
					else {
						return;
						m_IsMoveLeft = false;
						m_IsMoveRight = true;
					}
				}		
				//if(m_BeforeVelo<0.0f) {
				//	if (data.hitDir == HitDir::Left) {
				//		m_IsMoveLeft = true;
				//		m_IsMoveRight = false;
				//	}
				//	if (data.hitDir == HitDir::Right) {
				//		m_IsMoveLeft = false;
				//		m_IsMoveRight = true;
				//	}
				//	if(data.hitDir == HitDir::Left) {
				//		m_IsMoveLeft = true;
				//		m_IsMoveRight = false;
				//	}
				//}
			}
		}
	}

	shared_ptr<SearchFarState> SearchFarState::Instance() {
		static shared_ptr<SearchFarState> instance(new SearchFarState);
		return instance;
	}
	void SearchFarState::Enter(const shared_ptr<Enemy>& Obj) {
	}
	void SearchFarState::Execute(const shared_ptr<Enemy>& Obj) {
		Obj->Move();
	}
	void SearchFarState::Exit(const shared_ptr<Enemy>& Obj) {
	}

}

//end basecross

