#pragma once
//#include "Core.h"

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
			this->x = std::move(o.x);
			this->y = std::move(o.y);
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

	struct Rectf
	{
		Float2 leftBottom;
		float width;
		float height;

		//---- Constructors ----
		Rectf() = default;
		Rectf(const Float2& leftBottom, float w, float h)
			: leftBottom{ leftBottom }, width{ w }, height{ h } {  }
		Rectf(float l, float b, float w, float h)
			: leftBottom{ l, b }, width{ w }, height{ h } {  }
		Rectf(const Rectf& o) noexcept
			: leftBottom{ o.leftBottom }, width{ o.width }, height{ o.height } {  }
		Rectf(Rectf&& o) noexcept
			: leftBottom{ std::move(o.leftBottom) }, width{ std::move(o.width) }, height{ std::move(o.height) } {  }

	};
}