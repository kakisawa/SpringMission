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
	virtual void End();

private:
	int m_graphClear;		// 「GameClear」画像
	int m_graphClick;		// 「Spaceキーでスタート」画像
	int m_graphBg;				// 背景画像

	int m_displayCount;		// 「Spaceキーをクリック」表示カウント
	int m_fadeAlpha;        // フェードイン、アウト

	bool m_isSpace;			// スペースキーが押されたかどうかのフラグ
	bool m_isFadeIn;		// フェードイン用のフラグ
	bool m_isFadeOut;		// フェードアウト用のフラグ
	bool m_isSceneEnd;		// シーン遷移用のフラグ
};

