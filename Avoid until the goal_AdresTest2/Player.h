#pragma once
#include "DxLib.h"
#include "Rect.h"

class Player final
{
public:
	Player();
	~Player();

	void Update();
	void Draw();

	const VECTOR& GetPos() const { return m_pos; }
	const VECTOR& GetDir() const { return m_dir; }
	Rect GetColRect() const { return m_colRect; }		// プレイヤーの当たり判定を取得する

	int GetModelHandle() const { return m_modelHandle; }

private:
	int m_modelHandle;		// モデル
	int m_jumpCount;		// ジャンプの回数

	float m_gravity;		// 重力

	bool m_isOnGround;		// プレイヤーが地面についているかのフラグ
	bool m_isJump;			// プレイヤーがジャンプ(上昇)中かどうかのフラグ

	VECTOR m_pos;
	VECTOR m_velocity;
	VECTOR m_dir;

	Rect m_colRect;		// 当たり判定用の矩形

	// 静的定数.
	static const float m_speed;
	static const float m_scale;
};

