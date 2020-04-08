
#ifdef PE_PLATFORM_WINDOWS
#include "Princess.h"

#ifdef _DEBUG
#include <vld.h>
#endif
#include <iostream>

int main(int, char* [])
{
	std::cout << "Princess Engine" << std::endl;
	auto engine = Princess::Engine{};
	engine.Run();
	return 0;
}

#endif

