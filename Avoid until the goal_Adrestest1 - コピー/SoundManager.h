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
	
	// SEを読み込む
	void LoadSE();

	// 音を鳴らす
	// SE
	void SoundButton();
	void SoundJump();
	// BGM
	void BGMDefo();
	void BGMButtle();
	void BGMGameClear();
	void BGMGameOver();
	// 音を止める
	// SE
	void StopSoundButton();
	void StopSoundJump();
	// BGM
	void StopBGMDefo();
	void StopBGMButtle();
	void StopBGMGameClear();
	void StopBGMGameOver();

private:
	// 各音源
	int m_soundJump;		// SE_ジャンプ時
	int m_soundButton;		// SE_決定時
	int m_bgmDefo;			// BGM_デフォルト
	int m_bgmButtle;		// BGM_戦闘中
	int m_bgmGameClear;		// BGM_ゲームクリア
	int m_bgmGameOver;		// BGM_ゲームオーバー
};