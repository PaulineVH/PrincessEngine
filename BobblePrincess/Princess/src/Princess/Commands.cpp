//Project Includes
#include "EnginePCH.h"
#include "Commands.h"

void Princess::DuckCommand::Execute(uint16_t)
{
	std::cout << "Duck command called!" << std::endl;
}

void Princess::FartCommand::Execute(uint16_t)
{
	std::cout << "FartCommand Executed" << std::endl;
}

void Princess::FireCommand::Execute(uint16_t)
{
	std::cout << "Fire command called!" << std::endl;
}

void Princess::JumpCommand::Execute(uint16_t)
{
	std::cout << "Jump command called!" << std::endl;
}
