//2DAE07 - Vanden Heede, Pauline - 2019/200
#pragma once

//Project Includes
#include "Systems.h"

//Standard Includes
#include <vector>


namespace Princess
{
	//Class Forward Declarations
	struct BaseComponentSystem;

	class SystemManager
	{
	public:
		SystemManager() = default;

		InputSystem& GetInputSystem();
		RenderSystem& GetRenderSystem();

	private:
		std::vector<BaseComponentSystem*> m_Systems;

		//Input and Rendersystem will be hold sepperatly
		InputSystem m_InputSystem;
		RenderSystem m_RenderSystem;
	};
}


