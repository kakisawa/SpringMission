#include "SoundManager.h"
#include "DxLib.h"

SoundManager::SoundManager()
{
	m_soundJump= LoadSoundMem("");
	m_soundButton = LoadSoundMem("");
	m_bgmDefo = LoadSoundMem("data/Sound/BGM_Defo2.mp3");
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

void SoundManager::Ring(int s)
{
	PlaySoundMem(s, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoundButton()
{
	Ring(m_bgmButtle);
}

void SoundManager::SoundJump()
{
	Ring(m_soundJump);
}

void SoundManager::BGMDefo()
{
	Ring(m_bgmDefo);
}

void SoundManager::BGMButtle()
{
	Ring(m_bgmButtle);
}

void SoundManager::BGMGameClear()
{
	Ring(m_bgmGameClear);
}

void SoundManager::BGMGameOver()
{
	Ring(m_bgmGameOver);
}
