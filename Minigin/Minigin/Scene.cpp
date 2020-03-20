#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace Princess;

uint32_t Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	uint32_t size{ (uint32_t)m_pObjects.size() };
	for (uint32_t i{ 0 }; i < size; ++i)
	{
		delete m_pObjects[i];
	}
	m_pObjects.clear();
}

void Scene::Add(SceneObject* pObject)
{
	m_pObjects.push_back(pObject);
}

void Scene::Update(const float deltaTime)
{
	for(auto& pObject : m_pObjects)
	{
		pObject->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& pObject : m_pObjects)
	{
		pObject->Render();
	}
}

