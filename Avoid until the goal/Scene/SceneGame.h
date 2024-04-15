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
	// �o�ߎ��ԉ摜
	int m_graph20sHavePassed;
	int m_graph40sHavePassed;
	int m_graph60sHavePassed;
	int m_graph80sHavePassed;

	float m_timeStartCount;		// �Q�[���X�^�[�g�J�E���g
	float m_timeCount;			// �o�ߎ��ԃJ�E���g

	bool m_isTimeStartCountFlag;// �Q�[���X�^�[�g�J�E���g�t���O	
	bool m_isTimeCountFlag;		// �o�ߎ��ԃJ�E���g�J�n�t���O

	bool m_isGameOverFlag;		// �Q�[���I�[�o�[�t���O
	bool m_isGameClearFlag;		// �Q�[���N���A�t���O

	shared_ptr<Camera> m_pCamera = make_shared<Camera>();
	shared_ptr<Player> m_pPlayer = make_shared<Player>();
	shared_ptr<Enemy> m_pEnemy = make_shared<Enemy>();
};