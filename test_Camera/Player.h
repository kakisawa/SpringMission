#pragma once
#include "DxLib.h"

class Player final
{
public:
	Player();
	~Player();

	void Update();
	void Draw();

	int GetModelHandle() const { return m_modelHandle; }

	const VECTOR& GetPos() const { return m_pos; }
	const VECTOR& GetDir() const { return m_dir; }

private:
	int m_modelHandle;

	bool m_isOnGround;		// �v���C���[���n�ʂɂ��Ă��邩�̃t���O
	bool m_isJump;			// �v���C���[���W�����v(�㏸)�����ǂ����̃t���O
	bool m_isFall;			// �v���C���[���W�����v(���~)�����ǂ����̃t���O


	VECTOR m_pos;
	VECTOR m_velocity;
	VECTOR m_dir;

	// �ÓI�萔.
	static const float m_speed;
	static const float m_scale;
};

