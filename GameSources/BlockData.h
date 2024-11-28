/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	struct BlockData {
		int m_Id;
		shared_ptr<GameObject> m_Obj;
		wstring m_AllData;

		BlockData(int id,const wstring& data = L""):
			m_Id(id),
			m_AllData(data){}

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

		/*wstring& GetData(const wstring& dataName) {
			vector<wstring> strData;
			Util::WStrToTokenVector(strData, m_AllData, L'.');
			for (auto d : strData) {
				vector<wstring> data;
				Util::WStrToTokenVector(data, d, L':');
				if (data[0] == dataName) {
					return data[1];
				}
			}
			return ;
		}*/
	};
}
//end basecross
