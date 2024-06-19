#pragma once
#include "SceneBase.h"
#include <memory>]
#include <vector>

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
	virtual void End();

	void CreateEnemy();

private:
	// �o�ߎ��ԉ摜
	int m_graph20sHavePassed;
	int m_graph40sHavePassed;
	int m_graph60sHavePassed;
	int m_graph80sHavePassed;
	int m_explanation;
	int m_graphClick;
	int m_count3Graph;
	int m_count2Graph;
	int m_count1Graph;

	float m_timeStartCount;		// �Q�[���X�^�[�g�J�E���g
	float m_timeCount;			// �o�ߎ��ԃJ�E���g
	int m_displayCount;

	bool m_isTimeStartCountFlag;// �Q�[���X�^�[�g�J�E���g�t���O	
	bool m_isTimeCountFlag;		// �o�ߎ��ԃJ�E���g�J�n�t���O

	bool m_isGameOverFlag;		// �Q�[���I�[�o�[�t���O
	bool m_isGameClearFlag;		// �Q�[���N���A�t���O

	int m_enemyInterval;

	int m_enemyNum = 10;

	std::shared_ptr<Camera> m_pCamera = std::make_shared<Camera>();
	std::shared_ptr<Player> m_pPlayer = std::make_shared<Player>();
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;
};