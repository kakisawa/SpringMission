#include "Bg.h"
#include "Game.h"
#include "DxLib.h"

namespace {

	// スクロール移動量
	constexpr float kBgScroll1 = 0.3f;
	constexpr float kBgScroll2 = 0.5f;
	constexpr float kBgScroll3 = 0.8f;
	constexpr float kBgScroll4 = 1.0f;


	// 背景の拡大率
	constexpr int kBgScale = 5;
}

Bg::Bg():
	m_bg1(-1),
	m_bg2(-1),
	m_bg3(-1),
	m_bg4(-1),
	m_bg5(-1),
	m_pos(VGet(0,0,0)),
	m_pos2(VGet(0, 0, 0)),
	m_pos3(VGet(0, 0, 0)),
	m_pos4(VGet(0, 0, 0)),
	m_scrollX_1(0),
	m_scrollX_2(0),
	m_scrollX_3(0),
	m_scrollX_4(0)
{
	m_bg1 = LoadGraph("data/Bg/plx-1.png");
	m_bg2 = LoadGraph("data/Bg/plx-2.png");
	m_bg3 = LoadGraph("data/Bg/plx-3.png");
	m_bg4 = LoadGraph("data/Bg/plx-4.png");
	m_bg5 = LoadGraph("data/Bg/plx-5.png");
}

Bg::~Bg()
{
	DeleteGraph(m_bg1);
	DeleteGraph(m_bg2);
	DeleteGraph(m_bg3);
	DeleteGraph(m_bg4);
	DeleteGraph(m_bg5);
}

void Bg::Init()
{

}

void Bg::Update()
{
	// 背景スクロール
	m_scrollX_1 += kBgScroll1;

	m_scrollX_2 += kBgScroll2;

	m_scrollX_3 += kBgScroll3;

	m_scrollX_4 += kBgScroll4;
}

void Bg::Draw()
{
	Size bgSize;
	GetGraphSize(m_bg1, &bgSize.m_width, &bgSize.m_height);
	

	// スクロール量を計算
	int scrollBg = static_cast<int>(m_scrollX_1) % static_cast<int>(bgSize.m_width * kBgScale);
	int scrollBg2 = static_cast<int>(m_scrollX_2) % static_cast<int>(bgSize.m_width * kBgScale);
	int scrollBg3 = static_cast<int>(m_scrollX_3) % static_cast<int>(bgSize.m_width * kBgScale);
	int scrollBg4 = static_cast<int>(m_scrollX_4) % static_cast<int>(bgSize.m_width * kBgScale);

	// 一番下
	DrawRotaGraph2(m_pos.x, m_pos.y,
		0, 0,
		kBgScale, 0.0f,
		m_bg1, true);

	for (int index = 0; index < 4; index++)
	{
		// 下から2番目
		DrawRotaGraph2(-scrollBg + index * bgSize.m_width * kBgScale,
			m_pos.y,
			0, 0,
			kBgScale, 0.0f,
			m_bg2, true);

		// 下から3番目
		DrawRotaGraph2(-scrollBg2 + index * bgSize.m_width * kBgScale,
			m_pos.y,
			0, 0,
			kBgScale, 0.0f,
			m_bg3, true);

		// 下から4番目
		DrawRotaGraph2(-scrollBg3 + index * bgSize.m_width * kBgScale,
			m_pos.y,
			0, 0,
			kBgScale, 0.0f,
			m_bg4, true);

		// 下から5番目(一番)
		DrawRotaGraph2(-scrollBg4 + index * bgSize.m_width * kBgScale,
			m_pos.y,
			0, 0,
			kBgScale, 0.0f,
			m_bg5, true);
	}

}
