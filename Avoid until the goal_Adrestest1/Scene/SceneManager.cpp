#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"

SceneManager::SceneManager() :
	m_pScene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	// 最初のシーンのメモリを確保する
	m_pScene = std::make_shared<SceneTitle>();
	m_pScene->Init();
}

void SceneManager::Update()
{
	std::shared_ptr<SceneBase> pNext = m_pScene->Update();
	if (pNext != m_pScene)
	{
		// 現在のシーンの終了処理
		m_pScene->End();

		// Updateが返した新しいシーンの開始処理を行う
		m_pScene = pNext;
		m_pScene->Init();
	}
}

void SceneManager::Draw()
{
	m_pScene->Draw();
}

void SceneManager::End()
{
	m_pScene->End();
}
