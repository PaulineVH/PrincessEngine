#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Princess::SceneManager::Update()
{
	for(auto& pScene : m_pScenes)
	{
		pScene->Update();
	}
}

void Princess::SceneManager::Render()
{
	for (const auto& pScene : m_pScenes)
	{
		pScene->Render();
	}
}

Princess::SceneManager::~SceneManager()
{
	uint32_t size{ (uint32_t)m_pScenes.size() };
	for (uint32_t i{ 0 }; i < size; ++i)
	{
		delete m_pScenes[i];
	}
	m_pScenes.clear();
}

Princess::Scene& Princess::SceneManager::CreateScene(const std::string& name)
{
	const auto pScene = new Scene{ name };
	m_pScenes.push_back(pScene);
	return *pScene;
}
