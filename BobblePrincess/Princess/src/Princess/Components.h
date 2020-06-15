//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once

//Project Includes
#include "Utils.h"
#include "Exception.h"
#include "FixedSizeAllocator.h"

//Standard Includes
#include <vector>
#include <unordered_map>

namespace Princess
{
	//Class Forward Declarations in the namespace Princess
	class Texture2D;

	//-------------------------------------------------------------------------------------
	//----------------------------------- BaseComponent -----------------------------------
	//-------------------------------------------------------------------------------------
	struct BaseComponent
	{
		//---- Datamembers ----
		//shouldn't be able to switch components from owners
		uint16_t IDentity;

		//---- Constructors ----
		explicit BaseComponent() : IDentity{ 0 } {  }
		explicit BaseComponent(uint16_t id) : IDentity{ id } {  }
		BaseComponent(const BaseComponent& o) noexcept
			: IDentity{ o.IDentity }
		{
		}
		BaseComponent(BaseComponent&& o) noexcept
			: IDentity{ o.IDentity }
		{
			std::cout << "BaseComponent move constructor!\n";
			o.IDentity = 0;
		}

		//---- Operators ----
		//-- Assignment Operators --
		BaseComponent& operator=(const BaseComponent& o) noexcept
		{
			this->IDentity = o.IDentity;

			return *this;
		}
		BaseComponent& operator=(BaseComponent&& o) noexcept
		{
			std::cout << "BaseComponent move assignment operator!\n";

			this->IDentity = o.IDentity;
			o.IDentity = 0;

			return *this;
		}
		
		//----- Destructor ----
		virtual ~BaseComponent() = default;
	};

	/* 
		it's for the user of the game to make the game specific components that it needs,
		but here some modular components
	*/

	//-------------------------------------------------------------------------------------
	//-------------------------------- Transform Component --------------------------------
	//-------------------------------------------------------------------------------------
	struct TransformComponent final : public BaseComponent
	{
		Float2 position;
		Float2 scale;
		float rotation; // how does rotation work in 2D? -> only in the xy 

		//---- Constructors ----
		explicit TransformComponent(uint16_t entityID) noexcept
			: TransformComponent{ entityID, Float2{ 0.f, 0.f } } {  }
		explicit TransformComponent(uint16_t entityID, const Float2& pos, const Float2& sc = Float2(1.f, 1.f), const float& rot = 0.f) noexcept
			: BaseComponent{ entityID }
			, position{ pos }, scale{ sc }, rotation{ rot } {  }
		TransformComponent(const TransformComponent&) = delete;
		TransformComponent(TransformComponent&& o) noexcept
			: BaseComponent{ std::move(o) }
			, position{ std::move(o.position) }, scale{ std::move(o.scale) }, rotation{ o.rotation }
		{
			o.rotation = 0;
		}
		//---- Destructors ----
		virtual ~TransformComponent() = default;

		//---- Operator Overloading -----
		//-- Assignment Operator --
		TransformComponent& operator=(const TransformComponent& o) = delete;
		TransformComponent& operator=(TransformComponent&& o) noexcept
		{
			BaseComponent::operator=(std::move(o));
			this->position = std::move(o.position);
			this->scale = std::move(o.scale);
			this->rotation = o.rotation;

			o.rotation = 0.f;

			return *this;
		}
		//-- Output Operator --
		friend std::ostream& operator<<(std::ostream& out, const TransformComponent& c);

	private:
	};
	//---- Operator Overloading -----
	//-- Output Operator --
	inline std::ostream& operator<<(std::ostream& out, const TransformComponent& c)
	{
		out << "Entity with ID " << c.IDentity << "has following transform: \n";
		out << "Position: " << c.position << ", rotation: " << c.rotation << ", scale: " << c.scale;
		return out;
	}


	//-------------------------------------------------------------------------------------
	//---------------------------------- Health Component ---------------------------------
	//-------------------------------------------------------------------------------------
	struct HealthComponent final : public BaseComponent
	{
		uint16_t currentHealth;
		uint16_t maxHealth;

		//---- Constructors ----
		explicit HealthComponent(uint16_t entityID) noexcept
			: HealthComponent{ entityID, 0 } {  }
		explicit HealthComponent(uint16_t entityID, uint16_t max) noexcept
			: BaseComponent{ entityID }
			, maxHealth{ max }, currentHealth{ max } {  }
		HealthComponent(const HealthComponent&) = delete;
		HealthComponent(HealthComponent&& o) noexcept
			: BaseComponent{ std::move(o) }
			, currentHealth{ o.currentHealth }, maxHealth{ o.maxHealth }
		{
			o.currentHealth = 0;
			o.maxHealth = 0;
		}

		//---- Destructor ----
		virtual ~HealthComponent() = default;

		//---- Operator Overloading -----
		//-- Assignment Operator --
		HealthComponent& operator=(const HealthComponent& o) = delete;
		HealthComponent& operator=(HealthComponent&& o) noexcept
		{
			BaseComponent::operator=(std::move(o));
			this->currentHealth = o.currentHealth;
			this->maxHealth = o.maxHealth;

			o.currentHealth = 0;
			o.maxHealth = 0;

			return *this;
		}
		//-- Output Operator --
		friend std::ostream& operator<<(std::ostream& out, const HealthComponent& c);
	};
	//---- Operator Overloading -----
	//-- Output Operator --
	inline std::ostream& operator<<(std::ostream& out, const HealthComponent& c)
	{
		out << "Entity with ID " << c.IDentity << "has following health: \n";
		return out << "Health: " << c.currentHealth << "/" << c.maxHealth;
	}


