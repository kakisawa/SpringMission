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
	// �Q�[���J�n�O�����`��ʒu
	constexpr float kExPosX = kScreenWidth * 0.23f;
	constexpr float kExPosY = kScreenHeight * 0.1f;

	constexpr float kClickGraphPosX = kScreenWidth * 0.28f;
	constexpr float kClickGraphPosY = kScreenHeight * 0.73f;

	// �J�E���g�_�E���摜�`��ʒu
	constexpr float CountDownX = static_cast<float>(kScreenWidth) * 0.5f - 53;
	constexpr float CountDownY = static_cast<float>(kScreenHeight) * 0.5f - 114;

	// �Q�[���J�n�O�J�E���g�`��ʒu
	constexpr float kTimeCountPosX = kScreenWidth * 0.03f;
	constexpr float kTimeCountPosY = kScreenHeight * 0.05f;

	// �Q�[���o�ߎ��ԍ��m�`��ʒu
	constexpr float kProgressTimePosX = kScreenWidth * 0.32f;
	constexpr float kProgressTimePosY = kScreenHeight * 0.15f;

	// �Q�[���o�ߎ��ԍ��m(20�b����)
	constexpr float kCountTime_20s = 1200.0f;
	constexpr float kCountTime_40s = 2400.0f;
	constexpr float kCountTime_60s = 3600.0f;
	constexpr float kCountTime_80s = 4800.0f;

	constexpr float kCountTime_Display = 180.0f;	// �Q�[���o�ߎ��ԍ��m�`�掞��(3�b)
	constexpr float kCountTime_Finish = 5400.0f;	// �Q�[������(90�b)
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
	}

	if (m_displayCount >= 80)
	{
		m_displayCount = 0;
	}
	m_displayCount++;

	if ( m_timeCount >= kCountTime_Finish)
	{
		return std::make_shared<SceneGameClear>();
	}
	if (m_isGameOverFlag == true)
	{
		return std::make_shared<SceneGameOver>();
	}

	/*
	Pad::IsTrigger(PAD_INPUT_1) ||
	Pad::IsTrigger(PAD_INPUT_2)||
	*/

	return shared_from_this();	// ���g��shared_ptr��Ԃ�
}

void SceneGame::Draw()
{
#ifdef _DEBUG
	//// �f�o�b�O�`��
	//// XYZ��
	//float lineSize = 300.0f;
	//DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	//DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	//DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

	//DrawFormatString(0, 0, 0xFFFFFF, "%.1f", m_timeStartCount);
	//DrawFormatString(0, 20, 0xFFFFFF, "m_isGameOverFlag=%d", m_isGameOverFlag);
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
		// �Q�[���J�n�O�J�E���g�_�E���`��
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
			"�o�ߎ���:%.1f", m_timeCount / 60);

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
	constexpr float kEnemyPosYHigh = 1.5f;	
	constexpr float kEnemyPosYLow = 0.0f;	



}

void SceneGame::CreateEnemy()
{
	m_pEnemy.resize(m_enemyNum);
	for (int i = 0; i < m_pEnemy.size(); i+2)
	{
		m_pEnemy[i] = std::make_shared<Enemy>(VGet(5.0f + 5.0f * i, kEnemyPosYHigh, 0.0f));
		/*m_pEnemy[i] = std::make_shared<Enemy>(VGet(10.0f, kEnemyPosYHigh, 0.0f));
		m_pEnemy[i] = std::make_shared<Enemy>(VGet(15.0f, kEnemyPosYLow, 0.0f));
		m_pEnemy[i] = std::make_shared<Enemy>(VGet(20.0f, kEnemyPosYHigh, 0.0f));*/

		if (i % 2 == 1)
		{
			m_pEnemy[i] = std::make_shared<Enemy>(VGet(5.0f + 5.0f * i, kEnemyPosYHigh, 0.0f));
		}
		else
		{

		}


	}

	

	/*for (int i = 0; i < m_pEnemy.size(); i++)
	{
		VECTOR pos = VGet(19.0f+i * 5.0f, 0.0f, 0.0f);
		m_pEnemy[0] = std::make_shared<Enemy>(VGet(19.0f + i * 5.0f, 0.0f, 0.0f));
	}*/
}