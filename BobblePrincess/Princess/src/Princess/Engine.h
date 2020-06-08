#pragma once
//Project includes
#include "Core.h"
#include <cstdint>

//Forward declarations
struct SDL_Window;

namespace Princess
{
	class TextObject;
	
	class PRINCESS_API Engine
	{
	public:
		//------ Public Functions ------
		//---- Default Constructor ----
		//---- Functionality ----
		void Run();
	private:
		static const int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_pWindow{};

		//------ Private Functions ------
		virtual void LoadGame() = 0;
		void Initialise(uint32_t width, uint32_t height);
		void CleanUp();
	};
}