/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//
	//	0>speed:4-start:2^3^2-end:-2^3^2
	//	数字>引数
	//	
	//	キー:数値-キー:数値
	// 
	//	数値
	//	float:1
	//	Vec2 Vec3:1^2^1
	//
	struct BlockData {
		int m_Id;
		bool m_IsLoaded;
		shared_ptr<GameObject> m_Obj;
		map<wstring, wstring> m_Data;

		inline BlockData& operator =(const BlockData& other) {
			
			m_Id = other.m_Id;
			m_IsLoaded = other.m_IsLoaded;
			m_Obj = other.m_Obj;
			m_Data.clear();
			for (auto& newData : other.m_Data) {
				m_Data.insert(pair<wstring, wstring>(newData.first, newData.second));
			}

			return *this;
		}
		BlockData(int id,const wstring& data = L""):
			m_Id(id),
			m_IsLoaded(false),
			m_Obj(nullptr)
		{
			if (data != L"") {
				vector<wstring> strData;
				Util::WStrToTokenVector(strData, data, L'/');
				for (auto d : strData) {
					vector<wstring> data;
					Util::WStrToTokenVector(data, d, L':');
					m_Data.insert(pair<wstring, wstring>(data[0], data[1]));
				}
			}
		}
		bool GetIsLoaded() {
			return m_IsLoaded;
		}
		void SetIsLoaded(bool flag) {
			m_IsLoaded = flag;
		}
		int GetID() {
			return m_Id;
		}
		void RemoveBlock() {
			m_Id = 0;
			ClearGameObject();
		}
		shared_ptr<GameObject> GetBlock() {
			return m_Obj;
		}
		void ClearGameObject() {
			m_Obj = nullptr;
		}
		void SetGameObject(const shared_ptr<GameObject>& obj) {
			if (m_Obj != nullptr) ClearGameObject();

			m_Obj = obj;
		}
		wstring GetData(const wstring& dataName) {
			if (m_Data.find(dataName) != m_Data.end()) {
				return m_Data[dataName];
			}
			else {
				return L"";
			}
		}
		static bool IsFloat(const wstring& data) {
			for (auto& str : data) {
				if (!isdigit(str) && str != '.') {
					return false;
				}
			}
			return true;
		}
		static float WstrToFloat(const wstring& data,const float initData = 0.0f) {
			if (data == L"") return initData;
			if (!IsFloat(data)) {
				return initData;
			}
			return stof(data);
		}
		static int WstrToInt(const wstring& data,const int initData = 0) {
			if (data == L"") return initData;
			if (!all_of(data.cbegin(), data.cend(), isdigit)) {
				return initData;
			}
			return stoi(data);
		}
		static Vec2 WstrToVec2(const wstring& data,const Vec2 initData = Vec2()) {
			vector<wstring> numStr;
			Util::WStrToTokenVector(numStr, data, L'^');
			Vec2 vec = initData;
			for (int i = 0; i < numStr.size(); i++) {
				if (numStr[i] == L"") continue;
				if (all_of(numStr[i].cbegin(), numStr[i].cend(), isdigit)) {
					vec[i] = stoi(numStr[i]);
				}
			}
			return vec;
		}
		static Vec3 WstrToVec3(const wstring& data,const Vec3 initData = Vec3()) {
			vector<wstring> numStr;
			Util::WStrToTokenVector(numStr, data, L'^');
			Vec3 vec = initData;
			for (int i = 0; i < numStr.size(); i++) {
				if (numStr[i] == L"") continue;
				if (all_of(numStr[i].cbegin(), numStr[i].cend(), isdigit)) {
					vec[i] = stoi(numStr[i]);
				}
			}

			return vec;
		}
	};
}
//end basecross
