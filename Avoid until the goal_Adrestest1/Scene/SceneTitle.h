#pragma once
#include "SceneBase.h"

using namespace std;
class SoundManager;
class SceneTitle:
	public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual shared_ptr<SceneBase> Update();
	virtual void Draw();
	virtual void End();

private:
	int m_graphTitle;		// タイトルロゴ画像
	int m_graphClick;		// 「Spaceキーでスタート」画像
	int m_graphBg;				// 背景画像

	int m_displayCount;		// 「Spaceキーをクリック」表示カウント
	int m_fadeAlpha;        // フェードイン、アウト

	bool m_isSpace;			// スペースキーが押されたかどうかのフラグ
	bool m_isFadeIn;		// フェードイン用のフラグ
	bool m_isFadeOut;		// フェードアウト用のフラグ
	bool m_isSceneEnd;		// シーン遷移用のフラグ

	shared_ptr<SoundManager> m_pSound = make_shared<SoundManager>();
};
