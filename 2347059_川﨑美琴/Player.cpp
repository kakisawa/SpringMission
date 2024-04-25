#include "Player.h"
#include "Pad.h"
#include "DxLib.h"
#include "Rect.h"
#include <cassert>

namespace {
	constexpr int kJumpMaxCount = 2;	// �W�����v�����

	constexpr float kGravity = 0.18f;	// �d��
	constexpr float kJumpPow = 0.4f;	// �W�����v��

	constexpr float kWidht = 50.0f;
	constexpr float kHeight = 65.0f;

	constexpr float kColPosAdjustment = 0.5f;
}

// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Player::m_speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Player::m_scale = 0.002f;		// �X�P�[��

Player::Player() :
	m_modelHandle(-1),
	m_jumpCount(0),
	m_gravity(kGravity),
	m_isOnGround(true),
	m_isJump(false)
{
	m_modelHandle = MV1LoadModel("data/Robot.mv1");
	assert(m_modelHandle != -1);

	m_pos = VGet(147, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);
}

Player::~Player()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(m_modelHandle);
}

void Player::Update()
{
	if (m_pos.y >= 0)
	{
		m_pos = VSub(m_pos, VGet(0, m_gravity, 0));	// �d��
		m_isOnGround = false;						// �n�ʂɂ��Ă��Ȃ�
		m_gravity += 0.01f;							// �d�͉���
	}
	else
	{
		m_gravity = kGravity;						// �d�͂������l�ɒ���

		m_isOnGround = true;						// �n�ʂɂ��Ă���
		m_isJump = false;							// �W�����v(�㏸)���Ă��Ȃ�

		m_jumpCount = 0;
	}

	if (Pad::IsTrigger(PAD_INPUT_10))				// Space�L�[�����������n�ʂɂ��Ă���
	{
		m_isJump = true;							// �W�����v���Ă���
		m_jumpCount += 1;
	}
	if (m_isJump == true)							// �W�����v���Ă��銎�W�����v�̍ő哞�B�n�_�܂ōs���Ă��Ȃ��ꍇ
	{
		m_pos = VAdd(m_pos, VGet(0, kJumpPow, 0));
		if (m_jumpCount >= 2)
		{
			m_pos = VAdd(m_pos, VGet(0, kJumpPow * 0.5f, 0));
		}
	}

	m_dir = VGet(0, 0, 0);
	m_dir = VAdd(m_dir, VGet(1, 0, 0));

	// �[�����Z����
	if (VSquareSize(m_dir) > 0)
	{
		// ���K��
		m_dir = VNorm(m_dir);
	}

	// �|�W�V�������X�V.
	m_velocity = VScale(m_dir, m_speed);
	m_pos = VAdd(m_pos, m_velocity);

	// �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
	if (VSize(m_velocity) != 0)
	{
		m_dir = VNorm(m_velocity);
	}

	// 3D���f���̃X�P�[������
	MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_pos);

	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, -90.0f, 0.0f));

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y + kColPosAdjustment, m_pos.z,
		kWidht, kHeight);
}

void Player::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	////DrawFormatString(0, 0, 0xFFFFFF, "m_isJump=%d", m_isJump);
	////DrawFormatString(0, 20, 0xFFFFFF, "m_isOnGround=%d", m_isOnGround);
	////DrawFormatString(0, 0, 0xFFFFFF, "m_jumpCount=%d", m_jumpCount);
	////DrawFormatString(0, 150, 0xFFFFFF, "m_gravity=%f", m_gravity);

	DrawFormatString(500, 300, 0xFFFFFF, "m_pos.x=%.2f", m_pos.x);
	DrawFormatString(500, 320, 0xFFFFFF, "m_pos.y=%.2f", m_pos.y);
	DrawFormatString(500, 340, 0xFFFFFF, "m_pos.z=%.2f", m_pos.z);

	// �����蔻��̕\��
	m_colRect.Draw(0xFFFFFF, false); 
#endif
}
