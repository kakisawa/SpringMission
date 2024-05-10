#pragma once
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void Init();
	void Update() {}
	void Draw();
	void End();

	void Ring(int s);
	
	// SE
	void SoundButton();
	void SoundJump();

	// BGM
	void BGMDefo();
	void BGMButtle();
	void BGMGameClear();
	void BGMGameOver();


private:
	// 各音源
	int m_soundJump;		// SE_ジャンプ時
	int m_soundButton;		// SE_決定時
	int m_bgmDefo;			// BGM_デフォルト
	int m_bgmButtle;		// BGM_戦闘中
	int m_bgmGameClear;		// BGM_ゲームクリア
	int m_bgmGameOver;		// BGM_ゲームオーバー
};