	//-------------------------------------------------------------------------------------
	//------------------------------- BoundingBox Component -------------------------------
	//-------------------------------------------------------------------------------------
	struct BoundingBoxComponent final : public BaseComponent
	{
		Rectf boundingBox;
		
		//---- Constructors ----
		explicit BoundingBoxComponent(uint16_t entityID) noexcept
			: BoundingBoxComponent{ entityID, Rectf{} } {  }
		explicit BoundingBoxComponent(uint16_t entityID, const Rectf& bb) noexcept
			: BaseComponent{ entityID }
			, boundingBox{ bb } {  }
		BoundingBoxComponent(const BoundingBoxComponent& o) = delete;
		BoundingBoxComponent(BoundingBoxComponent&& o) noexcept
			: BaseComponent{ std::move(o) }
			, boundingBox{ std::move(o.boundingBox) } {  }

		//---- Destructor ----
		virtual ~BoundingBoxComponent() = default;

		//---- Operators ----
		//-- Assignment Operators --
		BoundingBoxComponent& operator=(const BoundingBoxComponent&) = delete;
		BoundingBoxComponent& operator=(BoundingBoxComponent&& o) noexcept
		{
			BaseComponent::operator=(std::move(o));
			this->boundingBox = std::move(o.boundingBox);

			return *this;
		}
	};


	//-------------------------------------------------------------------------------------
	//----------------------------------- Move Component ----------------------------------
	//-------------------------------------------------------------------------------------
	struct MoveComponent : public BaseComponent
	{
		float xSpeed;
		float ySpeed;

		//---- Constructors ----
		explicit MoveComponent(uint16_t entityID) noexcept
			: MoveComponent{ entityID, 0.f, 0.f } {  }
		explicit MoveComponent(uint16_t entityID, float _xSpeed, float _ySpeed) noexcept
			: BaseComponent{ entityID }
			, xSpeed{ _xSpeed }, ySpeed{ _ySpeed } {  }
		MoveComponent(const MoveComponent&) = delete;
		MoveComponent(MoveComponent&& o)
			: BaseComponent{ std::move(o) }
			, xSpeed{ o.xSpeed }, ySpeed{ o.ySpeed }
		{
			o.xSpeed = 0.f;
			o.ySpeed = 0.f;
		}

		//---- Operator Overloading -----
		//-- Assignment Operator --
		MoveComponent& operator=(const MoveComponent& o) = delete;
		MoveComponent& operator=(MoveComponent&& o) noexcept
		{
			BaseComponent::operator=(std::move(o));
			this->xSpeed = o.xSpeed;
			this->ySpeed = o.ySpeed;

			o.xSpeed = 0;
			o.ySpeed = 0;
			o.IDentity = 0;

			return *this;
		}
	};


	//-------------------------------------------------------------------------------------
	//--------------------------------- Texture Component ---------------------------------
	//-------------------------------------------------------------------------------------
	struct TextureComponent : BaseComponent
	{
		Texture2D* pTexture;

		explicit TextureComponent(uint16_t entityID) : TextureComponent{ entityID, nullptr } {  };
		explicit TextureComponent(uint16_t entityID, Texture2D* pT) : BaseComponent{ entityID }, pTexture{ pT } {  };
	};


	//-------------------------------------------------------------------------------------
	//---------------------------------- Input Component ----------------------------------
	//-------------------------------------------------------------------------------------
	struct InputComponent : public BaseComponent
	{
		FixedSizeAllocator<Button> input;
		//default value false
		bool controllerUsed;


		//---- Constructors ----
		InputComponent() = default;
		explicit InputComponent(uint16_t entityID) noexcept
			: BaseComponent{ entityID }
			, controllerID{ 0 }
			, input{  }
			, controllerUsed{ false } {  }
		explicit InputComponent(uint16_t entityID, DWORD IDController, uint16_t nrOfButtons, bool controllerActive = false) noexcept
			: BaseComponent{ entityID }
			, controllerID{ IDController }
			, input{ nrOfButtons }
			, controllerUsed{ controllerActive } {  }
		InputComponent(const InputComponent&) = delete;
		InputComponent(InputComponent&& o) noexcept
			: BaseComponent{ std::move(o) }
			, controllerID{ o.controllerID }, input{ std::move(o.input) }, controllerUsed{ o.controllerUsed }
		{
			o.controllerID = 0;
			o.controllerUsed = false;
		}

		//---- Destructor ----
		virtual ~InputComponent() = default;

		//---- Operators ----
		//-- Assignment Operators --
		InputComponent& operator=(const InputComponent&) = delete;
		InputComponent& operator=(InputComponent&& o) noexcept
		{
			BaseComponent::operator=(std::move(o));
			this->controllerUsed = o.controllerUsed;
			this->controllerID = o.controllerID;
			this->input = std::move(o.input);

			o.controllerUsed = false;
			o.controllerID = 0;
			o.IDentity = 0;

			return *this;
		}

		//---- Functionality ----
		//-- Getters --
		DWORD GetControllerID() const
		{
			return controllerID;
		}
		//-- Setters --
		void SetControllerID(DWORD ID)
		{
			try
			{
				if (ID >= 0 && ID < XUSER_MAX_COUNT)
				{
					controllerID = ID;
				}
				else
				{
					throw Exception("Controlled ID out of bounds! Can only connect up to 4 controllers!");
				}
			}
			catch (Exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}

	private:
		//number from 0 to 3 -> xinput can connect up to 4 controllers.
		DWORD controllerID; 
	};
}