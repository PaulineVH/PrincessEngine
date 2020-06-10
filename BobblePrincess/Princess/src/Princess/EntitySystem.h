#pragma once
//Project includes
#include "Utils.h"
#include "ComponentAllocator.h"
#include "ComponentManager.h"

//Standard includes
#include <vector>
#include <unordered_map>

namespace Princess
{

//
	class EntitySystem final : public Singleton<EntitySystem>
	{
	public:
		//---- Functionality ----
		uint16_t CreateEntity();


		//-- Templated Functions --
		template<typename T>
		void InitialiseComponentManager(uint16_t capacity);
		template<typename T>
		void AddComponent(T&& value);
		template<typename T, typename... Components>
		void AddComponent(T&& c, Components&&... components);
		template<typename T>
		T* GetComponent(uint16_t entityID);

		template<typename T>
		void RemoveComponent(uint16_t& entityID);

	private:
		//---- Private Friends ----
		friend class Singleton<EntitySystem>;
		//---- Private Constructor ----
		EntitySystem() = default;
		

		//---- Static Datamembers ----
		static uint16_t m_ID;
		//---- Datamembers ---
	};

	//---- Functionality ----
	//-- Templated Functions --
	template<typename T>
	void EntitySystem::InitialiseComponentManager(uint16_t capacity)
	{
		ComponentManager<T>::GetInstance().Initialise(capacity);
	}
	template<typename T>
	void EntitySystem::AddComponent(T&& value)
	{
		ComponentManager<T>::GetInstance().AddComponent(std::move(value));
	}
	template<typename T, typename... Components>
	void EntitySystem::AddComponent(T&& c, Components&&... components)
	{
		AddComponent(std::move(c));
		AddComponent(std::move(components...));
	}
	template<typename T>
	T* EntitySystem::GetComponent(uint16_t entityID)
	{
		return ComponentManager<T>::GetInstance().GetComponent(entityID);
	}
	template<typename T>
	void EntitySystem::RemoveComponent(uint16_t& entityID)
	{
		//Remove from component manager
		ComponentManager<T>::GetInstance().RemoveComponent(entityID);
	}
}
