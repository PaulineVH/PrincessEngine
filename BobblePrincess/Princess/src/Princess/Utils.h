//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once

//Project Includes
#include "Commands.h"

//3rdParty Includes
#include "SDL.h"
#include <Windows.h>
#include <XInput.h>

//Standard Includes
#include <cstdint>
#include <iostream>
#include <iomanip>

namespace Princess
{
	/*
	Maybe problem: C standard leaves bitfield order to compiler implementation.
	-> We do not care about the order of the bitfield -> we only need the 2IDs packed into one
	-> So that we can easily identify which component it is and where in the object pool this is situated
	-> This means we can use a vector of just ID structs which is only 16 bits (sizeof(ID) = 2 bytes) big
	*/
	//struct ID // Declare ID bit field
	//{
	//	uint16_t IDarray : 13; // 000? ???? ???? ????
	//	uint16_t IDcomponent : 3; // ???0 0000 0000 0000
	//};

	struct Float2
	{
		float x, y;

		//---- Constructors ----
		Float2() = default;
		Float2(float x_, float y_) : x{ x_ }, y{ y_ } {  };
		Float2(const Float2& o) noexcept: x{ o.x }, y{ o.y } {  };
		Float2(Float2&& o) noexcept : x{ std::move(o.x) }, y{ std::move(o.y) } {  };

		//---- Operator Overloading ----
		//-- Assignment Operator
		Float2& operator=(const Float2& o) noexcept 
		{
			this->x = o.x;
			this->y = o.y;
			return *this;
		}
		Float2& operator=(Float2&& o) noexcept 
		{
			this->x = o.x;
			this->y = o.y;
			o.x = 0.f;
			o.y = 0.f;
			return *this;
		}
		//-- Output Operator --
		friend std::ostream& operator<<(std::ostream& out, const Float2& f);
	};
	//---- Operator Overloading ----
	//-- Output Operator --
	inline std::ostream& operator<<(std::ostream& out, const Float2& f)
	{
		std::cout.setf(std::ios::fixed);
		return out << "(" << std::setprecision(2) << f.x << ", " << f.y << ")";
	}


	struct Float3
	{
		float x, y, z;

		//---- Constructors ----
		Float3() = default;
		Float3(float x_, float y_, float z_) : x{ x_ }, y{ y_ }, z{ z_ } {  };
		Float3(const Float3& o) noexcept : x{ o.x }, y{ o.y }, z{ o.z } {  };
		Float3(Float3&& o) noexcept : x{ std::move(o.x) }, y{ std::move(o.y) }, z{ std::move(o.z) } {  };

		//---- Operator Overloading ----
		//-- Assignment Operator
		Float3& operator=(const Float3& o) noexcept 
		{
			this->x = o.x;
			this->y = o.y;
			this->z = o.z;
			return *this;
		}
		Float3& operator=(Float3&& o) noexcept 
		{
			this->x = std::move(o.x);
			this->y = std::move(o.y);
			this->z = std::move(o.z);
			return *this;
		}
		//-- Output Operator --
		friend std::ostream& operator<<(std::ostream& out, const Float3& f);
	};
	//---- Operator Overloading ----
	//-- Output Operator --
	inline std::ostream& operator<<(std::ostream& out, const Float3& f)
	{
		std::cout.setf(std::ios::fixed);
		return out << "(" << std::setprecision(2) << f.x << ", " << f.y << ", " << f.z << ")";
	}

	//-------------------------------------------------------------------------------------
	//--------------------------------------- Rectf ---------------------------------------
	//-------------------------------------------------------------------------------------
	struct Rectf
	{
		Float2 leftBottom;
		float width;
		float height;

		//---- Constructors ----
		Rectf() = default;
		explicit Rectf(const Float2& leftBottom, float w, float h) noexcept
			: leftBottom{ leftBottom }, width{ w }, height{ h } {  }
		explicit Rectf(float l, float b, float w, float h) noexcept
			: leftBottom{ l, b }, width{ w }, height{ h } {  }
		Rectf(const Rectf& o) noexcept
			: leftBottom{ o.leftBottom }, width{ o.width }, height{ o.height } {  }
		Rectf(Rectf&& o) noexcept
			: leftBottom{ std::move(o.leftBottom) }, width{ o.width }, height{ o.height } 
		{
			o.width = 0.f;
			o.height = 0.f;
		}

		//---- Operators -----
		//-- Assignment Operators --
		Rectf& operator=(const Rectf& o) noexcept
		{
			this->leftBottom = o.leftBottom;
			this->width = o.width;
			this->height = o.height;
			
			return *this;
		}
		Rectf& operator=(Rectf&& o) noexcept
		{
			this->leftBottom = std::move(o.leftBottom);
			this->width = o.width;
			this->height = o.height;

			o.width = 0.f;
			o.height = 0.f;

			return *this;
		}
	};


	//-------------------------------------------------------------------------------------
	//--------------------------------------- Button --------------------------------------
	//-------------------------------------------------------------------------------------
	struct Button
	{
		union
		{
			SDL_Keycode keyboardKey;
			//Bitmask of the device digital buttons is a WORD
			//https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad
			WORD controllerButton;
		} button{};
		Command* pCommand{ nullptr };
		//---- Constructors ----
		Button() = default;
		Button(WORD&& controllerButton, Command* pNewCommand)
			: pCommand{ pNewCommand }
		{
			button.controllerButton = controllerButton;
		}
		/*Button(const SDL_Keycode& keyboardKey, Command* pNewCommand)
			: pCommand{ pNewCommand }
		{
			button.keyboardKey = keyboardKey;
		}*/

		Button(Button&& o)
			: button{ o.button }
			, pCommand{ o.pCommand }
		{
			o.button.controllerButton = 0;
			o.pCommand = nullptr;
		}
		Button& operator=(Button&& o)
		{
			this->button = o.button;
			this->pCommand = o.pCommand;

			o.button.controllerButton = 0;
			o.pCommand = nullptr;
			return *this;
		}

		~Button()
		{
			if (pCommand)
			{
				delete pCommand;
				pCommand = nullptr;
			}

		}
	};
}