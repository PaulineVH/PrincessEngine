#include "EntitySystem.h"
//---- Static Datamembers ----
uint16_t Princess::EntitySystem::m_ID{ 0 };


//----- Functionality ----
uint16_t Princess::EntitySystem::CreateEntity()
{
	++m_ID;

	//Every entity has by default a transform component with all default values
	Princess::ComponentManager<Princess::TransformComponent>::GetInstance().AddComponent(Princess::TransformComponent{ m_ID, Princess::Float2{ 0.f, 0.f } });

	return m_ID;
}
