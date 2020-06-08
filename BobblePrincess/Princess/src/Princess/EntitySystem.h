#pragma once
//Project includes
//#include "Utils.h"
//#include "ComponentAllocator.h"
//#include "ComponentManager.h"
//
////Standard includes
//#include <vector>
//#include <unordered_map>
//
//namespace Princess
//{
//	struct Entity
//	{
//		//ids for all components
//		std::vector<ID> m_componentIDs;
//	};
//
//	class EntitySystem final : public Singleton<EntitySystem>
//	{
//	public:
//		//---- Constructors ----
//		EntitySystem() = default;
//		EntitySystem(uint16_t capacity);
//
//		//---- Functionality ----
//		uint16_t CreateEntity();
//		Entity& GetEntity(uint16_t id);
//
//
//		//-- Templated --
//		template<typename T>
//		bool AddComponent(uint16_t entityID, T& value);
//		template<typename T>
//		T* GetComponent(uint16_t entityID, ID componentID);
//
//		template<typename T>
//		void RemoveComponent(uint16_t& entityID, ID componentID);
//
//	private:
//		//---- Static Datamembers ----
//		static uint16_t m_ID;
//		//---- Datamembers ---
//		//Look up table of entities -> id entity == name , entity itself
//		// ComponentAllocator<std::pair<uint16_t, Entity>> m_Entities;
//		std::unordered_map<uint16_t, Entity> m_Entities;
//		// std::vector<ComponentManager
//	};
//
//	//---- Functionality ----
//	//-- Templated --
//	template<typename T>
//	bool EntitySystem::AddComponent(uint16_t entityID, T& value)
//	{
//		ID id{ ComponentManager<T>::GetInstance().AddComponent(value) };
//		if (id.IDarray != 0)
//		{
//			m_Entities[entityID].m_componentIDs.push_back(id);
//			return true;
//		}
//		else
//			return false;
//	}
//	template<typename T>
//	T* EntitySystem::GetComponent(uint16_t entityID, ID componentID)
//	{
//		return ComponentManager<T>::GetInstance().GetComponent(componentID);
//	}
//	template<typename T>
//	void Princess::EntitySystem::RemoveComponent(uint16_t& entityID, ID componentID)
//	{
//		//Erase out of Entity
//		std::vector<Princess::ID>::const_iterator cit = std::find(m_Entities[entityID].m_componentIDs.cbegin(), m_Entities[entityID].m_componentIDs.cend(), componentID);
//		m_Entities[entityID].m_componentIDs.erase(cit);
//
//		//If all components are gone then Entity doesn't exist anymore
//		if (m_Entities[entityID].m_componentIDs.size() == 0)
//		{
//			m_Entities.erase(entityID);
//			entityID = 0; //Let the user know the entity doesn't exist anymore
//		}
//
//		//Remove from component manager
//		ComponentManager<T>::GetInstance().RemoveComponent(componentID);
//	}
//}
//
//

