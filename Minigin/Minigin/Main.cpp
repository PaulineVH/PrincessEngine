#include "EnginePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Engine.h"

int main(int, char*[]) 
{
	Princess::Engine engine;
	
	engine.Run();
    
	return 0;
}