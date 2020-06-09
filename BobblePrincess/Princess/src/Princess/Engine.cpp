//2DAE07 - Vanden Heede, Pauline - 2019/2020
#include "EnginePCH.h"
#include "Engine.h"

//Project Includes
#include "ComponentManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

//Standard Includes
#include <chrono>
#include <thread>
#include <iostream>
#include <SDL.h>

using namespace std;
using namespace std::chrono;

//------ Public Functions ------
//---- Default Constructor ----
//---- Functionality ----
void Princess::Engine::Run()
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	
	cout << "Engine::Run() called!" << endl;
	Initialise(640, 480);


	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			
			renderer.Render();
			
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(m_MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
			lastTime = currentTime;
		}
	}

	CleanUp();
}



//------ Private Functions ------
void Princess::Engine::Initialise(uint32_t width, uint32_t height)
{
	cout << "Engine::Initialize() called!" << endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		"Programming 4 assignment - Pauline Vanden Heede",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);

	if (m_pWindow == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_pWindow);
	SceneManager::GetInstance().CreateScene("Demo");
}

void Princess::Engine::CleanUp()
{
	cout << "Engine::Cleanup() called!" << endl;

	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

