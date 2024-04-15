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
	int m_graphClick;		// 「Spaceキーをクリック」画像

	int m_displayCount;		// 「Spaceキーをクリック」表示カウント

	bool m_isSpace;			// スペースキーが押されたかどうかのフラグ
};

