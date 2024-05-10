#pragma once
class SoundManager
{
	SoundManager();
	~SoundManager();

	void Init();
	void Update() {}
	void Draw();
	void End();

	// SE
	void SoundButton();
	void SoundJump();

	// BGM
	void BGMDefo();
	void BGMButtle();
	void BGMGameClear();
	void BGMGameOver();


private:
	// �e����
	int m_soundJump;		// SE_�W�����v��
	int m_soundButton;		// SE_���莞
	int m_bgmDefo;			// BGM_�f�t�H���g
	int m_bgmButtle;		// BGM_�퓬��
	int m_bgmGameClear;		// BGM_�Q�[���N���A
	int m_bgmGameOver;		// BGM_�Q�[���I�[�o�[
};

