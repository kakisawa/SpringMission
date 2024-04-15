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

	bool m_isOnGround;		// プレイヤーが地面についているかのフラグ
	bool m_isJump;			// プレイヤーがジャンプ(上昇)中かどうかのフラグ
	bool m_isFall;			// プレイヤーがジャンプ(下降)中かどうかのフラグ


	VECTOR m_pos;
	VECTOR m_velocity;
	VECTOR m_dir;

	// 静的定数.
	static const float m_speed;
	static const float m_scale;
};

