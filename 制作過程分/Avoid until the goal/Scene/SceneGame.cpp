#include "SceneGame.h"
#include "SceneGameClear.h"
#include"SceneGameOver.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace {
	// ゲーム開始前説明描画位置
	constexpr float kExPosX = kScreenWidth * 0.23f;
	constexpr float kExPosY = kScreenHeight * 0.1f;

	constexpr float kClickGraphPosX = kScreenWidth * 0.28f;
	constexpr float kClickGraphPosY = kScreenHeight * 0.73f;

	// カウントダウン画像描画位置
	constexpr float CountDownX = static_cast<float>(kScreenWidth) * 0.5f - 53;
	constexpr float CountDownY = static_cast<float>(kScreenHeight) * 0.5f - 114;


	// ゲーム開始前カウント描画位置
	constexpr float kTimeCountPosX = kScreenWidth * 0.03f;
	constexpr float kTimeCountPosY = kScreenHeight * 0.05f;

	// ゲーム経過時間告知描画位置
	constexpr float kProgressTimePosX = kScreenWidth * 0.32f;
	constexpr float kProgressTimePosY = kScreenHeight * 0.15f;

	// ゲーム経過時間告知(20秒ごと)
	constexpr float kCountTime_20s = 1200.0f;
	constexpr float kCountTime_40s = 2400.0f;
	constexpr float kCountTime_60s = 3600.0f;
	constexpr float kCountTime_80s = 4800.0f;

	constexpr float kCountTime_Display = 180.0f;	// ゲーム経過時間告知描画時間(3秒)
	constexpr float kCountTime_Finish = 5400.0f;	// ゲーム時間(90秒)
}

SceneGame::SceneGame() :
	m_timeStartCount(kCountTime_Display),
	m_displayCount(0),
	m_timeCount(0.0f),
	m_enemyInterval(0),
	m_isTimeStartCountFlag(false),
	m_isTimeCountFlag(false),
	m_isGameOverFlag(false),
	m_isGameClearFlag(false)
{
	m_pEnemy.resize(m_enemyNum);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = std::make_shared<Enemy>();
	}
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_graph20sHavePassed = LoadGraph("data/20_progress.png");
	m_graph40sHavePassed = LoadGraph("data/40_progress.png");
	m_graph60sHavePassed = LoadGraph("data/60_progress.png");
	m_graph80sHavePassed = LoadGraph("data/80_progress.png");
	m_explanation = LoadGraph("data/Eexplanation.png");
	m_graphClick = LoadGraph("data/ClickSpaceToGame.png");
	m_count1Graph = LoadGraph("data/Count1.png");
	m_count2Graph = LoadGraph("data/Count2.png");
	m_count3Graph = LoadGraph("data/Count3.png");
}

std::shared_ptr<SceneBase> SceneGame::Update()
{
	Pad::Update();
	m_pCamera->Update(*m_pPlayer);


	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		m_isTimeStartCountFlag = true;
	}

	if (m_isTimeStartCountFlag == true)
	{
		if (m_timeStartCount <= 0)
		{
			m_isTimeCountFlag = true;
		}
		else {
			m_timeStartCount--;
		}
	}

	if (m_isTimeCountFlag == true && m_timeCount <= kCountTime_Finish)
	{
		m_timeCount++;

		m_pPlayer->Update();
		Rect playerRect = m_pPlayer->GetColRect();

		for (int i = 0; i < m_pEnemy.size(); i++)
		{

			m_pEnemy[i]->Update();

			Rect enemyRect = m_pEnemy[i]->GetColRect();
			if (playerRect.IsCollsion(enemyRect))
			{
				m_isGameOverFlag = true;
			}
		}

		//敵キャラクターの登場
		m_enemyInterval++;
		if (m_enemyInterval >= 60)
		{
			CreateEnemy();
			m_enemyInterval = 0;
		}
	}

	if (m_displayCount >= 80)
	{
		m_displayCount = 0;
	}
	m_displayCount++;

	if (Pad::IsTrigger(PAD_INPUT_1) || m_timeCount >= kCountTime_Finish)
	{
		return std::make_shared<SceneGameClear>();
	}
	if (Pad::IsTrigger(PAD_INPUT_2)|| m_isGameOverFlag == true)
	{
		return std::make_shared<SceneGameOver>();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}

void SceneGame::Draw()
{
#ifdef _DEBUG
	// デバッグ描画
	// XYZ軸
	float lineSize = 300.0f;
	DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

	DrawFormatString(0, 0, 0xFFFFFF, "%.1f", m_timeStartCount);
	DrawFormatString(0, 20, 0xFFFFFF, "m_isGameOverFlag=%d", m_isGameOverFlag);

#endif

	if (m_isTimeStartCountFlag== false)
	{
		DrawGraphF(kExPosX, kExPosY,
			m_explanation, true);
		if (m_displayCount <= 60)
		{
			DrawGraphF(kClickGraphPosX, kClickGraphPosY,
				m_graphClick, true);
		}
	}

	if (m_timeStartCount >= 0&& m_isTimeStartCountFlag==true)
	{
		// ゲーム開始前カウントダウン描画
		if (m_timeStartCount >= 121)
		{
			DrawExtendGraphF(CountDownX, CountDownY,
				CountDownX + 106, CountDownY + 228,
				m_count3Graph, true);
		}
		else if (m_timeStartCount <= 120 && m_timeStartCount >= 61)
		{
			DrawExtendGraphF(CountDownX, CountDownY,
				CountDownX + 106, CountDownY + 228,
				m_count2Graph, true);
		}
		else if (m_timeStartCount <= 60 && m_timeStartCount >= 1)
		{
			DrawExtendGraphF(CountDownX, CountDownY,
				CountDownX + 106, CountDownY + 228,
				m_count1Graph, true);
		}
	}
	

	if (m_isTimeCountFlag == true)
	{
		DrawExtendFormatStringF(kTimeCountPosX, kTimeCountPosY,
			3, 3, 0xFFFFFF,
			"経過時間:%.1f", m_timeCount / 60);

		m_pPlayer->Draw();

		for (int i = 0; i < m_pEnemy.size(); i++)
		{
			if (m_pEnemy[i])
			{
				m_pEnemy[i]->Draw();
			}
		}

		if (m_timeCount >= kCountTime_20s && m_timeCount <= kCountTime_20s + kCountTime_Display)
		{
			DrawGraphF(kProgressTimePosX, kProgressTimePosY,
				m_graph20sHavePassed, true);
		}
		else if (m_timeCount >= kCountTime_40s && m_timeCount <= kCountTime_40s + kCountTime_Display)
		{
			DrawGraphF(kProgressTimePosX, kProgressTimePosY,
				m_graph40sHavePassed, true);
		}
		else if (m_timeCount >= kCountTime_60s && m_timeCount <= kCountTime_60s + kCountTime_Display)
		{
			DrawGraphF(kProgressTimePosX, kProgressTimePosY,
				m_graph60sHavePassed, true);
		}
		else if (m_timeCount >= kCountTime_80s && m_timeCount <= kCountTime_80s + kCountTime_Display)
		{
			DrawGraphF(kProgressTimePosX, kProgressTimePosY,
				m_graph80sHavePassed, true);
		}
	}
}

void SceneGame::End()
{
}

void SceneGame::CreateEnemy()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])
		{
			m_pEnemy[i]->Start(19, 0.1f, 0);
			return;
		}
	}
}
