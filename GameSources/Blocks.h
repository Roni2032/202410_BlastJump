/*!
@file FloorBlock.h
@brief ’n–Ê‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross{
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
			GameObject(ptr),
			m_Pos(pos),m_Scale(scale),m_Rot(rot)
		{}
		virtual ~Block(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override; 

		virtual void Start(){}
		virtual void Update(){}
	};

	class FloorBlock : public Block {
	public:
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos) :
			FloorBlock(ptr, texKey, pos, Vec3(1, 1, 1))
		{}
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec3 scale) :
			FloorBlock(ptr, texKey, pos, scale, Vec3(0, 0, 0))
		{}
		FloorBlock(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec3 scale, Vec3 rot) :
			Block(ptr, texKey, pos, scale, rot)
		{}
		virtual ~FloorBlock() {}

		virtual void Start()override;
	};
}
//end basecross
