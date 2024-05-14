#include "SceneTitle.h"
#include "SceneGame.h"
#include "SoundManager.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"
#include "SoundManager.h"

namespace {
	constexpr float kTitleGraphPosX = kScreenWidth * 0.15f;
	constexpr float kTitleGraphPosY = kScreenHeight * 0.2f;
	constexpr float kClickGraphPosX = kScreenWidth * 0.28f;
	constexpr float kClickGraphPosY = kScreenHeight * 0.73f;
}

SceneTitle::SceneTitle() :
	m_displayCount(0),
	m_fadeAlpha(255),
	m_isSpace(false),
	m_isFadeIn(true),
	m_isFadeOut(false),
	m_isSceneEnd(false),
	m_graphBg(-1),
	m_graphClick(-1),
	m_graphTitle(-1)
{
	m_pSound->LoadSE();
	m_pSound->BGMDefo();
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_graphTitle);
	DeleteGraph(m_graphClick);
	DeleteGraph(m_graphBg);

	m_pSound->StopBGMDefo();
}

void SceneTitle::Init()
{
	m_graphTitle = LoadGraph("data/Title2.png");
	m_graphClick = LoadGraph("data/ClickSpaceToGame2.png");
	m_graphBg = LoadGraph("data/Bg/foggy-forest2.png");
}

std::shared_ptr<SceneBase> SceneTitle::Update()
{
	Pad::Update();

	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		m_pSound->SoundButton();
		m_isFadeOut = true;
		m_isFadeIn = false;
	}

	if (m_isFadeIn == true)
	{
		// フェードアウト
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
			m_isFadeIn = false;
		}
	}

	if (m_isFadeOut==true)
	{
		// フェードイン
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_isSceneEnd = true;
			m_fadeAlpha = 255;
		}

		if (m_isSceneEnd == true)
		{
			return std::make_shared<SceneGame>();
		}
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
	DrawRotaGraph2(0, 0,
		0, 0,
		1, 0.0f,
		m_graphBg, true);

	DrawExtendGraphF(kTitleGraphPosX, kTitleGraphPosY,
		kScreenWidth * 0.85f, kScreenHeight * 0.5f,
		m_graphTitle, true);

	if (m_displayCount <= 60)
	{
		DrawGraphF(kClickGraphPosX, kClickGraphPosY,
			m_graphClick, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBoxAA(0, 0, kScreenWidth, kScreenHeight,
		0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく

#ifdef _DEBUG
	/*DrawFormatString(0, 16, 0xFFFFFF,
		"%d", m_displayCount);*/
#endif
}
