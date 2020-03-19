#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Princess::SceneManager::Update()
{
	for(auto& spScene : m_spScenes)
	{
		spScene->Update();
	}
}

void Princess::SceneManager::Render()
{
	for (const auto& spScene : m_spScenes)
	{
		spScene->Render();
	}
}

Princess::Scene& Princess::SceneManager::CreateScene(const std::string& name)
{
	const auto spScene = std::shared_ptr<Scene>(new Scene(name));
	m_spScenes.push_back(spScene);
	return *spScene;
}
