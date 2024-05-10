#include "SceneGameClear.h"
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

SceneGameClear::SceneGameClear():
	m_displayCount(0),
	m_fadeAlpha(255),
	m_isSpace(false),
	m_isFadeIn(false),
	m_isFadeOut(false),
	m_isSceneEnd(false)
{
}

SceneGameClear::~SceneGameClear()
{
	DeleteGraph(m_graphClear);
	DeleteGraph(m_graphClick);
	DeleteGraph(m_graphBg);
}

void SceneGameClear::Init()
{
	m_graphClear = LoadGraph("data/GameClear2.png");
	m_graphClick = LoadGraph("data/ClickSpaceToTitle2.png");
	m_graphBg = LoadGraph("data/Bg/forest5.png");
}

std::shared_ptr<SceneBase> SceneGameClear::Update(const SoundManager& mng)
{
	Pad::Update();

	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		m_isFadeOut = true;
	}

	if (m_displayCount >= 80)
	{
		m_displayCount = 0;
	}
	m_displayCount++;

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

	

	return shared_from_this();	// 自身のshared_ptrを返す
}

void SceneGameClear::Draw()
{
	DrawRotaGraph2(0, 0,
		0, 0,
		1, 0.0f,
		m_graphBg, true);

	DrawExtendGraphF(kTitleGraphPosX, kTitleGraphPosY,
		kScreenWidth * 0.85f, kScreenHeight * 0.5f, m_graphClear, true);
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

void SceneGameClear::End()
{
}
