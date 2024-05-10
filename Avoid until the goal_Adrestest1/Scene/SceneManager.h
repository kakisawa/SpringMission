#pragma once
#include <memory>

class SceneBase;
class SoundManager;
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void Init();
	void Update(const SoundManager& mng);
	void Draw();
	void End();

private:
	std::shared_ptr<SceneBase> m_pScene;
};