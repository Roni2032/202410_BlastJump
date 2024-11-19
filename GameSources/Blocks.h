/*!
@file FloorBlock.h
@brief ’n–Ê‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class InstanceBlock : public GameObject {
		wstring m_TexKey;

		shared_ptr<PNTStaticInstanceDraw> m_Draw;
		shared_ptr<Camera> m_Camera;

		vector<vector<int>> m_Maps;
		vector<shared_ptr<GameObject>> m_CollisionObjects;

		float m_DrawMaxHeight;
		float m_CameraAtY;
		int m_SizeY;
		Vec2 m_StartPos;

	public:
		InstanceBlock(const shared_ptr<Stage>& stage,const wstring& texKey,int sizeY) :
			GameObject(stage),m_TexKey(texKey),m_SizeY(sizeY),m_DrawMaxHeight(-1),m_CameraAtY(0)
		{
		}

		virtual void OnCreate();

		void SetStartPos(Vec2 pos) {
			m_StartPos = pos;
		}
		void AddBlock(int y,int cell);
		
		void DrawMap(const Vec2 max = Vec2(0), const Vec2 min = Vec2(0));
	};
	class Block : public GameObject {
		wstring m_TexKey;
		Vec3 m_Pos;
		Vec3 m_Scale;
		Vec3 m_Rot;

		
	public:
		Block(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos):
			Block(ptr,texKey,pos,Vec3(1,1,1))
		{}
		Block(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos,Vec3 scale) :
			Block(ptr,texKey,pos,scale,Vec3(0,0,0))
		{}
		Block(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos,Vec3 scale,Vec3 rot) :
			GameObject(ptr),m_TexKey(texKey),
			m_Pos(pos),m_Scale(scale),m_Rot(rot)
		{}
		virtual ~Block(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override; 
		virtual void OnCollisionExcute(shared_ptr<GameObject>& Other)override;

		virtual void Start(){}
		virtual void Update(){}

		static vector<weak_ptr<Transform>> CollisionObjects;
	};

	class FloorBlock : public Block {
		int m_Durability;
	public:
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos,const int durability = 100) :
			FloorBlock(ptr, texKey, pos, Vec3(1, 1, 1),durability)
		{}
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec3 scale, const int durability = 100) :
			FloorBlock(ptr, texKey, pos, scale, Vec3(0, 0, 0),durability)
		{}
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec3 scale, Vec3 rot, const int durability = 100) :
			Block(ptr, texKey, pos, scale, rot),m_Durability(durability)
		{}
		virtual ~FloorBlock() {}

		virtual void Start()override;
		virtual void Update() override;
		void HitExplode(int damage);

		void CheckDurability();
	};

	class MoveBlock : public FloorBlock {
		Vec3 m_MoveStartPos;
		Vec3 m_MoveEndPos;
		Vec3 m_TargetPos;
		float m_MoveSpeed;

		shared_ptr<Transform> m_Trans;
	public:
		MoveBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, float speed, Vec3 moveRange) :
			MoveBlock(ptr,texKey,pos,speed, pos + moveRange, pos - moveRange){}

		MoveBlock(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,float speed,Vec3 start,Vec3 end) :
			FloorBlock(ptr,texKey,pos),
			m_MoveStartPos(start),m_MoveEndPos(end),
			m_MoveSpeed(speed)
		{}

		virtual void Start()override;
		virtual void Update()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other)override;

	};
}
//end basecross
