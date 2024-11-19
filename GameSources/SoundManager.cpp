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
		RegisterSound(L"BOMB_SD", L"Bomb.wav");
		RegisterSound(L"BGM_SD", L"kariBGM.wav");
		RegisterSound(L"WINNER_SD", L"kati.wav");
		RegisterSound(L"LOSER_SD", L"make.wav");
	}
	void SoundManager::RegisterSound(const wstring& key, const wstring& fileName) {
		wstring path = App::GetApp()->GetDataDirWString() + L"Sounds/";

		auto audioRes = App::GetApp()->RegisterWav(key, path + fileName);
		m_SoundKeys.push_back(key);
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
			if (m_Bgm != nullptr) {
				StopBGM();
			}
			m_Bgm = m_Audio->Start(key, XAUDIO2_LOOP_INFINITE, volume);
		}
	}
	void SoundManager::StopBGM() {
		if (m_Audio == nullptr) {
			m_Audio = App::GetApp()->GetXAudio2Manager();
		}

		m_Audio->Stop(m_Bgm);
		m_Bgm = nullptr;
	}
}
//end basecross
