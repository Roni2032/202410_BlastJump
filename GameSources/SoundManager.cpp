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
		RegisterSound(L"TITLE_BGM", L"TitleBGM.wav");
		RegisterSound(L"BOMB_GET_SD", L"BombGet.wav");
	}
	void SoundManager::RegisterSound(const wstring& key, const wstring& fileName) {
		wstring path = App::GetApp()->GetDataDirWString() + L"Sounds/";

		auto audioRes = App::GetApp()->RegisterWav(key, path + fileName);
		m_SoundKeys.push_back(key);
	}
	void SoundManager::PlayLoopSE(const wstring& key, const float volume) {
		if (find(m_SoundKeys.begin(), m_SoundKeys.end(), key) != m_SoundKeys.end()) {
			auto se = m_Audio->Start(key, XAUDIO2_LOOP_INFINITE,volume);
			m_PlayingSE.insert(pair<wstring, shared_ptr<SoundItem>>(key, se));
		}
	}
	void SoundManager::StopLoopSE(const wstring& key) {
		if (find(m_SoundKeys.begin(), m_SoundKeys.end(), key) != m_SoundKeys.end()) {
			if (m_PlayingSE.find(key) != m_PlayingSE.end()) {
				m_Audio->Stop(m_PlayingSE[key]);
				m_PlayingSE.erase(key);
			}
		}
	}
	shared_ptr<SoundItem> SoundManager::PlaySE(const wstring& key, const float volume) {
		if (m_Audio == nullptr) {
			m_Audio = App::GetApp()->GetXAudio2Manager();
		}
		if (find(m_SoundKeys.begin(), m_SoundKeys.end(), key) != m_SoundKeys.end()) {
			auto se = m_Audio->Start(key, 0, volume);
			m_PlayingSE.insert(pair<wstring, shared_ptr<SoundItem>>(key, se));
			return se;
		}
		else {
			int result = MessageBox(NULL, L"Key Not Found. key : ", L"ERROR", MB_OK);
		}
	}
	shared_ptr<SoundItem> SoundManager::PlayBGM(const wstring& key, const float volume) {
		if (m_Audio == nullptr) {
			m_Audio = App::GetApp()->GetXAudio2Manager();
		}
		if (find(m_SoundKeys.begin(), m_SoundKeys.end(), key) != m_SoundKeys.end()) {
			if (m_Bgm != nullptr) {
				StopBGM();
			}
			m_Bgm = m_Audio->Start(key, XAUDIO2_LOOP_INFINITE, volume);
		}
		else {
			int result = MessageBox(NULL, L"Key Not Found. key : ", L"ERROR", MB_OK);
		}
		return m_Bgm;
	}
	void SoundManager::StopBGM() {
		if (m_Audio == nullptr) {
			m_Audio = App::GetApp()->GetXAudio2Manager();
		}
		if (m_Bgm != nullptr) {
			m_Audio->Stop(m_Bgm);
			m_Bgm = nullptr;
		}
	}
	void SoundManager::StopAll() {
		StopBGM();
		for (auto se : m_PlayingSE) {
			m_Audio->Stop(se.second);
		}
		m_PlayingSE.clear();
	}

	void SoundManager::Update() {
		
	}
}
//end basecross
