#pragma once
#include "SceneBase.h"
class SceneGameClear :
	public SceneBase
{
public:
	SceneGameClear();
	virtual ~SceneGameClear();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();

private:
	int m_graphClear;		// �uGameClear�v�摜
	int m_graphClick;		// �uSpace�L�[���N���b�N�v�摜

	int m_displayCount;		// �uSpace�L�[���N���b�N�v�\���J�E���g

	bool m_isSpace;			// �X�y�[�X�L�[�������ꂽ���ǂ����̃t���O
};

