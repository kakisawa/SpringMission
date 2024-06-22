#pragma once
#include "DxLib.h"
#include "Rect.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Update();
	void Draw();

	const VECTOR& GetPos() const { return m_pos; }
	const VECTOR& GetDir() const { return m_dir; }
	Rect GetColRect() const { return m_colRect; }

	int GetModelHandle() const { return m_modelHandle;}

	void Start(float x, float y,float z);

private:
	int m_modelHandle;

	bool m_isExist;			// 存在するかフラグ

	VECTOR m_pos;			// 
	VECTOR m_velocity;
	VECTOR m_dir;
	Rect m_colRect;			// 当たり判定用の矩形

	// 静的定数.
	static const float m_speed;
	static const float m_scale;

};

