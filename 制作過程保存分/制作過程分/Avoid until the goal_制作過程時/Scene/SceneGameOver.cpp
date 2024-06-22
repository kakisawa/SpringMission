#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace {
	constexpr float kTitleGraphPosX = kScreenWidth * 0.15f;
	constexpr float kTitleGraphPosY = kScreenHeight * 0.2f;
	constexpr float kClickGraphPosX = kScreenWidth * 0.2f;
	constexpr float kClickGraphPosY = kScreenHeight * 0.73f;
}

SceneGameOver::SceneGameOver() :
	m_displayCount(0),
	m_isSpace(false)
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	m_graphOver = LoadGraph("data/GameOver.png");
	m_graphClick = LoadGraph("data/ClickSpaceToTitle.png");
}

std::shared_ptr<SceneBase> SceneGameOver::Update()
{
	Pad::Update();

	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		return std::make_shared<SceneTitle>();
	}
	if (m_displayCount >= 80)
	{
		m_displayCount = 0;
	}
	m_displayCount++;

	return shared_from_this();	// é©êgÇÃshared_ptrÇï‘Ç∑
}

void SceneGameOver::Draw()
{
	DrawExtendGraphF(kTitleGraphPosX, kTitleGraphPosY, kScreenWidth * 0.85f, kScreenHeight * 0.5f, m_graphOver, true);
	if (m_displayCount <= 60)
	{
		DrawGraphF(kClickGraphPosX, kClickGraphPosY, m_graphClick, true);
	}


#ifdef _DEBUG
	DrawFormatString(0, 16, 0xFFFFFF, "%d", m_displayCount);

	if (m_isSpace == true)
	{
		DrawString(0, 0, "SpaceÉLÅ[ì¸óÕ", 0xFFFFFF);
	}
#endif
}

void SceneGameOver::End()
{
}
