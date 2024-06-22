#include "Enemy.h"
#include "DxLib.h"
#include "Rect.h"
#include "Player.h"
#include <cassert>

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Enemy::m_speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Enemy::m_scale =0.003f;		// スケール

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
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);
}

void Enemy::Update()
{
	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y * kColPosAdjustment, m_pos.z,
		kWidht, kHeight);

	m_dir = VGet(0, 0, 0);
	//m_dir = VAdd(m_dir, VGet(1, 0, 0));

	// ゼロ除算避け
	if (VSquareSize(m_dir) > 0)
	{
		// 正規化
		m_dir = VNorm(m_dir);
	}

	//ポジションを更新.
	m_velocity = VScale(m_dir, -m_speed);
	m_pos = VAdd(m_pos, m_velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(m_velocity) != 0)
	{
		m_dir = VNorm(m_velocity);
	}

	// 3Dモデルのスケール決定
	MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pos);

	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
}

void Enemy::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(0xff0000, false);

	DrawFormatString(300, 300, 0xFFFFFF, "m_pos.x=%.2f", m_pos.x);
	DrawFormatString(300, 320, 0xFFFFFF, "m_pos.y=%.2f", m_pos.y);
	DrawFormatString(300, 340, 0xFFFFFF, "m_pos.z=%.2f", m_pos.z);

	DrawFormatString(300, 360, 0xFFFFFF, "m_colRect=%.2f", m_colRect);
#endif
}


void Enemy::Start(float x, float y,float z)
{
	m_isExist = true;	// 敵を出現させる

	// 敵の座標をセットする
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}
