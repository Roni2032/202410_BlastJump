/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	
	void BCCollisionObb::OnCreate() {
		m_Trans = GetGameObject()->GetComponent<Transform>();
		m_Stage = GetGameObject()->GetStage();
		m_GameObject = GetGameObject();
	}

	void BCCollisionObb::OnUpdate() {

		m_PushBackObject.clear();
		m_EnterObject.clear();
		vector<shared_ptr<GameObject>> objs;
		m_Stage->GetUsedTagObjectVec(m_WallTag, objs);
		for (auto slipTag : m_SlipTags) {
			m_Stage->GetUsedTagObjectVec(slipTag, objs);
		}

		for (auto obj : objs) {
			auto objTrans = obj->GetComponent<Transform>();

			Vec3 objPos = objTrans->GetWorldPosition();
			Vec3 objSize = objTrans->GetScale();

			Vec3 pos = m_Trans->GetWorldPosition() + m_CollisionGap;

			Vec3 diff = objPos - pos;

			if (diff.length() > m_CollisionDistance) {
				auto it = find(m_ExcuteObject.begin(), m_ExcuteObject.end(), obj);
				if (it != m_ExcuteObject.end()) {
					m_ExcuteObject.erase(it);
					obj->OnCollisionExit(m_GameObject);
					m_GameObject->OnCollisionExit(obj);

				}
				continue;
			}
			
			Vec3 center = Vec3(pos.x + m_Size.x / 2.0f, pos.y - m_Size.y / 2.0f, pos.z + m_Size.z / 2.0f);
			Vec3 objCenter = Vec3(objPos.x + objSize.x / 2.0f, objPos.y - objSize.y / 2.0f, objPos.z + objSize.z / 2.0f);

			if(IsHit(center,objCenter,objSize)){

				if (find(m_ExcuteObject.begin(), m_ExcuteObject.end(), obj) == m_ExcuteObject.end()) {
					m_ExcuteObject.push_back(obj);
					m_EnterObject.push_back(obj);
					//obj->OnCollisionEnter(m_GameObject);
					//m_GameObject->OnCollisionEnter(obj);
				}
			}
			else {
				auto it = find(m_ExcuteObject.begin(), m_ExcuteObject.end(), obj);
				if (it != m_ExcuteObject.end()) {
					m_ExcuteObject.erase(it);
					obj->OnCollisionExit(m_GameObject);
					m_GameObject->OnCollisionExit(obj);
				}
			}
		}
		
		auto& object = m_GameObject;
		sort(m_ExcuteObject.begin(), m_ExcuteObject.end(), [object](shared_ptr<GameObject>& a, shared_ptr<GameObject>& b) {
			auto transA = a->GetComponent<Transform>();
			auto transB = b->GetComponent<Transform>();
			auto trans = object->GetComponent<Transform>();

			Vec3 scaleA = transA->GetScale();
			scaleA.y *= -1;
			Vec3 scaleB = transB->GetScale();
			scaleB.y *= -1;
			Vec3 scale = trans->GetScale();
			scale.y *= -1;

			Vec3 posA = transA->GetPosition();
			Vec3 posB = transB->GetPosition();
			Vec3 pos = trans->GetPosition();

			float diffA = ((posA + scaleA / 2.0f) - (pos + scale / 2.0f)).length();
			float diffB = ((posB + scaleB / 2.0f) - (pos + scale / 2.0f)).length();


			return diffA < diffB;
			});

		
		for (auto obj : m_ExcuteObject) {

			Vec3 pos = m_Trans->GetWorldPosition() + m_CollisionGap;

			bool isSlip = false;
			for (auto slipTag : m_SlipTags) {
				if (obj->FindTag(slipTag)) {
					isSlip = true;
				}
			}
			if (!isSlip) {
				pos = PushBackPosition(pos, obj);
				m_Trans->SetWorldPosition(pos);
			}

			obj->OnCollisionExcute(m_GameObject);
			m_GameObject->OnCollisionExcute(obj);
		}
		for (auto obj : m_EnterObject) {
			obj->OnCollisionEnter(m_GameObject);
			m_GameObject->OnCollisionEnter(obj);
		}
	}

	bool BCCollisionObb::IsHit(Vec3 center, Vec3 wallCenter, Vec3 wallSize) {
		if (abs(wallCenter.x - center.x) <= m_Size.x / 2.0f + wallSize.x / 2.0f &&
			abs(wallCenter.y - center.y) <= m_Size.y / 2.0f + wallSize.y / 2.0f) {
			return true;
		}

		return false;
	}
	Vec3 BCCollisionObb::PushBackPosition(Vec3 pos, shared_ptr<GameObject>& wall) {
		HitDir dir = HitDir::None;
		auto objTrans = wall->GetComponent<Transform>();

		Vec3 wallPos = objTrans->GetWorldPosition();
		Vec3 wallSize = objTrans->GetScale();

		Vec3 diff = Vec3();
		Vec3 diff2 = Vec3();
		diff.x = abs((pos.x + m_Size.x) - wallPos.x);
		diff2.x = abs((wallPos.x + wallSize.x) - pos.x);

		diff.y = abs(pos.y - (wallPos.y - wallSize.y));
		diff2.y = abs(wallPos.y - (pos.y - m_Size.y));

		if (diff.x > diff2.x) {
			diff.x = diff2.x;
		}
		if (diff.y > diff2.y) {
			diff.y = diff2.y;
		}
		auto Grv = m_GameObject->GetComponent<BCGravity>();
		Vec3 velocity = Vec3(0, 0, 0);
		if (Grv != nullptr) {
			velocity = Grv->GetVelocity();
		}
		
		//めり込みの比較
		if (diff.x < diff.y) {
			//左押し出し
			if (pos.x < wallPos.x) {
				pos.x = wallPos.x - m_Size.x;
				dir = HitDir::Left;
			}
			//右押し出し
			else {
				pos.x = wallPos.x + wallSize.x;
				dir = HitDir::Right;
			}
			if (Grv != nullptr) {
				Grv->SetVelocity(Vec3(0, velocity.y, velocity.z));
			}
		}
		else {
			//下押し出し
			if (pos.y < wallPos.y) {
				pos.y = wallPos.y - wallSize.y;
				dir = HitDir::Down;
				if (Grv != nullptr) {
					Grv->SetVelocity(Vec3(velocity.x, 0, velocity.z));
				}
			}
			//上押し出し
			else {
				pos.y = wallPos.y + m_Size.y;
				dir = HitDir::Up;
				if (Grv != nullptr) {
					Grv->SetVelocity(Vec3(0, 0, velocity.z));
				}
			}
		}
		m_PushBackObject.push_back(CollisionData(wall, dir));
		return pos - m_CollisionGap;
	}

	CollisionData BCCollisionObb::GetCollisionData(const shared_ptr<GameObject>& obj) {
		for (auto& data : m_PushBackObject) {
			if (obj == data.m_HitObject) {
				return data;
			}
		}
		return CollisionData();
	}
}
//end basecross
