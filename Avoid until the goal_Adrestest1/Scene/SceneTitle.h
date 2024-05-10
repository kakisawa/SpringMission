#pragma once
#include "SceneBase.h"
class SoundManager;
class SceneTitle:
	public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(const SoundManager& mng);
	virtual void Draw();
	virtual void End();

private:
	int m_graphTitle;		// �^�C�g�����S�摜
	int m_graphClick;		// �uSpace�L�[�ŃX�^�[�g�v�摜
	int m_graphBg;				// �w�i�摜

	int m_displayCount;		// �uSpace�L�[���N���b�N�v�\���J�E���g
	int m_fadeAlpha;        // �t�F�[�h�C���A�A�E�g

	bool m_isSpace;			// �X�y�[�X�L�[�������ꂽ���ǂ����̃t���O
	bool m_isFadeIn;		// �t�F�[�h�C���p�̃t���O
	bool m_isFadeOut;		// �t�F�[�h�A�E�g�p�̃t���O
	bool m_isSceneEnd;		// �V�[���J�ڗp�̃t���O
};
