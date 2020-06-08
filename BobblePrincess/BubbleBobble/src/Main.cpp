
#ifdef PE_PLATFORM_WINDOWS
#include "Princess.h"

#ifdef _DEBUG
#include <vld.h>
#endif
#include <iostream>
#include <iomanip>
#include <bitset>

class Demo final : public Princess::Engine
{
private:
	virtual void LoadGame() override
	{
		std::cout << "Demo: LoadGame() called!" << std::endl;

	}
};


int main(int, char* [])
{
	Demo game{};
	game.Run();
	return 0;
}

#endif

