//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once
//Project Includes
#include "ComponentManager.h"
#include "Components.h"
#include "Renderer.h"

//Standard Includes
//#include "windows.h"

namespace Princess
{
	//Almost a case of structs as function pointers.


	//Abstract class
	struct BaseComponentSystem abstract
	{
		//Pure virtual functions
		virtual void OnUpdate(float) = 0;
		virtual void OnCollision() = 0;
	};


	struct RenderSystem final
	{
		void OnUpdate(float)
		{
			ComponentAllocatorPair<TextureComponent> pair = ComponentManager<TextureComponent>::GetInstance().GetComponents();
			TextureComponent* pBegin{ pair.pArray };
			TextureComponent* pEnd{ pair.pArray + pair.size };
			for (; pBegin != pEnd; ++pBegin)
			{
				Renderer::GetInstance().RenderTexture(pBegin, ComponentManager<TransformComponent>::GetInstance().GetComponent(pBegin->IDentity)->position);
			}
		}
	};


	struct InputSystem final
	{
		void Initialise()
		{
			m_NrOfPlayers = ComponentManager<InputComponent>::GetInstance().GetNumberOfComponents();
			m_CurrentStateControllers.resize(m_NrOfPlayers);
		}

		bool ProcessInput()
		{
			//for every controller check the input
			for (size_t i{ 0 }; i < m_CurrentStateControllers.size(); ++i)
			{
				ZeroMemory(&m_CurrentStateControllers[i], sizeof(XINPUT_STATE));
				XInputGetState(i, &m_CurrentStateControllers[i]);
			}

			//keyboard input
			while (SDL_PollEvent(&m_CurrentStateKeyboard)) {
				if (m_CurrentStateKeyboard.type == SDL_QUIT) {
					return false;
				}
			}

			return true;
		}

		void OnUpdate()
		{
			ComponentAllocatorPair<InputComponent> pair = ComponentManager<InputComponent>::GetInstance().GetComponents();
			InputComponent* pBegin{ pair.pArray };
			InputComponent* pEnd{ pair.pArray + pair.size };

			for (; pBegin != pEnd; ++pBegin) // for every inputcomponent
			{
				//for every input action it has
				for (uint16_t i{ 0 }; i < pBegin->input.GetSize(); ++i)
				{
					//check if the related key is pressed
					if (IsPressed(pBegin->input[i], pBegin->GetControllerID(), pBegin->controllerUsed))
					{
						pBegin->input[i].pCommand->Execute(pBegin->IDentity);
					}
				}

			}
		}

	private:
		//---- Datamembers ----
		uint16_t m_NrOfPlayers{};
		std::vector<XINPUT_STATE> m_CurrentStateControllers{};
		SDL_Event m_CurrentStateKeyboard{};

		//---- Private Functions ----
		bool IsPressed(const Button& button, DWORD controllerID, bool controllerUsed)
		{
			if (controllerUsed)
			{
				//check for controller input
				return button.button.controllerButton & m_CurrentStateControllers[controllerID].Gamepad.wButtons;
			}
			else
			{
				//check for keyboard input
				return button.button.keyboardKey == m_CurrentStateKeyboard.key.keysym.sym;
			}
		}
	};

}
