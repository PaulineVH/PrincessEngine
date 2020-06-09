#pragma once
#include "Core.h"
#include <cstdint>

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
	};
	struct Float3
	{
		float x, y, z;

		//---- Constructors ----
		Float3() = default;
		Float3(float x_, float y_, float z_) : x{ x_ }, y{ y_ }, z{ z_ } {  };

	};
}