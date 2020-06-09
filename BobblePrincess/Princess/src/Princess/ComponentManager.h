#pragma once
#include "Singleton.h"
#include "Utils.h"
#include "ComponentAllocator.h"

#include <vector>
#include <utility>

namespace Princess
{
	template<typename T>
	class ComponentManager final : public Singleton<ComponentManager<T>>
	{
	public:
		//------ Public Functions ------
		//---- Destructor ----
		virtual ~ComponentManager() = default;

		//---- Functionality ----
		void Initialise(uint16_t capacity);
		bool AddComponent(T& value);
		//You don't want to change the pointer.
		T* const GetComponent(uint16_t id);
		const T* const GetComponent(uint16_t id) const;
		void RemoveComponent(uint16_t id);

	private:
		//---- Private Friends ----
		friend class Singleton<ComponentManager<T>>;
		//------ Private Functions ------
		//---- Private Constructor ----
		ComponentManager();
		//---- Datamembers ----
		ComponentAllocator<T> m_Components;
	};

	//---- Functionality ----
	template<typename T>
	inline void ComponentManager<T>::Initialise(uint16_t size)
	{
		m_Components.Initialise(size);
	}
	template<typename T>
	inline bool ComponentManager<T>::AddComponent(T& value)
	{
		return m_Components.Add(std::move(value));
	}
	template<typename T>
	inline T* const ComponentManager<T>::GetComponent(uint16_t entityID)
	{
		//return m_Components[id.IDarray - 1];
	}
	template<typename T>
	inline const T* const ComponentManager<T>::GetComponent(uint16_t entityID) const
	{
		return m_Components.Find(entityID);
	}

	template<typename T>
	inline void ComponentManager<T>::RemoveComponent(uint16_t entityID)
	{
		m_Components.Remove(entityID);
	}

	//---- Private Constructor ----
	template<typename T>
	ComponentManager<T>::ComponentManager()
		: m_Components{  }
	{
	}
}

