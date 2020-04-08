#pragma once

#include "Core.h"

struct SDL_Window;

namespace Princess
{
	class TextObject;
	
	class PRINCESS_API Engine
	{
	public:
		void Initialize();
		void LoadGame();
		void Cleanup();
		void Run();
	private:
		static const int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_pWindow{};
	};
}