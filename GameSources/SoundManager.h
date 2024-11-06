/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class SoundManager{
		vector<wstring> m_SoundKeys;
		shared_ptr<XAudio2Manager> m_Audio;
		shared_ptr<SoundItem> m_Bgm;
	public:
		SoundManager(){}
		virtual ~SoundManager(){}

		void RegisterSounds();

		static SoundManager& Instance();
		void PlaySE(const wstring& key,const float volume = 1.0f);
		void PlayBGM(const wstring& key, const float volume = 1.0f);
		void StopBGM();
	};

}
//end basecross
