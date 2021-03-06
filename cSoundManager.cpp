#include "DXUT.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager()
{
	Init();
}

cSoundManager::~cSoundManager()
{
	Release();
}

void cSoundManager::Init()
{
	m_Manager.Initialize(DXUTGetHWND(), 1);
}

LONG volume = 0L;
void cSoundManager::Update()
{
	if (INPUT->KeyDown(VK_F9))
	{
		volume = DSBVOLUME_MAX;
	}
	else if (INPUT->KeyDown(VK_F10))
	{
		volume = -1000;
	}
	else if (INPUT->KeyDown(VK_F11))
	{
		volume = DSBVOLUME_MIN;
	}

	if (INPUT->KeyDown(VK_BACK))
	{
		SOUND->StopAll();
	}

	DWORD status;
	for (auto& iter = m_channels.begin(); iter != m_channels.end();)
	{
		(*iter).second->SetVolume(volume);
		(*iter).second->GetStatus(&status);
		if (!(status & DSBSTATUS_PLAYING))
		{
			(*iter).second->Release();
			iter = m_channels.erase(iter);
		}
		else
			iter++;
	}
}

void cSoundManager::Release()
{
	// for (auto iter : m_sounds) SAFE_DELETE(iter.second);
	for (auto iter : m_channels) iter.second->Release();
	m_channels.clear();
}

LPDIRECTSOUNDBUFFER cSoundManager::Play(string key, LONG volume, bool loop)
{
	LPDIRECTSOUNDBUFFER sb;
	m_Manager.GetDirectSound()->DuplicateSoundBuffer(m_sounds[key]->GetBuffer(0), &sb);
	sb->SetVolume(volume);
	sb->Play(0, 0, loop == true ? DSBPLAY_LOOPING : 0);
	m_channels.insert(make_pair(key, sb));
	return sb;
}

void cSoundManager::Stop(string key)
{
	auto find = m_channels.find(key);
	if (find == m_channels.end()) return;
	find->second->Release();
	find = m_channels.erase(find);
}

void cSoundManager::StopAll()
{
	for (auto iter : m_channels) iter.second->Release();
	m_channels.clear();
}

void cSoundManager::AddSound(string key, wstring path)
{
	CSound* sound;
	wchar_t Path[128];
	swprintf(Path, L"./Resource/Sound/%s.wav", path.c_str());
	m_Manager.Create(&sound, Path, DSBCAPS_CTRLVOLUME);
	m_sounds.insert(make_pair(key, sound));
}