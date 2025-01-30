/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class Goal : public GameObject {
		Vec3 m_Pos;
	public:
		Goal(const shared_ptr<Stage>& ptr,Vec3 pos) : GameObject(ptr),m_Pos(pos){}
		virtual ~ Goal(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};

	class CheckPoint : public GameObject {
		Vec3 m_Pos;
		bool m_IsActuated;

		shared_ptr<PNTBoneModelDraw> m_Draw;
		shared_ptr<MeshResource> m_Mesh;
	public:
		CheckPoint(const shared_ptr<Stage>& ptr, Vec3 pos) : GameObject(ptr),m_Pos(pos),m_IsActuated(false) {}
		virtual ~CheckPoint() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
	};

	//----------------------------------------------------------
	//																																
	//	ボード																						
	//																																
	//----------------------------------------------------------

	class Board : public GameObject {
		shared_ptr<Transform> m_Trans;
		Vec3 m_StartPos;
		Vec3 m_Size;
	public:
		Board(shared_ptr<Stage>& ptr,Vec3 pos,Vec3 size) : GameObject(ptr),m_StartPos(pos),m_Size(size) {}
		virtual ~Board() {}

		virtual void OnCreate()override;
	};
}
//end basecross
