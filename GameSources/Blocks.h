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
		vector<vector<int>> m_Maps;

		int m_SizeY;
		Vec2 m_StartPos;
	public:
		InstanceBlock(const shared_ptr<Stage>& stage,const wstring& texKey,int sizeY) :
			GameObject(stage),m_TexKey(texKey),m_SizeY(sizeY)
		{
		}

		virtual void OnCreate();

		void SetStartPos(Vec2 pos) {
			m_StartPos = pos;
		}
		void AddBlock(int y,int cell);
		void DrawMap();
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

		virtual void Start(){}
		virtual void Update(){}
	};

	class FloorBlock : public Block {
		int m_Durability;
	public:
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos) :
			FloorBlock(ptr, texKey, pos, Vec3(1, 1, 1))
		{}
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec3 scale) :
			FloorBlock(ptr, texKey, pos, scale, Vec3(0, 0, 0))
		{}
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec3 scale, Vec3 rot) :
			Block(ptr, texKey, pos, scale, rot),m_Durability(100)
		{}
		virtual ~FloorBlock() {}

		virtual void Start()override;
		virtual void Update() override;
		void HitExplode(int damage);

		void CheckDurability();
	};
}
//end basecross
