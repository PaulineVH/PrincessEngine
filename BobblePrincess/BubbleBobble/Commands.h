//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once

//Standard Includes
#include <cstdint>
#include <iostream>

namespace BubbleBobble
{
	void DuckCommand(uint16_t entityID)
	{
		std::cout << "Entity with ID:" << entityID << " executing DuckCommand" << std::endl;
	}
}
