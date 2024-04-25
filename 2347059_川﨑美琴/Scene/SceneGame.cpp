#include "SceneGame.h"
#include "SceneGameClear.h"
#include"SceneGameOver.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

using namespace std;

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
	m_isGameClearFlag(false),
	m_graph20sHavePassed(-1),
	m_graph40sHavePassed(-1)
{
	CreateEnemy();
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

shared_ptr<SceneBase> SceneGame::Update()
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
	}

	if (m_displayCount >= 80)
	{
		m_displayCount = 0;
	}
	m_displayCount++;

	if (m_timeCount >= kCountTime_Finish)
	{
		return make_shared<SceneGameClear>();
	}
	if (m_isGameOverFlag == true)
	{
		return make_shared<SceneGameOver>();
	}

	/*
	Pad::IsTrigger(PAD_INPUT_1) ||
	Pad::IsTrigger(PAD_INPUT_2)||
	*/

	return shared_from_this();	// 自身のshared_ptrを返す
}

void SceneGame::Draw()
{
#ifdef _DEBUG
	//// デバッグ描画
	//// XYZ軸
	//float lineSize = 300.0f;
	//DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	//DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	//DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

	//DrawFormatString(0, 0, 0xFFFFFF, "%.1f", m_timeStartCount);
	//DrawFormatString(0, 20, 0xFFFFFF, "m_isGameOverFlag=%d", m_isGameOverFlag);
#endif

	if (m_isTimeStartCountFlag == false)
	{
		DrawGraphF(kExPosX, kExPosY,
			m_explanation, true);
		if (m_displayCount <= 60)
		{
			DrawGraphF(kClickGraphPosX, kClickGraphPosY,
				m_graphClick, true);
		}
	}

	if (m_timeStartCount >= 0 && m_isTimeStartCountFlag == true)
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

namespace {
	constexpr float kEnemyPosYInit = 17.0f;
	constexpr float kEnemyPosYHigh = 1.5f;
	constexpr float kEnemyPosYLow = 0.0f;

	constexpr float kEnemyPosX = 4.0f;
	constexpr float kEnemyPosXLow = 5.0f;

	constexpr float kEnemyIntervalX = 0.6f;
}

void SceneGame::CreateEnemy()
{
	m_pEnemy.resize(m_enemyNum);

	m_pEnemy[0] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX, kEnemyPosYLow, 0.0f));
	m_pEnemy[1] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 2, kEnemyPosYHigh, 0.0f));
	m_pEnemy[2] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 3, kEnemyPosYLow, 0.0f));
	m_pEnemy[3] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 4, kEnemyPosYHigh, 0.0f));
	m_pEnemy[4] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 5, kEnemyPosYLow, 0.0f));
	m_pEnemy[5] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 6, kEnemyPosYHigh, 0.0f));
	m_pEnemy[6] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 7, kEnemyPosYLow, 0.0f));
	m_pEnemy[7] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 8, kEnemyPosYHigh, 0.0f));
	m_pEnemy[8] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 9, kEnemyPosYLow, 0.0f));
	m_pEnemy[9] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 10, kEnemyPosYHigh, 0.0f));

	// 20秒 50
	m_pEnemy[10] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 11, kEnemyPosYLow, 0.0f));
	m_pEnemy[11] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 11.2f, kEnemyPosYLow, 0.0f));
	m_pEnemy[12] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 12, kEnemyPosYLow, 0.0f));
	m_pEnemy[13] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 13, kEnemyPosYLow, 0.0f));
	m_pEnemy[14] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 13.2f, kEnemyPosYLow, 0.0f));
	m_pEnemy[15] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 14, kEnemyPosYHigh, 0.0f));
	m_pEnemy[16] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 15, kEnemyPosYLow, 0.0f));
	m_pEnemy[17] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 15.2f, kEnemyPosYLow, 0.0f));
	m_pEnemy[18] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 16, kEnemyPosYLow, 0.0f));
	m_pEnemy[19] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 16.2f, kEnemyPosYLow, 0.0f));
	m_pEnemy[20] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 17, kEnemyPosYLow, 0.0f));
	m_pEnemy[21] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 17.5f, kEnemyPosYHigh, 0.0f));
	m_pEnemy[22] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 17.7f, kEnemyPosYHigh, 0.0f));
	m_pEnemy[23] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 18.5, kEnemyPosYLow, 0.0f));
	m_pEnemy[24] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 18.7f, kEnemyPosYLow, 0.0f));
	m_pEnemy[25] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 20, kEnemyPosYHigh, 0.0f));
	m_pEnemy[26] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 21, kEnemyPosYLow, 0.0f));
	m_pEnemy[27] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 21.2f, kEnemyPosYLow, 0.0f));
	m_pEnemy[28] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 22, kEnemyPosYLow, 0.0f));
	m_pEnemy[29] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 22.2f, kEnemyPosYLow, 0.0f));
	m_pEnemy[30] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 23, kEnemyPosYHigh, 0.0f));
	m_pEnemy[31] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 23.2f, kEnemyPosYHigh, 0.0f));
	m_pEnemy[32] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 24, kEnemyPosYLow, 0.0f));
	
	// 40秒 110
	m_pEnemy[33] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 25, kEnemyPosYLow, 0.0f));
	m_pEnemy[34] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * (25 + kEnemyIntervalX * 1), kEnemyPosYLow, 0.0f));
	m_pEnemy[35] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * (25 + kEnemyIntervalX * 2), kEnemyPosYLow, 0.0f));
	m_pEnemy[36] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * (25 + kEnemyIntervalX * 3), kEnemyPosYLow, 0.0f));
	m_pEnemy[37] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * (25 + kEnemyIntervalX * 4), kEnemyPosYLow, 0.0f));
	m_pEnemy[38] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * (25 + kEnemyIntervalX * 5), kEnemyPosYLow, 0.0f));
	m_pEnemy[39] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * (25 + kEnemyIntervalX * 6), kEnemyPosYLow, 0.0f));
	m_pEnemy[40] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * (25 + kEnemyIntervalX * 7), kEnemyPosYLow, 0.0f));
	m_pEnemy[41] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 30, kEnemyPosYLow, 0.0f));
	m_pEnemy[42] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 30.2f, kEnemyPosYLow, 0.0f));
	m_pEnemy[43] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 30.8f, kEnemyPosYLow, 0.0f));
	m_pEnemy[44] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 31, kEnemyPosYLow, 0.0f));
	m_pEnemy[45] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 32, kEnemyPosYLow, 0.0f));
	m_pEnemy[46] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 32.1f, kEnemyPosYHigh, 0.0f));
	m_pEnemy[47] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 33.5f, kEnemyPosYHigh, 0.0f));
	m_pEnemy[48] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 33.6f, kEnemyPosYLow, 0.0f));
	m_pEnemy[49] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 34.5, kEnemyPosYLow, 0.0f));
	m_pEnemy[50] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 34.7f, kEnemyPosYLow, 0.0f));
	m_pEnemy[51] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 36, kEnemyPosYHigh, 0.0f));
	m_pEnemy[52] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 37, kEnemyPosYLow, 0.0f));
	m_pEnemy[53] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 37.1f, kEnemyPosYHigh, 0.0f));

	// 60秒　170
	m_pEnemy[54] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 38, kEnemyPosYLow, 0.0f));
	m_pEnemy[55] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 38.1f, kEnemyPosYHigh, 0.0f));
	m_pEnemy[56] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 39, kEnemyPosYLow, 0.0f));
	
	m_pEnemy[57] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 40, kEnemyPosYLow, 0.0f));
	m_pEnemy[58] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 40.2f, kEnemyPosYLow, 0.0f));
	m_pEnemy[59] = make_shared<Enemy>(VGet(kEnemyPosYInit + kEnemyPosX * 41, kEnemyPosYLow, 0.0f));


	// 80秒

	// 90秒


}