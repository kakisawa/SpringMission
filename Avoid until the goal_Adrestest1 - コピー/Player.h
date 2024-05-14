#pragma once
#include "DxLib.h"
#include "Rect.h"
#include <memory>

using namespace std;
class SoundManager;
class Player final
{
public:
	Player();
	~Player();

	void Update();
	void Draw();

	const VECTOR& GetPos() const { return m_pos; }
	const VECTOR& GetDir() const { return m_dir; }
	Rect GetColRect() const { return m_colRect; }		// �v���C���[�̓����蔻����擾����

	int GetModelHandle() const { return m_modelHandle; }

private:
	int m_modelHandle;		// ���f��
	int m_jumpCount;		// �W�����v�̉�

	float m_gravity;		// �d��

	bool m_isOnGround;		// �v���C���[���n�ʂɂ��Ă��邩�̃t���O
	bool m_isJump;			// �v���C���[���W�����v(�㏸)�����ǂ����̃t���O

	VECTOR m_pos;
	VECTOR m_velocity;
	VECTOR m_dir;

	Rect m_colRect;		// �����蔻��p�̋�`

	// �ÓI�萔.
	static const float m_speed;
	static const float m_scale;

	shared_ptr<SoundManager> m_pSound = make_shared<SoundManager>();
};