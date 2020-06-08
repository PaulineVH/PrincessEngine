#pragma once
//#include "Singleton.h"
//#include "Utils.h"
//#include "ComponentAllocator.h"
//
//#include <vector>
//#include <utility>
//
//namespace Princess
//{
//	template<typename T>
//	class ComponentManager final : public Singleton<ComponentManager<T>>
//	{
//	public:
//		//---- Constructor ----
//		//---- Destructor ----
//		virtual ~ComponentManager() = default;
//
//		//---- Functionality ----
//		void SetID(uint16_t id);
//
//		ID AddComponent(T& value);
//		T* GetComponent(ID id);
//		const T* GetComponent(ID id) const;
//
//		void RemoveComponent(ID id);
//
//	private:
//		//---- Private Friends ----
//		friend class Singleton<ComponentManager<T>>;
//		//---- Private Constructor ----
//		ComponentManager();
//		//---- Datamembers ----
//		ComponentAllocator<T> m_Components;
//
//		std::vector<T> m_Components;
//		std::vector<uint16_t> m_EntitiesID;
//		
//		uint16_t m_ID;
//	};
//	
//
//	//---- Functionality ----
//	template<typename T>
//	inline void ComponentManager<T>::SetID(uint16_t id)
//	{
//		m_ID = id;
//	}
//
//	template<typename T>
//	inline ID ComponentManager<T>::AddComponent(T& value)
//	{
//		return ID(m_ID, m_Components.Add(std::move(value)));
//	}
//	template<typename T>
//	inline T* ComponentManager<T>::GetComponent(ID id)
//	{
//		return m_Components[id.IDarray - 1];
//	}
//	template<typename T>
//	inline const T* ComponentManager<T>::GetComponent(ID id) const
//	{
//		return m_Components[id.IDarray - 1];
//	}
//
//	template<typename T>
//	inline void ComponentManager<T>::RemoveComponent(ID id)
//	{
//		if (m_ID != id.IDcomponent)
//			return;
//
//		m_Components.Remove(id.IDcomponent);
//	}
//
//	//---- Private Constructor ----
//	template<typename T>
//	ComponentManager<T>::ComponentManager()
//		: m_ID{ 0 }
//		, m_Components{ 10 }
//	{
//	}
//}

