#pragma once
#include "SceneBase.h"
#include <memory>
#include <iostream>

using namespace std;

class Camera;
class Player;
class Enemy;

class SceneGame :
	public SceneBase
{
public:
	SceneGame();
	virtual ~SceneGame();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();

private:
	// 経過時間画像
	int m_graph20sHavePassed;
	int m_graph40sHavePassed;
	int m_graph60sHavePassed;
	int m_graph80sHavePassed;

	float m_timeStartCount;		// ゲームスタートカウント
	float m_timeCount;			// 経過時間カウント

	bool m_isTimeStartCountFlag;// ゲームスタートカウントフラグ	
	bool m_isTimeCountFlag;		// 経過時間カウント開始フラグ

	bool m_isGameOverFlag;		// ゲームオーバーフラグ
	bool m_isGameClearFlag;		// ゲームクリアフラグ

	shared_ptr<Camera> m_pCamera = make_shared<Camera>();
	shared_ptr<Player> m_pPlayer = make_shared<Player>();
	shared_ptr<Enemy> m_pEnemy = make_shared<Enemy>();
};