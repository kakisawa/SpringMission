#include "SceneTitle.h"
#include "SceneGame.h"
#include "SoundManager.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"
#include "SoundManager.h"

namespace {
	// �uAvoid until the goal�v�摜���W
	constexpr float kTitleGraphPosX = kScreenWidth * 0.15f;
	constexpr float kTitleGraphPosY = kScreenHeight * 0.2f;
	// �uSpace�L�[���N���b�N�v�摜���W
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
	// �摜�ǂݍ���
	m_graphTitle = LoadGraph("data/Title2.png");
	m_graphClick = LoadGraph("data/ClickSpaceToGame2.png");
	m_graphBg = LoadGraph("data/Bg/foggy-forest2.png");

	m_pSound->LoadSE();		// SE���[�h
	m_pSound->BGMDefo();	// BGM�𗬂�
}

SceneTitle::~SceneTitle()
{
	// �摜�폜
	DeleteGraph(m_graphTitle);
	DeleteGraph(m_graphClick);
	DeleteGraph(m_graphBg);
}

shared_ptr<SceneBase> SceneTitle::Update()
{
	Pad::Update();

	// �t�F�[�h�C��
	if (m_isFadeIn == true)
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
			m_isFadeIn = false;
		}
	}

	// �uSpace�L�[���N���b�N�v�摜�_�ŗp
	if (m_displayCount >= 80)
	{
		m_displayCount = 0;
	}
	m_displayCount++;

	if (Pad::IsTrigger(PAD_INPUT_10))
	{
		m_pSound->SoundButton();
		m_isFadeOut = true;
		m_isFadeIn = false;
	}

	// �t�F�[�h�A�E�g
	if (m_isFadeOut == true)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_pSound->StopBGMDefo();	// BGM���~�߂�
			m_isSceneEnd = true;
			m_fadeAlpha = 255;
		}

		if (m_isSceneEnd == true)
		{
			return make_shared<SceneGame>();	// �Q�[���V�[���֍s��
		}
	}

	return shared_from_this();
}

void SceneTitle::Draw()
{
	DrawRotaGraph2(0, 0, 0, 0, 1, 0.0f, m_graphBg, true);	// �w�i�`��

	// �^�C�g���摜�`��
	DrawExtendGraphF(kTitleGraphPosX, kTitleGraphPosY,
		kScreenWidth * 0.85f, kScreenHeight * 0.5f,
		m_graphTitle, true);

	// �uSpace�L�[���N���b�N�v�摜�`��
	if (m_displayCount <= 60)
	{
		DrawGraphF(kClickGraphPosX, kClickGraphPosY,
			m_graphClick, true);
	}

	// �t�F�[�h�C���E�t�F�[�h�A�E�g�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBoxAA(0, 0, kScreenWidth, kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}