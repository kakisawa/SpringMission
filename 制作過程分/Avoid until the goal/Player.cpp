#include "Player.h"
#include "Pad.h"
#include "DxLib.h"
#include "Rect.h"
#include <cassert>

namespace {
	constexpr int kJumpMaxCount = 2;	// ジャンプ上限回数

	constexpr float kGravity = 0.18f;	// 重力
	constexpr float kJumpPow = 0.4f;	// ジャンプ力

	constexpr float kWidht = 50.0f;
	constexpr float kHeight = 65.0f;

	constexpr float kColPosAdjustment = 0.5f;
}

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::m_speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Player::m_scale = 0.002f;		// スケール

Player::Player() :
	m_modelHandle(-1),
	m_jumpCount(0),
	m_gravity(kGravity),
	m_isOnGround(true),
	m_isJump(false)
{
	m_modelHandle = MV1LoadModel("data/Robot.mv1");
	assert(m_modelHandle != -1);

	m_pos = VGet(1, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);
}

Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);
}

void Player::Update()
{
	if (m_pos.y >= 0)
	{
		m_pos = VSub(m_pos, VGet(0, m_gravity, 0));	// 重力
		m_isOnGround = false;						// 地面についていない
		m_gravity += 0.01f;							// 重力加速
	}
	else
	{
		m_gravity = kGravity;					// 重力を初期値に直す

		m_isOnGround = true;					// 地面についている
		m_isJump = false;						// ジャンプ(上昇)していない

		m_jumpCount = 0;
	}

	if (Pad::IsTrigger(PAD_INPUT_10))	// Spaceキーを押した且つ地面についている
	{
		m_isJump = true;						// ジャンプしている
		m_jumpCount += 1;
	}
	if (m_isJump == true)		// ジャンプしている且つジャンプの最大到達地点まで行っていない場合
	{

		m_pos = VAdd(m_pos, VGet(0, kJumpPow, 0));
		if (m_jumpCount == 2)
		{
			m_pos = VAdd(m_pos, VGet(0, kJumpPow * 0.5f, 0));
		}
	}

	m_dir = VGet(0, 0, 0);
	m_dir = VAdd(m_dir, VGet(1, 0, 0));

	// ゼロ除算避け
	if (VSquareSize(m_dir) > 0)
	{
		// 正規化
		m_dir = VNorm(m_dir);
	}

	// ポジションを更新.
	m_velocity = VScale(m_dir, m_speed);
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
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, -90.0f, 0.0f));

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y + kColPosAdjustment, m_pos.z,
		kWidht, kHeight);
}

void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	//DrawFormatString(0, 0, 0xFFFFFF, "m_isJump=%d", m_isJump);
	//DrawFormatString(0, 20, 0xFFFFFF, "m_isOnGround=%d", m_isOnGround);
	//DrawFormatString(0, 0, 0xFFFFFF, "m_jumpCount=%d", m_jumpCount);
	//DrawFormatString(0, 150, 0xFFFFFF, "m_gravity=%f", m_gravity);

	DrawFormatString(500, 300, 0xFFFFFF, "m_pos.x=%.2f", m_pos.x);
	DrawFormatString(500, 320, 0xFFFFFF, "m_pos.y=%.2f", m_pos.y);
	DrawFormatString(500, 340, 0xFFFFFF, "m_pos.z=%.2f", m_pos.z);

	// 当たり判定の表示
	m_colRect.Draw(0xFFFFFF, false); 
#endif
}
