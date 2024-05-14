#pragma once
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void Init(){}
	void Update() {}
	void Draw(){}
	void End(){}

	void Unload();

	void Ring(int s);
	void Stop(int s);
	
	// SE��ǂݍ���
	void LoadSE();

	// ����炷
	// SE
	void SoundButton();
	void SoundJump();
	// BGM
	void BGMDefo();
	void BGMButtle();
	void BGMGameClear();
	void BGMGameOver();
	// �����~�߂�
	// SE
	void StopSoundButton();
	void StopSoundJump();
	// BGM
	void StopBGMDefo();
	void StopBGMButtle();
	void StopBGMGameClear();
	void StopBGMGameOver();

private:
	// �e����
	int m_soundJump;		// SE_�W�����v��
	int m_soundButton;		// SE_���莞
	int m_bgmDefo;			// BGM_�f�t�H���g
	int m_bgmButtle;		// BGM_�퓬��
	int m_bgmGameClear;		// BGM_�Q�[���N���A
	int m_bgmGameOver;		// BGM_�Q�[���I�[�o�[
};