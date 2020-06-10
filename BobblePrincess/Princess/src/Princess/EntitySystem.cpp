#include "EntitySystem.h"
//---- Static Datamembers ----
uint16_t Princess::EntitySystem::m_ID{ 0 };


//----- Functionality ----
uint16_t Princess::EntitySystem::CreateEntity()
{
	++m_ID;
	return m_ID;
}

