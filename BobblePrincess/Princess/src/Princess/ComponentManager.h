//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once
//Project Includes
#include "Singleton.h"
#include "Utils.h"
#include "ComponentAllocator.h"

//Standard Includes
#include <vector>
#include <utility>

namespace Princess
{
	template<typename T>
	struct ComponentAllocatorPair
	{
		T* pArray;
		uint16_t size;
	};

	template<typename T>
	class ComponentManager final : public Singleton<ComponentManager<T>>
	{
	public:
		
		//------ Public Functions ------
		//---- Destructor ----
		virtual ~ComponentManager() = default;

		//---- Functionality ----
		void Initialise(uint16_t capacity);
		void AddComponent(T&& value);
		//You don't want to change the pointer.
		T* GetComponent(uint16_t entityID);
		const T* GetComponent(uint16_t entityID) const;
		ComponentAllocatorPair<T>& GetComponents() const;
		void RemoveComponent(uint16_t entityID);


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
	inline void ComponentManager<T>::AddComponent(T&& value)
	{
		m_Components.Add(std::move(value));
	}
	template<typename T>
	inline T* ComponentManager<T>::GetComponent(uint16_t entityID)
	{
		//return m_Components[id.IDarray - 1];
		return m_Components.Find(entityID);
	}
	template<typename T>
	inline const T* ComponentManager<T>::GetComponent(uint16_t entityID) const
	{
		return m_Components.Find(entityID);
	}
	template<typename T>
	inline ComponentAllocatorPair<T>& ComponentManager<T>::GetComponents() const
	{
		ComponentAllocatorPair<T> pair{  };
		pair.pArray = m_Components.GetHead();
		pair.size = m_Components.GetSize();
		return pair;
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

