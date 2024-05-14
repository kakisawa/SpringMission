#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"
#include "SoundManager.h"

namespace {
	constexpr float kTitleGraphPosX = kScreenWidth * 0.15f;
	constexpr float kTitleGraphPosY = kScreenHeight * 0.2f;
	constexpr float kClickGraphPosX = kScreenWidth * 0.2f;
	constexpr float kClickGraphPosY = kScreenHeight * 0.73f;
}

SceneGameOver::SceneGameOver() :
	m_displayCount(0),
	m_fadeAlpha(255),
	m_isSpace(false),
	m_isFadeIn(false),
	m_isFadeOut(false),
	m_isSceneEnd(false),
	m_graphBg1(-1),
	m_graphBg2(-1),
	m_graphBg3(-1),
	m_graphClick(-1),
	m_graphOver(-1)
{
	m_pSound->LoadSE();
	m_pSound->BGMGameOver();
}

SceneGameOver::~SceneGameOver()
{
	DeleteGraph(m_graphOver);
	DeleteGraph(m_graphClick);
	DeleteGraph(m_graphBg1);
	DeleteGraph(m_graphBg2);
	DeleteGraph(m_graphBg3);

	m_pSound->StopBGMGameOver();
}

void SceneGameOver::Init()
{
	m_graphOver = LoadGraph("data/GameOver2.png");
	m_graphClick = LoadGraph("data/ClickSpaceToTitle2.png");
	m_graphBg1 = LoadGraph("data/bg/background_layer_1.png");
	m_graphBg2 = LoadGraph("data/bg/background_layer_2.png");
	m_graphBg3 = LoadGraph("data/bg/background_layer_3.png");
}

std::shared_ptr<SceneBase> SceneGameOver::Update()
{
	Pad::Update();

	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		m_pSound->SoundButton();
		m_isFadeOut = true;
	}
	if (m_displayCount >= 80)
	{
		m_displayCount = 0;
	}
	m_displayCount++;

	// フェードイン
	if (m_isFadeOut == true)
	{
		
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
			m_isSceneEnd = true;
		}

		if (m_isSceneEnd == true)
		{
			return std::make_shared<SceneTitle>();
		}
	}

	// フェードアウト
	if (m_isFadeIn == false)
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
			m_isFadeIn = true;
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}

void SceneGameOver::Draw()
{
	DrawRotaGraph2(0, 0,
		0, 0,
		6, 0.0f,
		m_graphBg1, true);
	DrawRotaGraph2(0, 0,
		0, 0,
		6, 0.0f,
		m_graphBg2, true);
	DrawRotaGraph2(0, 0,
		0, 0,
		6, 0.0f,
		m_graphBg3, true);


	DrawExtendGraphF(kTitleGraphPosX, kTitleGraphPosY, kScreenWidth * 0.85f, kScreenHeight * 0.5f, m_graphOver, true);
	if (m_displayCount <= 60)
	{
		DrawGraphF(kClickGraphPosX, kClickGraphPosY, m_graphClick, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBoxAA(0, 0, kScreenWidth, kScreenHeight,
		0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく

#ifdef _DEBUG
	/*DrawFormatString(0, 16, 0xFFFFFF, "%d", m_displayCount);

	if (m_isSpace == true)
	{
		DrawString(0, 0, "Spaceキー入力", 0xFFFFFF);
	}*/
#endif
}

void SceneGameOver::End()
{
}
