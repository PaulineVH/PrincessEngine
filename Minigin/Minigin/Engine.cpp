#include "EnginePCH.h"
#include "Engine.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include <chrono>
#include <thread>
#include <SDL.h>

using namespace std;
using namespace std::chrono;

void Princess::Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		"Programming 4 assignment - Pauline Vanden Heede",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	if (m_pWindow == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_pWindow);
}

/**
 * Code constructing the scene world starts here
 */
void Princess::Engine::LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = new GameObject{  };
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = new GameObject{  };
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = new TextObject{ "Programming 4 Assignment", pFont };
	to->SetPosition(80, 20);
	scene.Add(to);

}

void Princess::Engine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void Princess::Engine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

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
			
			lastTime = currentTime;
		}
	}

	Cleanup();
}
