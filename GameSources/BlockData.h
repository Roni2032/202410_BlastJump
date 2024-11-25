/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	struct BlockData {
		int m_Id;
		wstring m_AllData;

		BlockData(int id,const wstring& data = L""):
			m_Id(id),m_AllData(data){}

		int GetID() {
			return m_Id;
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
