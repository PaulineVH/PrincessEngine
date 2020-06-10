//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once
#include "Utils.h"
// #include "Core.h"
// #include <iostream>

namespace Princess
{
	struct BaseComponent
	{
		//shouldn't be able to switch components from owners
		const uint16_t IDentity;

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
		float rotation; // how does rotation work in 2D? -> only in the xy 

		//---- Constructors ----
		explicit TransformComponent(uint16_t entityID)
			: TransformComponent{ entityID, Float2{ 0.f, 0.f } } {  }
		explicit TransformComponent(uint16_t entityID, const Float2& pos, const Float2& sc = Float2(1.f, 1.f), const float& rot = 0.f) 
			: BaseComponent{ entityID }
			, position{ pos }, scale{ sc }, rotation{ rot } {  }

		//---- Operator Overloading -----
		//-- Assignment Operator --
		TransformComponent& operator=(const TransformComponent& o) noexcept
		{
			this->position = o.position;
			this->scale = o.scale;
			this->rotation = o.rotation;
			return *this;
		}
		TransformComponent& operator=(TransformComponent&& o) noexcept
		{
			this->position = std::move(o.position);
			this->scale = std::move(o.scale);
			this->rotation = std::move(o.rotation);
			return *this;
		}
		//-- Output Operator --
		friend std::ostream& operator<<(std::ostream& out, const TransformComponent& c);
	};
	//---- Operator Overloading -----
	//-- Output Operator --
	inline std::ostream& operator<<(std::ostream& out, const TransformComponent& c)
	{
		out << "Position: " << c.position << ", rotation: " << c.rotation << ", scale: " << c.scale;
		return out;
	}


	struct HealthComponent : public BaseComponent
	{
		uint16_t currentHealth;
		uint16_t maxHealth;

		//---- Constructors ----
		explicit HealthComponent(uint16_t entityID) noexcept
			: HealthComponent{ entityID, 0 } {  }
		explicit HealthComponent(uint16_t entityID, uint16_t max) noexcept
			: BaseComponent{ entityID }
			, maxHealth{ max }, currentHealth{ max } {  }

		//---- Operator Overloading -----
		//-- Assignment Operator --
		HealthComponent& operator=(const HealthComponent& o) noexcept
		{
			this->currentHealth = o.currentHealth;
			this->maxHealth = o.maxHealth;
			return *this;
		}
		HealthComponent& operator=(HealthComponent&& o) noexcept
		{
			this->currentHealth = std::move(o.currentHealth);
			this->maxHealth = std::move(o.maxHealth);
			return *this;
		}
		//-- Output Operator --
		friend std::ostream& operator<<(std::ostream& out, const HealthComponent& c);
	};
	//---- Operator Overloading -----
	//-- Output Operator --
	inline std::ostream& operator<<(std::ostream& out, const HealthComponent& c)
	{
		return out << "Health: " << c.currentHealth << "/" << c.maxHealth;
	}

	struct BoundingBoxComponent : public BaseComponent
	{
		Rectf boundingBox;
		
		//---- Constructors ----
		explicit BoundingBoxComponent(uint16_t entityID)
			: BoundingBoxComponent{ entityID, Rectf{} } {  }
		explicit BoundingBoxComponent(uint16_t entityID, const Rectf& bb)
			: BaseComponent{ entityID }
			, boundingBox{ bb } {  }
	};
}