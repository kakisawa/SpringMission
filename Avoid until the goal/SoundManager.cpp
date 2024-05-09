#include "SoundManager.h"
#include "DxLib.h"

SoundManager::SoundManager()
{
	m_soundJump= LoadSoundMem("");
	m_soundButton = LoadSoundMem("");
	m_bgmDefo = LoadSoundMem("");
	m_bgmButtle = LoadSoundMem("");
	m_bgmGameClear = LoadSoundMem("");
	m_bgmGameOver = LoadSoundMem("");
}

SoundManager::~SoundManager()
{
	DeleteSoundMem(m_soundJump);
	DeleteSoundMem(m_soundButton);
	DeleteSoundMem(m_bgmDefo);
	DeleteSoundMem(m_bgmButtle);
	DeleteSoundMem(m_bgmGameClear);
	DeleteSoundMem(m_bgmGameOver);
}

void SoundManager::Init()
{
}

void SoundManager::Draw()
{
}

void SoundManager::End()
{
}

void SoundManager::SoundButton()
{
	PlaySoundMem(m_bgmButtle, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoundJump()
{
	PlaySoundMem(m_soundJump, DX_PLAYTYPE_BACK, true);
}

void SoundManager::BGMDefo()
{
	PlaySoundMem(m_bgmDefo, DX_PLAYTYPE_BACK, true);
}

void SoundManager::BGMButtle()
{
	PlaySoundMem(m_bgmButtle, DX_PLAYTYPE_BACK, true);
}

void SoundManager::BGMGameClear()
{
	PlaySoundMem(m_bgmGameClear, DX_PLAYTYPE_BACK, true);
}

void SoundManager::BGMGameOver()
{
	PlaySoundMem(m_bgmGameOver, DX_PLAYTYPE_BACK, true);
}
