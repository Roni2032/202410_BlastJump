/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class BCCollisionObb : public Component {
		wstring m_WallTag;
		vector<wstring> m_SlipTags;

		float m_CollisionDistance;
		shared_ptr<GameObject> m_GameObject;
		shared_ptr<Transform> m_Trans;
		shared_ptr<Stage> m_Stage;

		Vec3 m_Size;
		Vec3 m_CollisionGap;

		vector<shared_ptr<GameObject>> m_ExcuteObject;
	public:
		BCCollisionObb(const shared_ptr<GameObject>& ptr,float distance,const wstring& wallTag = L"") : Component(ptr),
			m_WallTag(wallTag),m_CollisionDistance(distance),m_Size(1,1,1),m_CollisionGap(0,0,0) {}
		virtual ~BCCollisionObb(){}

		virtual void OnCreate();
		virtual void OnUpdate();
		virtual void OnDraw(){}

		Vec3 PushBackPosition(Vec3 pos,Vec3 wallPos,Vec3 wallSize);
		bool IsHit(Vec3 center, Vec3 wallCenter, Vec3 wallSize);

		void SetSize(Vec3 size) {
			m_Size = size;
		}
		void SetGap(Vec3 gap) {
			m_CollisionGap = gap;
		}
		void AddSlipTag(const wstring& tag) {
			m_SlipTags.push_back(tag);
		}
	};
}
//end basecross
