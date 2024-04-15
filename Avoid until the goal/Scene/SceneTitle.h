#pragma once
#include "SceneBase.h"
class SceneTitle:
	public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	int m_graphTitle;		// �^�C�g�����S�摜
	int m_graphClick;		// �uSpace�L�[���N���b�N�v�摜

	int m_displayCount;		// �uSpace�L�[���N���b�N�v�\���J�E���g

	bool m_isSpace;			// �X�y�[�X�L�[�������ꂽ���ǂ����̃t���O
};
