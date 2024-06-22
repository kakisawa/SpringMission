#include "Enemy.h"
#include "DxLib.h"
#include "Rect.h"
#include "Player.h"
#include <cassert>

// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Enemy::m_speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Enemy::m_scale =0.003f;		// �X�P�[��

namespace
{
	constexpr float kWidht = 50.0f;
	constexpr float kHeight = 60.0f;

	constexpr float kColPosAdjustment = 1.4f;
}

Enemy::Enemy():
	m_modelHandle(-1),
	m_isExist(false)
{
	m_modelHandle = MV1LoadModel("data/Bee.mv1");
	assert(m_modelHandle != -1);

	m_pos = VGet(19, 0.1f, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);
}

Enemy::~Enemy()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(m_modelHandle);
}

void Enemy::Update()
{
	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y * kColPosAdjustment, m_pos.z,
		kWidht, kHeight);

	m_dir = VGet(0, 0, 0);
	//m_dir = VAdd(m_dir, VGet(1, 0, 0));

	// �[�����Z����
	if (VSquareSize(m_dir) > 0)
	{
		// ���K��
		m_dir = VNorm(m_dir);
	}

	//�|�W�V�������X�V.
	m_velocity = VScale(m_dir, -m_speed);
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
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
}

void Enemy::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(0xff0000, false);

	DrawFormatString(300, 300, 0xFFFFFF, "m_pos.x=%.2f", m_pos.x);
	DrawFormatString(300, 320, 0xFFFFFF, "m_pos.y=%.2f", m_pos.y);
	DrawFormatString(300, 340, 0xFFFFFF, "m_pos.z=%.2f", m_pos.z);

	DrawFormatString(300, 360, 0xFFFFFF, "m_colRect=%.2f", m_colRect);
#endif
}


void Enemy::Start(float x, float y,float z)
{
	m_isExist = true;	// �G���o��������

	// �G�̍��W���Z�b�g����
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}
