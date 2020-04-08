#include "EnginePCH.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"

void Princess::SceneManager::Update(const float deltaTime)
{
	for(auto& pScene : m_pScenes)
	{
		pScene->Update(deltaTime);
	}

	//if (++m_FPSCounter > 10)
	{
		m_pFPS->SetText("FPS: " + std::to_string(uint32_t(1.f / deltaTime)));
		m_FPSCounter = 0;
	}
	m_pFPS->Update(deltaTime);
}

void Princess::SceneManager::Render()
{
	for (const auto& pScene : m_pScenes)
	{
		pScene->Render();
	}

	m_pFPS->Render();
}

Princess::SceneManager::~SceneManager()
{
	uint32_t size{ (uint32_t)m_pScenes.size() };
	for (uint32_t i{ 0 }; i < size; ++i)
	{
		delete m_pScenes[i];
	}
	m_pScenes.clear();

	delete m_pFPS;
	m_pFPS = nullptr;
}

Princess::Scene& Princess::SceneManager::CreateScene(const std::string& name)
{
	const auto pScene = new Scene{ name };
	m_pScenes.push_back(pScene);

	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	m_pFPS = new TextObject{ "FPS: ", pFont };
	m_pFPS->SetPosition(10, 10);

	return *pScene;
}
