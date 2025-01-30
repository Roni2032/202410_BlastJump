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
		
		map<wstring, shared_ptr<SoundItem>> m_PlayingSE;

		float m_SoundVolume;
		SoundManager() : m_SoundVolume(1.0f) {}
	public:
		
		virtual ~SoundManager(){}

		void Update();
		void RegisterSounds();
		void RegisterSound(const wstring& key, const wstring& fileName);
		void PlayLoopSE(const wstring& key,const float volume = 1.0f);
		void StopLoopSE(const wstring& key);

		static SoundManager& Instance();
		shared_ptr<SoundItem> PlaySE(const wstring& key,const float volume = 1.0f);
		shared_ptr<SoundItem> PlayBGM(const wstring& key, const float volume = 1.0f);
		void StopAll();
		void StopBGM();
	};

}
//end basecross
