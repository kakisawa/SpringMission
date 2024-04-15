#include "Player.h"
#include "Pad.h"
#include "DxLib.h"

// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Player::m_speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Player::m_scale = 0.002f;		// �X�P�[��

Player::Player():
	m_modelHandle(-1),
	m_isOnGround(true),
	m_isJump(false),
	m_isFall(false)
{
	m_modelHandle = MV1LoadModel("data/Robot.mv1");

	m_pos = VGet(1, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir=VGet(0, 0, 1);
}

Player::~Player()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(m_modelHandle);
}

void Player::Update()
{
	Pad::Update();

	if (m_pos.y >= 0)
	{
		m_pos = VSub(m_pos, VGet(0, 0.18f, 0));	// �d��
		m_isOnGround = false;					// �n�ʂɂ��Ă��Ȃ�
	}
	else
	{
		m_isOnGround = true;					// �n�ʂɂ��Ă���
		m_isJump = false;						// �W�����v(�㏸)���Ă��Ȃ�
		m_isFall = false;						// �W�����v(���~)���Ă��Ȃ�
	}

	if (Pad::IsTrigger(PAD_INPUT_10) && m_isOnGround == true)	// Space�L�[�����������n�ʂɂ��Ă���
	{
		m_isJump = true;						// �W�����v���Ă���
	}
	if (m_isJump==true)		// �W�����v���Ă��銎�W�����v�̍ő哞�B�n�_�܂ōs���Ă��Ȃ��ꍇ
	{
		
		if (m_isFall == false)
		{
			m_pos = VAdd(m_pos, VGet(0, 0.4f, 0));
			if (m_pos.y >= 5.0f)
			{
				m_isFall = true;
			}
		}
	}
	
	//m_dir = VGet(0, 0, 0);
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
	//printfDx("%f %f %f\n", m_dir.x, m_dir.y, m_dir.z);

	// 3D���f���̃X�P�[������
	MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_pos);

	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, -90.0f, 0.0f));
}

void Player::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

	DrawFormatString(0, 0, 0xFFFFFF, "m_isJump=%d",m_isJump);
	DrawFormatString(0, 20, 0xFFFFFF, "m_isOnGround=%d", m_isOnGround);
	DrawFormatString(0, 40, 0xFFFFFF, "m_isFall=%d", m_isFall);

	//printfDx("%f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
}
