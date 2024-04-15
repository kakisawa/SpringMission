#include "SceneTitle.h"
#include "SceneGame.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace {
	constexpr float kTitleGraphPosX = kScreenWidth * 0.15f;
	constexpr float kTitleGraphPosY = kScreenHeight * 0.2f;
	constexpr float kClickGraphPosX= kScreenWidth * 0.28f;
	constexpr float kClickGraphPosY = kScreenHeight * 0.73f;
}

SceneTitle::SceneTitle():
	m_displayCount(0),
	m_isSpace(false)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_graphTitle = LoadGraph("data/Title.png");
	m_graphClick = LoadGraph("data/ClickSpaceToGame.png");
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	Pad::Update();

	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		return std::make_shared<SceneGame>();
	}

	if (m_displayCount >= 80)
	{
		m_displayCount = 0;
	}
	m_displayCount++;

	return shared_from_this();
}

void SceneTitle::Draw()
{
	DrawExtendGraphF(kTitleGraphPosX, kTitleGraphPosY, 
		kScreenWidth*0.85f, kScreenHeight*0.5f,
		m_graphTitle, true);

	if (m_displayCount <= 60)
	{
		DrawGraphF(kClickGraphPosX, kClickGraphPosY, 
			m_graphClick, true);
	}

#ifdef _DEBUG
	DrawFormatString(0, 16, 0xFFFFFF,
		"%d", m_displayCount);
#endif
}

void SceneTitle::End()
{
}
