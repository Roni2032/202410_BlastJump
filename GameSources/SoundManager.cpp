/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	SoundManager& SoundManager::Instance() {
		static SoundManager instance;

		return instance;
	}
	void SoundManager::RegisterSounds() {
		m_Audio = App::GetApp()->GetXAudio2Manager();

	}

	void SoundManager::PlaySE(const wstring& key, const float volume) {
		if (m_Audio == nullptr) {
			m_Audio = App::GetApp()->GetXAudio2Manager();
		}
		if (find(m_SoundKeys.begin(), m_SoundKeys.end(), key) != m_SoundKeys.end()) {
			m_Audio->Start(key, 0, volume);
		}

		
	}
	void SoundManager::PlayBGM(const wstring& key, const float volume) {
		if (m_Audio == nullptr) {
			m_Audio = App::GetApp()->GetXAudio2Manager();
		}
		if (find(m_SoundKeys.begin(), m_SoundKeys.end(), key) != m_SoundKeys.end()) {
			m_Bgm = m_Audio->Start(key, XAUDIO2_LOOP_INFINITE, volume);
		}
	}
	void SoundManager::StopBGM() {
		if (m_Audio == nullptr) {
			m_Audio = App::GetApp()->GetXAudio2Manager();
		}

		m_Audio->Stop(m_Bgm);
	}
}
//end basecross
