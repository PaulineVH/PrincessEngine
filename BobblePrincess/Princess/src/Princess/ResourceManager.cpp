//2DAE07 - Vanden Heede, Pauline - 2019/2020
//Project Includes
#include "EnginePCH.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

//SDL Includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//---- Destructor ----
Princess::ResourceManager::~ResourceManager()
{
	for (std::pair<std::string, Texture2D*> p : m_pTextures)
	{
		delete p.second;
		p.second = nullptr;
	}
	m_pTextures.clear();
}


void Princess::ResourceManager::Initialise(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

Princess::Texture2D* Princess::ResourceManager::LoadTexture(const std::string& file)
{
	std::unordered_map<std::string, Texture2D*>::const_iterator pFound = m_pTextures.find(file);
	if (pFound == m_pTextures.cend())
	{
		SDL_Texture* pTexture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), (m_DataPath + file).c_str());
		if(!pTexture)
			throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());

		m_pTextures[file] = new Texture2D{ pTexture };
	}
	return m_pTextures[file];

	/*const auto fullPath = m_DataPath + file;
	auto pTexture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (pTexture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return new Texture2D{ pTexture };*/
}

void Princess::ResourceManager::UnloadTexture(const std::string& file)
{
	std::unordered_map<std::string, Texture2D*>::iterator pFound = m_pTextures.find(file);
	if (pFound != m_pTextures.end())
	{
		delete pFound->second;
		pFound->second = nullptr;
		m_pTextures.erase(file);
	}
}

Princess::Texture2D* Princess::ResourceManager::GetTexture(const std::string& file) const
{
	std::unordered_map<std::string, Texture2D*>::const_iterator pFound = m_pTextures.find(file);
	if (pFound == m_pTextures.cend())
		return nullptr;
	else
		return pFound->second;
}

Princess::Font* Princess::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return new Font{ m_DataPath + file, size };
}
