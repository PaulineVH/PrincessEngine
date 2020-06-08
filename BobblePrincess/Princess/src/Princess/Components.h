#pragma once
#include "Utils.h"
namespace Princess
{
	struct BaseComponent
	{
		uint16_t IDentity;

		BaseComponent() : IDentity{ 0 } {  };
		BaseComponent(uint16_t id) : IDentity{ id } {  };
	};

	/* 
		it's for the user of the game to make the game specific components that it needs,
		but here some modular components
	*/
	struct TransformComponent : public BaseComponent
	{
		Float2 position;
		Float2 scale;
		Float2 rotation; // how does rotation work in 2D? -> only in the xy 

		//---- Constructors ----
		TransformComponent() = default;
		TransformComponent(uint16_t entityID, Float2 pos, Float2 sc = Float2(1.f, 1.f), Float2 rot = Float2(0.f, 0.f)) 
			: BaseComponent{ entityID }
			, position{ pos }, scale{ sc }, rotation{ rot } {  };
	};

	struct HealthComponent : public BaseComponent
	{
		uint16_t m_CurrentHealth;
		uint16_t m_MaxHealth;

		//---- Constructors ----
		HealthComponent() = default;
		HealthComponent(uint16_t entityID, uint16_t max) 
			: BaseComponent{ entityID }
			, m_MaxHealth{ max }, m_CurrentHealth{ max } {  };
	};
}